

#include <iostream>
#include "SNSFMLView.h"

#include <fstream>

SNSFMLView:: SNSFMLView(SnakeLogic & logic) : logic(logic)
{
    loadTextures();
    if (!font.loadFromFile("PressStart2P-Regular.ttf"))
    {
        std::cerr << "Could not load font\n";
    }
    setupSprites();
}


int SNSFMLView::getTileSize() const
{
    return tileSize;
}

void SNSFMLView::draw1(sf::RenderWindow &window) const
{
    sf::Vector2u windowSize = window.getSize();
    sf::Text text;
    text.setFont(font);
    text.setString("1");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Blue);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    window.draw(text);
}

void SNSFMLView::draw2(sf::RenderWindow &window) const
{
    sf::Vector2u windowSize = window.getSize();
    sf::Text text;
    text.setFont(font);
    text.setString("2");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Blue);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    window.draw(text);
}

void SNSFMLView::draw3(sf::RenderWindow &window) const
{
    sf::Vector2u windowSize = window.getSize();
    sf::Text text;
    text.setFont(font);
    text.setString("3");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Blue);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    window.draw(text);
}


void SNSFMLView::draw(sf::RenderWindow & window)
{
    float offsetX = 0, offsetY = 0, x, y;
    char info;

    scaleBoard(window, offsetX, offsetY);

    for (int row = 0; row < boardHeight; ++row)
    {
        for (int col = 0; col < boardWidth; ++col)
        {
            x = col * tileSize + offsetX;
            y = row * tileSize + offsetY;

            info = logic.getFieldInfo(row, col);
            if (sprites.count(info))
            {
                    sf::Sprite sprite = sprites[info];
                    sprite.setPosition(x, y);
                    window.draw(sprite);
            }
        }
    }
}

void SNSFMLView::drawGameOver(sf::RenderWindow &window)
{
    score = logic.getScore();
    if(logic.getGameState() != RUNNING)
    {
        sf::Text gameOver;
        drawGameIsOver(window, gameOver);
        window.draw(gameOver);

        sf::Text score1;
        drawTopScores(window, score1);
        window.draw(score1);

        sf::Text yourScore;
        drawYourScore(window, yourScore);
        window.draw(yourScore);

        sf::Text scores;
        drawScores(window, scores);

    }
}

void SNSFMLView::loadTextures()
{
    std::vector<std::pair<char, std::string>> texture =
    {
        {' ', "grass.png"}, {'s', "snake.png"},
        {'f', "fruit.png"}, {'w', "wall.png"}, {'h', "snakeHead.png"}
    };

    for (auto& [key, filename] : texture)
    {
        sf::Texture tex;
        if (!tex.loadFromFile(filename))
        {
            std::cerr << "Failed to load " << filename << std::endl;
        }
        else
        {
            textures[key] = tex; // Jeżeli operacja w if się udaje to dla key zachowujemy obiekt tex
        }
    }
}

void SNSFMLView::setupSprites()
{
    sprites.clear(); // Funkcja do czyszczenia mapy

    for (auto& [key, tex] : textures)
    {
        sf::Sprite sprite;
        sprite.setTexture(tex);
        float scaleX = static_cast<float>(tileSize) / tex.getSize().x;
        float scaleY = static_cast<float>(tileSize) / tex.getSize().y;
        sprite.setScale(scaleX, scaleY);

        sprites[key] = sprite; // Asocjuje klucz z obiektem sprite
    }
}

void SNSFMLView::scaleBoard(sf::RenderWindow& window, float &offsetX, float &offsetY)
{
    sf::Vector2u winSize = window.getSize(); // Dostajemy rozmiar sfml screen (by def 800*600)
    // Potrzebne, gdy nasza plansza będzie za duża dla sfml screen

    float scaleX = static_cast<float>(winSize.x) / pixelWidth;
    float scaleY = static_cast<float>(winSize.y) / pixelHeight;
    scale = std::min(scaleX, scaleY); // Funkcja wybiera mniejszy wariant
    tileSize = static_cast<int>(tileSize * scale);
    setupSprites();

    // Robimy to po raz drugi, bo tileSize mógł się zmienić
    pixelWidth = boardWidth * tileSize;
    pixelHeight = boardHeight * tileSize;

    offsetX = (winSize.x - pixelWidth) / 2.0f;
    offsetY = ((winSize.y - pixelHeight) / 2.0f);
}

void SNSFMLView::drawGameIsOver(sf::RenderWindow &window, sf::Text & gameOver) const
{
    gameOver.setFont(font);
    gameOver.setString("Game over");
    gameOver.setCharacterSize(50);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = gameOver.getLocalBounds();
    int winWidth = window.getSize().x / 2;
    int winHeight = window.getSize().y / 20.f;
    int tWidth = winWidth - bounds.width / 2.f;
    gameOver.setPosition(tWidth, winHeight);
}

void SNSFMLView::drawTopScores(sf::RenderWindow &window, sf::Text &score) const
{
    score.setFont(font);
    score.setString("Top Scores:");
    score.setCharacterSize(50);
    score.setFillColor(sf::Color::Green);
    score.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = score.getLocalBounds();
    int winWidth = window.getSize().x / 2;
    int winHeight = window.getSize().y / 3.5f;
    int tWidth = winWidth - bounds.width / 2.f;
    score.setPosition(tWidth, winHeight);
}

void SNSFMLView::drawYourScore(sf::RenderWindow &window, sf::Text &youScore) const
{
    youScore.setFont(font);
    youScore.setString("Yours Score: " + std::to_string(score));
    youScore.setCharacterSize(50);
    youScore.setFillColor(sf::Color::Green);
    youScore.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = youScore.getLocalBounds();
    int winWidth = window.getSize().x / 2;
    int winHeight = window.getSize().y / 6.f;
    int tWidth = winWidth - bounds.width / 2.f;
    youScore.setPosition(tWidth, winHeight);
}

void SNSFMLView::drawScores(sf::RenderWindow &window, sf::Text &scores)
{
    std::string displayScores;
    openScores(displayScores);

    scores.setFont(font);
    scores.setString(displayScores);
    scores.setCharacterSize(35);
    scores.setFillColor(sf::Color::Blue);
    scores.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = scores.getLocalBounds();
    scores.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    scores.setPosition(window.getSize().x / 2.f, window.getSize().y / 1.4f);

    window.draw(scores);
}

void SNSFMLView::openScores(std::string & displayScores) const
{
    std::ifstream file("scores.txt");
    std::vector<int> scoreList;
    int s;

    while (file >> s)
        scoreList.push_back(s);
    file.close();

    std::sort(scoreList.begin(), scoreList.end(), std::greater<int>());

    for (size_t i = 0; i < std::min<size_t>(10, scoreList.size()); ++i)
    {
        if(i<9)
            displayScores += " " + std::to_string(i + 1) + ": " + std::to_string(scoreList[i]) + "\n";
        else
            displayScores +=  std::to_string(i + 1) + ": " + std::to_string(scoreList[i]) + "\n";
    }
}







