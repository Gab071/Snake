

#ifndef SNCONTROLLER_H
#define SNCONTROLLER_H

#include "SnakeLogic.h"
#include "SNSFMLView.h"
#include <SFML/Graphics.hpp>

class SNSFMLController {

    SnakeLogic & logic;
    SNSFMLView & view;

    int tileSize;
    Course course;
    Turn turnSnake;

    bool Triggered;
    bool is_gameOver;
    bool isGameStart;

    /// Funkcja obsługuje kliknięcie klawiatury
    /// \param event odpowiedzialny za obsługę zdarzeń (Closed, Resized, Mouseclick)
    void keyClick(sf::Event &event);

    /// Funkcja obsługuje zdarzenia (Closed, Resized, Mouseclick)
    /// \param event odpowiedzialny za obsługę zdarzeń (Closed, Resize, Mouseclick)
    void Events(sf::RenderWindow & window, sf::Event & event);

    /// Funkcja odpowiedzialna za rozpoczęcie zegarka n sekundowego po zanończeniu rozgrywki
    /// \param clock ten zegareczek, który odlicza n sekund
    void clockStart(sf::Clock & clock);

    void gameStart(sf::RenderWindow & window, sf::Clock & clockStart);

    /// Funkcje, które obsługują wciśnięcie klucza klawiatury
    void keyW();
    void keyA();
    void keyS();
    void keyD();

    /// Funkcja, która obsługuje wszystkie funkcje wyświetlania w sfml
    void drawAll(sf::RenderWindow & window, bool & save, sf::Clock & clockGameStart);

public:
    /// Konstruktor
    SNSFMLController(SnakeLogic & logic, SNSFMLView & view);

    /// Funckja obsługująca rozgrywkę
    /// \param window odpowiedzialny za obsługę planszy (obsługę wyświetlania)
    void play(sf::RenderWindow &window);
};



#endif //SNCONTROLLER_H
