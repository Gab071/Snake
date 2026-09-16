
#ifndef SNAKE_AK_CZ16_286997_MSSFMLVIEW_H
#define SNAKE_AK_CZ16_286997_MSSFMLVIEW_H

#include "SnakeLogic.h"
#include <string>
#include <vector>

class SNSFMLView {

    SnakeLogic & logic;
    sf::Font font;

    int tileSize = 256;
    float scale = 1.0f;

    int score = 0;

    // Tu po prostu kalkulujemy jaki rozmiar będzie posiadała nasza nowa plansza
    int boardWidth = logic.getBoardWidth();
    int boardHeight = logic.getBoardHeight();
    int pixelWidth = boardWidth * tileSize;
    int pixelHeight = boardHeight * tileSize + tileSize;

    std::map<char, sf::Texture> textures;
    std::map<char, sf::Sprite> sprites;


    /// Funkcja odpowiedzialna za załadowanie grafik (teraz jest w Konstruktorze)
    void loadTextures();

    /// Funkcja odpowiedzialna za stworzenie sprites (grafika dla sfml)
    void setupSprites();

    /// Funkcja, która przeskalowuje planszę, gdy okno zmienia rozmiar
    /// \param window odpowiedzialny za obsługę planszy (obsługę wyświetlania)
    /// \param offsetX wyśrodkowuje planszę po width
    /// \param offsetY wyśrodkowuje planszę po lenght
    void scaleBoard(sf::RenderWindow& window, float &offsetX, float &offsetY);

    /// Funkcja, która jest odpowiedzialna za wyświetlenie tekstu GameOver
    /// \param window odpowiedzialny za obsługę planszy (obsługę wyświetlania)
    /// \param gameOver odpowiedzialny za ustawienie tekstu GameOver
    void drawGameIsOver(sf::RenderWindow& window, sf::Text & gameOver) const;

    /// Funkcja, która jest odpowiedzialna za wyświetlenie tekstu TopScores
    /// \param window odpowiedzialny za obsługę planszy (obsługę wyświetlania)
    /// \param score odpowiedzialny za ustawienie tekstu score
    void drawTopScores(sf::RenderWindow& window, sf::Text & score) const;

    /// Funkcja, która jest odpowiedzialna za wyświetlenie tekstu Your Score
    /// \param window odpowiedzialny za obsługę planszy (obsługę wyświetlania)
    /// \param score odpowiedzialny za ustawienie tekstu youScore
    void drawYourScore(sf::RenderWindow& window, sf::Text & youScore) const;

    /// Funkcja odpowiedzialna za wyświetlanie 10 najlepszych wyników
    void drawScores(sf::RenderWindow& window, sf::Text & scores);

    void openScores(std::string & displayScores) const;

public:
    /// Konstruktor
    explicit  SNSFMLView(SnakeLogic & snake_logic);

    /// Funkcja wyświetla planszę
    void draw(sf::RenderWindow& window);

    /// Funkcja jest odpowiedzialna za wyświetlanie komunikaty po zakończeniu gry
    void drawGameOver(sf::RenderWindow & window);

    /// Funkcja pobiera titleSize, aby oddać do klasy MSSFMLController
    int getTileSize() const;

    /// Funkcje do wyświetlenia cyfr dla odliczenia startu gry
    void draw1(sf::RenderWindow& window) const;
    void draw2(sf::RenderWindow& window) const;
    void draw3(sf::RenderWindow& window) const;

};


#endif //SNAKE_AK_CZ16_286997_MSSFMLVIEW_H
