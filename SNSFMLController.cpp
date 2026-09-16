

#include "SNSFMLController.h"

#include <fstream>
#include <iostream>


SNSFMLController::SNSFMLController(SnakeLogic &logic, SNSFMLView &view)
    : logic{logic}, view{view}, Triggered(false), is_gameOver(false), isGameStart(true)
{
    tileSize = view.getTileSize();
    course = logic.getCourse();
    turnSnake = logic.getTurn();
}

void SNSFMLController::play(sf::RenderWindow &window)
{
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    sf::Clock clockGameStart;
    sf::Clock clock;
    sf::Clock gameOverClock;

    bool save = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            Events(window, event);
        }

        if(clock.getElapsedTime().asSeconds() >= logic.getTime() && !isGameStart)
        {
            logic.update();
            clock.restart();
        }
            clockStart(gameOverClock);

        window.clear();
        drawAll(window, save, clockGameStart);
        window.display();
    }
}

void SNSFMLController::keyClick(sf::Event &event)
{
    if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
    {
        keyW();
    }
    if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
    {
        keyS();
    }
    if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
    {
        keyA();
    }
    if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
    {
        keyD();
    }
}

void SNSFMLController::keyW()
{
    if(course == EAST)
    {
        turnSnake = LEFT;
        logic.turn(turnSnake);
    }

    else if(course == WEST)
    {
        turnSnake = RIGHT;
        logic.turn(turnSnake);
    }
    course = logic.getCourse();
}

void SNSFMLController::keyA()
{
    if(course == NORTH)
    {
        turnSnake = LEFT;
        logic.turn(turnSnake);
    }

    else if(course == SOUTH)
    {
        turnSnake = RIGHT;
        logic.turn(turnSnake);
    }
    course = logic.getCourse();
}

void SNSFMLController::keyS()
{
    if(course == EAST)
    {
        turnSnake = RIGHT;
        logic.turn(turnSnake);
    }

    else if(course == WEST)
    {
        turnSnake = LEFT;
        logic.turn(turnSnake);
    }
    course = logic.getCourse();
}

void SNSFMLController::keyD()
{
    if(course == NORTH)
    {
        turnSnake = RIGHT;
        logic.turn(turnSnake);
    }

    else if(course == SOUTH)
    {
        turnSnake = LEFT;
        logic.turn(turnSnake);
    }
    course = logic.getCourse();
}

void SNSFMLController::drawAll(sf::RenderWindow &window, bool &save, sf::Clock & clockGameStart)
{
    if(isGameStart)
    {
        gameStart(window, clockGameStart);
    }

    if(!is_gameOver && !isGameStart)
        view.draw(window);

    if(save && is_gameOver)
    {
        logic.SaveScores();
        save = false;
    }

    if(is_gameOver)
        view.drawGameOver(window);
}

void SNSFMLController::Events(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        window.close();
    if (event.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }
    if (event.type == sf::Event::KeyPressed)
    {
        keyClick(event);
    }
}

void SNSFMLController::clockStart(sf::Clock &clock)
{
    if (logic.getGameState() != RUNNING && !Triggered)
    {
        clock.restart();
        Triggered = true;
    }

    if (Triggered && clock.getElapsedTime().asSeconds() >= 2.f)
    {
        is_gameOver = true;
    }
}

void SNSFMLController::gameStart(sf::RenderWindow &window, sf::Clock &clockStart)
{
    if(clockStart.getElapsedTime().asSeconds() < 1.f)
        view.draw3(window);

    else if(clockStart.getElapsedTime().asSeconds() < 2.f)
        view.draw2(window);

    else if(clockStart.getElapsedTime().asSeconds() < 3.f)
        view.draw1(window);

    else
        isGameStart = false;
}


