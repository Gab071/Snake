
#ifndef SNAKE_AK_CZ16_286997_SNAKECONTROL_H
#define SNAKE_AK_CZ16_286997_SNAKECONTROL_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Menu.h"


enum Course {NORTH, SOUTH, EAST, WEST};
enum Turn {LEFT, RIGHT};
enum GameState {RUNNING, FINISHED};

struct SnakePos {
    int x;
    int y;
    bool operator==(const SnakePos & check) const
    {
        return x == check.x && y == check.y;
    }
};

class SnakeLogic{

    Menu & menu;

    Course course;
    GameState state;
    Turn turnSnake;
    GameMode mode;

    bool isFruit;
    int sLength;
    int fruitAte;
    float timeIs;
    float timeSurvived;
    int score;

    SnakePos boardDimensions;
    SnakePos snakeHead;
    std::vector<SnakePos> snake;
    SnakePos fruit;

    /// Funkcja, która sprawdza dla funkcji debug_display gdzie jest snakeHead i snake (ciało snake)
    /// \param nrow - aktualny wiersz boardDimensions
    /// \param ncol - aktualna kolumna boardDimensions
    void checkForSnake(int nrow, int ncol) const;

    /// Funkcja porusza węża
    /// w kierunku do góry
    void moveNorth();

    /// Funkcja porusza węża
    /// w kierunku do dołu
    void moveSouth();

    /// Funkcja porusza węża
    /// w kierunku w prawo
    void moveEast();

    /// Funkcja porusza węża
    /// w kierunku w lewo
    void moveWest();

    /// Funkcja zgaduje i łoży fruit na planszy
    void placeFruit();

    /// Funkcja sprawdza, czy wszystko prawidłowo jest ustawione w konstruktorze
    void checkForErrors() const;

    /// Funkcja sprawdza, czy row oraz col nie wychodzą za granicę planszy
    /// \param row
    /// \param col
    /// \return
    bool outBoard(const int row, const int col) const;

    /// Funkcja sprawdza, czy pole row, col zawiera snake'a
    /// \param col - kolumna
    /// \param row - wiersz
    /// \return - zwraca prawdę, jeśli pozycja row, col posiada snake'a
    bool isSnake(const int row, const int col) const;

    /// Funkcja sprawdza, czy pole row, col zawiera głowę snake'a
    /// \param col - kolumna
    /// \param row - wiersz
    /// \return - zwraca prawdę, jeśli pozycja row, col posiada głowę snake'a
    bool isSnakeHead(const int row, const int col) const;

    bool is_Fruit(const int row, const int col) const;

    /// Funkcja sprawdza, czy pole row, col zawiera ścianę
    /// \param col - kolumna
    /// \param row - wiersz
    /// \return - zwraca prawdę, jeśli pozycja row, col posiada ścianę
    bool isWall(const int row, const int col) const;

    /// Funkcja sprawdza, czy snake nie zderzył się z granicami planszy
    /// \return - czy zaszła kolizja
    void checkCollision();

    /// Funkcja, która porusza snake'a,
    /// sprawdza, w którą stronę ma go poruszyć
    void moveSnake();

    /// Funkcja, która porusza snake'a w odpowiednim kierunku
    void moveSnakeBy(const int dx, const int dy);

    /// Funkcja sprawdza, czy snake zjadł owoc
    /// \return - czy pole posiada fruit
    bool checkFruit();

    /// Funkcja zmienia kierunek snake'a
    /// przy argumencie turnSnake LEFT
    void turnLeft();

    /// Funkcja zmienia kierunek snake'a
    /// przy argumencie turnSnake RIGHT
    void turnRight();

    /// Funkcja, która ustawia odpowiedni poziom trundości
    void setMode();

public:
    /// Konstruktor
    SnakeLogic(Menu & menu);

    /// Funkcja testowa, która wyświetla snake'a na board
    void debug_display() const;

    /// Proste gettery
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getSnakeLength() const;
    int getFruitAte() const;
    float getTime() const;
    int getScore() const;

    /// Funkcja zwraca aktualny stan rozgrywki
    /// RUNNING - rozgrywka jeszcze się toczy
    /// FINISHED - rozgrywka dobiegła końca (przyczyną może być kolizja)
    GameState getGameState() const;

    /// Funkcja zwraca aktualny kierunek snake'a (widok z lotu ptaka)
    /// NORTH, do góry
    /// EAST, w prawo
    /// SOUTH, do dołu
    /// WEST, w lewo
    Course getCourse() const;

    /// Funkcja zwraca pole snakeTurn, które było zainicjalizowane w konstruktorze
    Turn getTurn() const;

    /// Funkcja zwraca odpowiedni char:
    /// \param row - wiersz
    /// \param col - kolumna
    /// \return :
    /// Jeśli głowa snake'a - 'h'
    /// Jeśli snake - 's'
    /// Jeśli owoc - 'f'
    /// Jeśli outBoard - '#'
    /// Jeśli ściana - 'w'
    /// Jeśli zwykłe pole - ' '
    char getFieldInfo(int row, int col) const;

    /// Zbiór funkcji moveSnake, updateState, checkFruit
    /// które kolaborują ze sobą i odpowiednio poruszają snake'a
    void update();

    /// Funkcja zawraca snake'a (w lewo lub w prawo)
    void turn(Turn & snakeTurn);

    /// Funkcja wczytuje scores
    void SaveScores() const;

};


#endif //SNAKE_AK_CZ16_286997_SNAKECONTROL_H