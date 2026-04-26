#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Menu.h"
#include <algorithm>

bool farFrom(const sf::Vector2i& a, const sf::Vector2i& b, int d) {
    return abs(a.x - b.x) > d || abs(a.y - b.y) > d;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

    const int tileSize = 20;
    const int width = 800 / tileSize;
    const int height = 600 / tileSize;

    std::srand(static_cast<unsigned>(time(0)));

    std::vector<sf::Vector2i> snake = { {10,10}, {9,10}, {8,10} };
    sf::Vector2i direction(1, 0);

    std::vector<sf::Vector2i> walls;
    sf::Vector2i food;

    sf::RectangleShape block(sf::Vector2f(tileSize, tileSize));
    sf::RectangleShape foodShape(sf::Vector2f(tileSize, tileSize));
    foodShape.setFillColor(sf::Color::Red);

    sf::Font font;
    font.loadFromFile("ChangaOne-Regular.ttf");

    sf::Text scoreText("Score: 0", font, 30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text gameOverText("GAME OVER", font, 40);
    gameOverText.setFillColor(sf::Color(255, 215, 0));
    gameOverText.setPosition(295, 130);

    sf::Text instructionsForR("Press R\nto restart\nsame level", font, 18);
    instructionsForR.setFillColor(sf::Color(200, 200, 200));
    instructionsForR.setPosition(220, 220);

    sf::RectangleShape gameOverPanel(sf::Vector2f(500, 380));
    gameOverPanel.setFillColor(sf::Color(20, 20, 40, 220));
    gameOverPanel.setOutlineThickness(4);
    gameOverPanel.setOutlineColor(sf::Color(255, 215, 0));
    gameOverPanel.setPosition(150, 100);

    sf::Text highScoreText("", font, 25);
    highScoreText.setFillColor(sf::Color::White);

    sf::RectangleShape menuButton(sf::Vector2f(210, 50));
    menuButton.setFillColor(sf::Color(255, 215, 0));
    menuButton.setPosition(295, 343);

    sf::Text menuButtonText("Return to Menu", font, 25);
    menuButtonText.setFillColor(sf::Color::Black);
    menuButtonText.setPosition(310, 350);

    sf::RectangleShape exitButton(sf::Vector2f(210, 50));
    exitButton.setFillColor(sf::Color(255, 215, 0));
    exitButton.setPosition(295, 407);

    sf::Text exitButtonText("Exit Game", font, 25);
    exitButtonText.setFillColor(sf::Color::Black);
    exitButtonText.setPosition(340, 415);

    // HOW TO PLAY
    sf::Text howTitle("HOW TO PLAY", font, 45);
    howTitle.setFillColor(sf::Color(255, 215, 0));
    howTitle.setPosition(240, 130);

    sf::Text howText(
        "Use W A S D to move\n\n"
        "Collect food to grow\n\n"
        "Avoid walls and yourself",
        font, 24);
    howText.setFillColor(sf::Color::White);
    howText.setPosition(200, 230);

    sf::RectangleShape howBack(sf::Vector2f(210, 50));
    howBack.setFillColor(sf::Color(255, 215, 0));
    howBack.setPosition(295, 405);

    sf::Text howBackText("Back to Menu", font, 25);
    howBackText.setFillColor(sf::Color::Black);
    howBackText.setPosition(310, 415);

    int score = 0;
    std::vector<int> highScores;

    sf::Clock clock;
    float delay = 0.15f;

    bool gameOver = false;
    bool showMenu = true;
    bool showHowToPlay = false;

    Menu menu(800.f, 600.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // MENU INPUT
            if (showMenu && event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) menu.moveUp();
                if (event.key.code == sf::Keyboard::S) menu.moveDown();

                if (event.key.code == sf::Keyboard::Enter) {

                    if (menu.getSelectedIndex() == 0) {
                        showMenu = false;
                        showHowToPlay = false;

                        snake = { {10,10},{9,10},{8,10} };
                        direction = { 1,0 };
                        score = 0;
                        gameOver = false;
                        walls.clear();

                        bool ok = false;
                        while (!ok) {
                            food = { rand() % width, rand() % height };
                            if (farFrom(food, snake[0], 5)) ok = true;
                        }

                        if (menu.getDifficulty() == "Easy") delay = 0.20f;
                        if (menu.getDifficulty() == "Medium") delay = 0.15f;
                        if (menu.getDifficulty() == "Hard") delay = 0.10f;

                        clock.restart();
                    }

                    if (menu.getSelectedIndex() == 1)
                        menu.nextDifficulty();

                    if (menu.getSelectedIndex() == 2) {
                        showMenu = false;
                        showHowToPlay = true;
                    }

                    if (menu.getSelectedIndex() == 3)
                        window.close();
                }
            }

            // MOUSE
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (!showMenu && gameOver) {
                    if (menuButton.getGlobalBounds().contains(mouse)) {
                        showMenu = true;
                        gameOver = false;
                    }
                    if (exitButton.getGlobalBounds().contains(mouse))
                        window.close();
                }

                if (showHowToPlay) {
                    if (howBack.getGlobalBounds().contains(mouse)) {
                        showMenu = true;
                        showHowToPlay = false;
                    }
                }
            }
        }

        // RESTART
        if (!showMenu && !showHowToPlay && gameOver &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

            snake = { {10,10},{9,10},{8,10} };
            direction = { 1,0 };
            score = 0;
            gameOver = false;
            walls.clear();
        }

        // GAME LOGIC
        if (!showMenu && !showHowToPlay && !gameOver) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction.y == 0) direction = { 0,-1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction.y == 0) direction = { 0,1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction.x == 0) direction = { -1,0 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction.x == 0) direction = { 1,0 };

            if (clock.getElapsedTime().asSeconds() > delay) {

                for (int i = snake.size() - 1;i > 0;i--)
                    snake[i] = snake[i - 1];

                snake[0] += direction;

                bool justDied = false;

                if (snake[0].x < 0 || snake[0].x >= width ||
                    snake[0].y < 0 || snake[0].y >= height)
                    justDied = true;

                for (int i = 1;i < snake.size();i++)
                    if (snake[0] == snake[i]) justDied = true;

                for (auto& w : walls)
                    if (snake[0] == w) justDied = true;

                if (justDied) {
                    gameOver = true;
                    highScores.push_back(score);

                    std::sort(highScores.begin(), highScores.end(), std::greater<int>());
                    if (highScores.size() > 5)
                        highScores.resize(5);
                }

                if (snake[0] == food) {
                    snake.push_back(snake.back());
                    score++;

                    bool ok = false;
                    while (!ok) {
                        food = { rand() % width,rand() % height };
                        if (farFrom(food, snake[0], 5)) ok = true;
                    }

                    if (menu.getDifficulty() == "Hard") {
                        walls.clear();
                        int len = rand() % 3 + 5;

                        sf::Vector2i cur = food + sf::Vector2i(5, 5);

                        for (int i = 0;i < len;i++) {
                            cur.x = std::max(0, std::min(width - 1, cur.x));
                            cur.y = std::max(0, std::min(height - 1, cur.y));

                            walls.push_back(cur);

                            int d = rand() % 4;
                            if (d == 0) cur.x++;
                            if (d == 1) cur.x--;
                            if (d == 2) cur.y++;
                            if (d == 3) cur.y--;
                        }
                    }
                }

                clock.restart();
            }
        }

        scoreText.setString("Score: " + std::to_string(score));

        std::string hs = "Top 5:\n";
        for (int i = 0;i < highScores.size();i++)
            hs += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";

        highScoreText.setString(hs);
        highScoreText.setPosition(365, 175);

        window.clear(sf::Color(30, 30, 30));

        if (showMenu) menu.draw(window);
        else if (showHowToPlay) {
            window.draw(gameOverPanel);
            window.draw(howTitle);
            window.draw(howText);
            window.draw(howBack);
            window.draw(howBackText);
        }
        else {
            block.setFillColor(sf::Color::Green);
            for (auto& s : snake) {
                block.setPosition(s.x * tileSize, s.y * tileSize);
                window.draw(block);
            }

            block.setFillColor(sf::Color(150, 150, 150));
            for (auto& w : walls) {
                block.setPosition(w.x * tileSize, w.y * tileSize);
                window.draw(block);
            }

            foodShape.setPosition(food.x * tileSize, food.y * tileSize);
            window.draw(foodShape);

            window.draw(scoreText);

            if (gameOver) {
                window.draw(gameOverPanel);
                window.draw(gameOverText);
                window.draw(instructionsForR);
                window.draw(highScoreText);
                window.draw(menuButton);
                window.draw(menuButtonText);
                window.draw(exitButton);
                window.draw(exitButtonText);
            }
        }

        window.display();
    }

    return 0;
}