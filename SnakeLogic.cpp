
#include "SnakeLogic.h"

#include <fstream>
#include <iostream>
#include <iomanip>

SnakeLogic::SnakeLogic(Menu & menu)
: menu(menu),
course(SOUTH), state(RUNNING), turnSnake(LEFT), mode(CLOSE),
isFruit(false), fruitAte(0), timeIs(1), timeSurvived(0), score{0},
boardDimensions({10, 10}),
snakeHead({5,5}),
fruit({2, 6})
{
    srand(time(nullptr));

    snake.push_back(snakeHead);
    snake.push_back({5,4});
    snake.push_back({5,3});

    sLength = snake.size();

    checkForErrors();
    setMode();
}

void SnakeLogic::checkForErrors() const
{
    for(auto const & pos : snake)
    {
        if(pos.x < 1 || pos.y < 1)
            std::exit(10);

        if(pos.x >= boardDimensions.x || pos.y >= boardDimensions.y)
            std::exit(10);

        if(pos.x == fruit.x && pos.y == fruit.y)
            std::exit(10);
    }
    if(fruit.x < 1 || fruit.y < 1)
        std::exit(10);

    if(fruit.x >= boardDimensions.x || fruit.y >= boardDimensions.y)
        std::exit(10);

}

bool SnakeLogic::outBoard(const int row, const int col) const
{
    if(row > boardDimensions.y || col > boardDimensions.x)
        return true;

    if(row < 0 || col < 0)
        return true;

    return false;
}

// Funkcja przeszukuje całego snake'a, w tym i głowę
bool SnakeLogic::isSnake(const int row, const int col) const
{
    if(outBoard(row, col))
        return false;

    return std::any_of(snake.begin(), snake.end(), [row, col](SnakePos pos)
        { return pos.y == row && pos.x == col; });
}

bool SnakeLogic::isSnakeHead(const int row, const int col) const
{
    if(outBoard(row, col))
        return false;

    if(snake[0].x == col && snake[0].y == row)
        return true;

    return false;
}

bool SnakeLogic::is_Fruit(const int row, const int col) const
{
    if(outBoard(row, col))
        return false;

    if(fruit.x == col && fruit.y == row)
        return true;

    return false;
}

bool SnakeLogic::isWall(const int row, const int col) const
{
    if(outBoard(row, col))
        return false;

    if(row == 0 || col == 0)
        return true;
    // Tutaj (-1) bo sprawdza po indeksach
    if(row == boardDimensions.y - 1 || col == boardDimensions.x - 1)
        return true;

    return false;
}


void SnakeLogic::debug_display() const
{
    for (int ncol = 0; ncol < boardDimensions.y; ncol++)
    {
        if(ncol == 0)
            std::cout << std::setw(4) << ncol;

        else
        std::cout << std::setw(3) << ncol;
    }
    std::cout << std::endl;

    for (int nrow = 0; nrow < boardDimensions.x; nrow++)
    {
        std::cout << nrow;
        for (int ncol = 0; ncol < boardDimensions.y; ncol++)
        {
            checkForSnake(nrow, ncol);
        }
        std::cout << std::endl;
    }
}

void SnakeLogic::checkForSnake(int nrow, int ncol) const
{

    bool isSnake = false;
    bool isHead = false;
    for(int pos = 0; pos < snake.size(); pos++)
    {
        if(nrow == snake[pos].y && ncol == snake[pos].x)
        {
            if(pos == 0)
                isHead = true;
            else
                isSnake = true;
        }
    }
    if(isHead)
        std::cout << std::setw(3) << "G";

    else if(isSnake)
        std::cout << std::setw(3) << "o";

    else
        std::cout << std::setw(3) << ".";
}

int SnakeLogic::getBoardWidth() const
{
    return boardDimensions.x;
}

int SnakeLogic::getBoardHeight() const
{
    return boardDimensions.y;
}

int SnakeLogic::getSnakeLength() const
{
    return sLength;
}

int SnakeLogic::getFruitAte() const
{
    return fruitAte;
}

float SnakeLogic::getTime() const
{
    return timeIs;
}

int SnakeLogic::getScore() const
{
    return score;
}

GameState SnakeLogic::getGameState() const
{
    return state;
}

Course SnakeLogic::getCourse() const
{
    return course;
}

Turn SnakeLogic::getTurn() const
{
    return turnSnake;
}

void SnakeLogic::moveSnake()
{
    if(state == FINISHED)
        return;

    if(course == NORTH)
        moveNorth();

    else if(course == SOUTH)
        moveSouth();

    else if(course == EAST)
        moveEast();

    else if(course == WEST)
        moveWest();

    isFruit = false;
}

void SnakeLogic::moveSnakeBy(const int dx, const int dy)
{
    SnakePos newHead = snakeHead;
    newHead.x += dx;
    newHead.y += dy;

    if (std::find(snake.begin(), snake.end(), newHead) != snake.end())
    {
        state = FINISHED;
        return;
    }

    snakeHead = newHead;
    snake.emplace(snake.begin(), snakeHead);

    if(!isFruit)
        snake.pop_back();

    sLength = snake.size();
}

void SnakeLogic::moveNorth()
{
    moveSnakeBy(0, -1);
}

void SnakeLogic::moveSouth()
{
    moveSnakeBy(0, 1);
}

void SnakeLogic::moveEast()
{
    moveSnakeBy(1, 0);
}

void SnakeLogic::moveWest()
{
    moveSnakeBy(-1, 0);
}

bool SnakeLogic::checkFruit()
{
    if(fruit.y == snakeHead.y && fruit.x == snakeHead.x)
    {
        placeFruit();
        fruitAte++;
        return true;
    }
        return false;
}

void SnakeLogic::placeFruit()
{
    while(true)
    {
        SnakePos placedFruit{
            // -2, bo raz odejmujemy 1, bo rozpoczynamy od indeksu 0, po raz drugi odejmujemy 1 bo ściana jest na końcu
            std::rand() % (boardDimensions.x - 2) + 1,
            std::rand() % (boardDimensions.y - 2) + 1
        };

        if(std::find(snake.begin(), snake.end(), placedFruit) == snake.end())
        {
            fruit = placedFruit;
            break;
        }
    }
}

void SnakeLogic::checkCollision()
{
    if(snakeHead.x <= 0 || snakeHead.y <= 0)
        state = FINISHED;

    if(snakeHead.x >= (boardDimensions.x - 1) || snakeHead.y >= (boardDimensions.y-1))
        state = FINISHED;
}

char SnakeLogic::getFieldInfo(int row, int col) const
{
    if(outBoard(row, col))
        return '#';

    if(is_Fruit(row, col))
        return 'f';

    if(isSnakeHead(row, col))
        return 'h';

    if(isSnake(row, col))
        return 's';

    if(isWall(row, col))
        return 'w';

    return ' ';
}

void SnakeLogic::update()
{
    moveSnake();
    isFruit = checkFruit();
    checkCollision();

  timeSurvived += timeIs;
    if(state == RUNNING)
        score = fruitAte*10 + timeSurvived;

}

void SnakeLogic::turn(Turn & snakeTurn)
{
    if(state == FINISHED)
        return;

    if(snakeTurn == RIGHT)
        turnRight();

    else if(snakeTurn == LEFT)
        turnLeft();

}

void SnakeLogic::SaveScores() const
{
    if (state != RUNNING)
    {
        std::ofstream file("scores.txt", std::ios::app);
        if (file)
            file << score << std::endl;
        else
            std::cerr << "Unable to open file" << std::endl;

        file.close();
    }
}

void SnakeLogic::turnLeft()
{
    if(course == NORTH)
        course = WEST;

    else if(course == WEST)
        course = SOUTH;

    else if(course == SOUTH)
        course = EAST;

    else if(course == EAST)
        course = NORTH;
}

void SnakeLogic::turnRight()
{
    if(course == NORTH)
        course = EAST;

    else if(course == EAST)
        course = SOUTH;

    else if(course == SOUTH)
        course = WEST;

    else if(course == WEST)
        course = NORTH;
}

void SnakeLogic::setMode()
{
    mode = menu.getGameMode();
    if(mode == EASY)
        timeIs = 0.8;

    else if(mode == NORMAL)
        timeIs = 0.6;

    else if(mode == HARD)
        timeIs = 0.4;
}



