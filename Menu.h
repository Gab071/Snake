#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

enum GameMode  { EASY, NORMAL, HARD, CLOSE };

class Menu {

    GameMode choose_mode;
    bool exitMenu;
    sf::Font font;

    /// Funkcja obsługuje kliknięcie klawiatury
    bool keyClick(sf::Event & event);

    /// Funkcja wyświetla słowo choose difficulty
    void drawDiff(sf::Text &diff, const sf::RenderWindow & menuWindow) const;

    /// Funkcja wyświetla słowo Easy 1
    void drawEasy(sf::Text & easy, const sf::RenderWindow & menuWindow) const;

    /// Funkcja wyświetla słowo Normal 2
    void drawNormal(sf::Text & normal, const sf::RenderWindow & menuWindow) const;

    /// Funkcja wyświetla słowo Hard 3
    void drawHard(sf::Text & hard, const sf::RenderWindow & menuWindow) const;

public:

    /// Konstruktor
    Menu();

    /// Funkcja do kontroli menu
    void controlMenu(sf::RenderWindow & menuWindow);

    /// Funkcja wyświetla menu
    void drawMenu(sf::RenderWindow & menuWindow);

    /// Funkcja zwraca choose_mode
    /// CLOSE - gdy zamykamy okno w programie to następne też musi się zakryć
    GameMode getGameMode() const;
};


#endif //MENU_H
