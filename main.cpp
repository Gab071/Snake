#include <iostream>
#include <SFML/Graphics.hpp>
#include <cassert>

#include "Menu.h"
#include "SnakeLogic.h"
#include "SNSFMLController.h"
#include "SNSFMLView.h"

void test1(SnakeLogic &logic);
void test2(SnakeLogic &logic);
void test3(SnakeLogic &logic);
void test4(SnakeLogic &logic);
void test5(SnakeLogic &logic);

int main()
{
    sf::RenderWindow menuWindow(sf::VideoMode({800, 600}), "Snake");
    Menu menu;
    menu.controlMenu(menuWindow);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    SnakeLogic logic(menu);
    SNSFMLView view(logic);
    SNSFMLController ctrl(logic, view);

    ctrl.play(window);

    return 0;
}

// Testy dla 1 konstruktora w SnakeLogic
void test1(SnakeLogic &logic)
{
    assert(logic.getBoardHeight() == 10);
    assert(logic.getBoardWidth() == 10);
    assert(logic.getGameState() == RUNNING);
    assert(logic.getCourse() == SOUTH);
}

// Test dla funkcji move
void test2(SnakeLogic &logic)
{
    assert(logic.getBoardHeight() == 10);
    assert(logic.getBoardWidth() == 10);
    assert(logic.getGameState() == RUNNING);
    assert(logic.getCourse() == SOUTH);
    assert(logic.getFieldInfo(5, 5) == 'h');
    // logic.moveSnake();
    assert(logic.getFieldInfo(6, 5) == 'h');
}

// Test dla funkcji move 2
void test3(SnakeLogic &logic)
{
    assert(logic.getBoardHeight() == 10);
    assert(logic.getBoardWidth() == 10);
    assert(logic.getGameState() == RUNNING);
    assert(logic.getCourse() == SOUTH);
    assert(logic.getFieldInfo(5, 5) == 'h');
    // logic.moveSnake();
    assert(logic.getFieldInfo(6, 5) == 'h');
    // logic.moveSnake();
    assert(logic.getFieldInfo(7, 5) == 'h');
    // logic.moveSnake();
    assert(logic.getFieldInfo(8, 5) == 'h');
}

// Test dla funkcji update
void test4(SnakeLogic &logic)
{
    assert(logic.getBoardHeight() == 10);
    assert(logic.getBoardWidth() == 10);
    assert(logic.getGameState() == RUNNING);
    assert(logic.getCourse() == SOUTH);
    assert(logic.getFieldInfo(5, 5) == 'h');
    assert(logic.getFieldInfo(6, 5) == 'f');
    logic.update();
    assert(logic.getFieldInfo(6, 5) == 'h');
    assert(logic.getFieldInfo(6, 5) != 'f');
    logic.update();
    assert(logic.getSnakeLength() == 4);
}

// Test dla funkcji turn
void test5(SnakeLogic &logic)
{
    assert(logic.getBoardHeight() == 10);
    assert(logic.getBoardWidth() == 10);
    assert(logic.getGameState() == RUNNING);
    assert(logic.getCourse() == SOUTH);
    assert(logic.getFieldInfo(5, 5) == 'h');
    // logic.turn();
    logic.update();
    assert(logic.getCourse() == EAST);
    assert(logic.getFieldInfo(5, 6) == 'h');
}
