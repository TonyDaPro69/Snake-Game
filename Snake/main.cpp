#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Menu.h"
#include <algorithm>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

    const int tileSize = 20;
    const int width = 800 / tileSize;
    const int height = 600 / tileSize;

    std::srand(static_cast<unsigned>(time(0)));

    std::vector<sf::Vector2i> snake = { {10,10}, {9,10}, {8,10} };
    sf::Vector2i direction(1, 0);

    sf::Vector2i food(rand() % width, rand() % height);

    sf::RectangleShape block(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
    sf::RectangleShape foodShape(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));

    block.setFillColor(sf::Color::Green);
    foodShape.setFillColor(sf::Color::Red);

    sf::Font font;
    font.loadFromFile("ChangaOne-Regular.ttf");

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color(255, 215, 0));
    gameOverText.setPosition(210.f, 130.f);
    gameOverText.setString("GAME OVER");

    // GAME OVER PANEL
    sf::RectangleShape gameOverPanel(sf::Vector2f(500.f, 380.f));
    gameOverPanel.setFillColor(sf::Color(20, 20, 40, 220));
    gameOverPanel.setOutlineThickness(4.f);
    gameOverPanel.setOutlineColor(sf::Color(255, 215, 0));
    gameOverPanel.setPosition(150.f, 100.f);

    // Highscore text
    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(sf::Color::White);

    // Return to Menu Button
    sf::RectangleShape menuButton(sf::Vector2f(250.f, 60.f));
    menuButton.setFillColor(sf::Color(255, 215, 0));
    menuButton.setPosition(275.f, 330.f);

    sf::Text menuButtonText;
    menuButtonText.setFont(font);
    menuButtonText.setString("Return to Menu");
    menuButtonText.setCharacterSize(24);
    menuButtonText.setFillColor(sf::Color::Black);
    menuButtonText.setPosition(295.f, 345.f);

    // Exit Game Button
    sf::RectangleShape exitButton(sf::Vector2f(250.f, 60.f));
    exitButton.setFillColor(sf::Color(255, 215, 0));
    exitButton.setPosition(275.f, 405.f);

    sf::Text exitButtonText;
    exitButtonText.setFont(font);
    exitButtonText.setString("Exit Game");
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::Black);
    exitButtonText.setPosition(335.f, 420.f);

    int score = 0;
    std::vector<int> highScores;

    sf::Clock clock;
    float delay = 0.15f;

    bool gameOver = false;
    bool showMenu = true;

    Menu menu(800.f, 600.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (showMenu && event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W)
                    menu.moveUp();

                if (event.key.code == sf::Keyboard::S)
                    menu.moveDown();

                if (event.key.code == sf::Keyboard::Enter) {
                    if (menu.getSelectedIndex() == 0) {
                        showMenu = false;

                        snake = { {10,10}, {9,10}, {8,10} };
                        direction = { 1, 0 };
                        food = { rand() % width, rand() % height };
                        score = 0;
                        gameOver = false;

                        if (menu.getDifficulty() == "Easy")
                            delay = 0.20f;
                        if (menu.getDifficulty() == "Medium")
                            delay = 0.15f;
                        if (menu.getDifficulty() == "Hard")
                            delay = 0.10f;

                        clock.restart();
                    }

                    if (menu.getSelectedIndex() == 1) {
                        menu.nextDifficulty();
                    }

                    if (menu.getSelectedIndex() == 2) {
                        window.close();
                    }
                }
            }

            // Button click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (!showMenu && gameOver) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (menuButton.getGlobalBounds().contains(mousePos)) {
                        showMenu = true;
                        gameOver = false;
                    }

                    if (exitButton.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }
            }
        }

        // Restart
        if (!showMenu && gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            snake = { {10,10}, {9,10}, {8,10} };
            direction = { 1, 0 };
            food = { rand() % width, rand() % height };
            score = 0;
            gameOver = false;

            if (menu.getDifficulty() == "Easy")
                delay = 0.15f;
            if (menu.getDifficulty() == "Medium")
                delay = 0.10f;
            if (menu.getDifficulty() == "Hard")
                delay = 0.07f;

            clock.restart();
        }

        if (!showMenu && !gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction.y == 0)
                direction = { 0, -1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction.y == 0)
                direction = { 0, 1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction.x == 0)
                direction = { -1, 0 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction.x == 0)
                direction = { 1, 0 };

            if (clock.getElapsedTime().asSeconds() > delay) {
                for (int i = static_cast<int>(snake.size()) - 1; i > 0; i--) {
                    snake[i] = snake[i - 1];
                }

                snake[0] += direction;

                // Collision
                if (snake[0].x < 0 || snake[0].x >= width ||
                    snake[0].y < 0 || snake[0].y >= height) {
                    gameOver = true;
                    highScores.push_back(score);
                }

                // Self collision
                for (int i = 1; i < static_cast<int>(snake.size()); i++) {
                    if (snake[0] == snake[i]) {
                        gameOver = true;
                        highScores.push_back(score);
                    }
                }

                // Sort + keep top 5
                std::sort(highScores.begin(), highScores.end(), std::greater<int>());
                if (highScores.size() > 5)
                    highScores.resize(5);

                //updating the speed
                if (snake[0] == food) {
                    snake.push_back(snake.back());
                    food = { rand() % width, rand() % height };
                    score++;

                    std::cout << "Food eaten | Score: " << score
                        << " | Delay: " << delay << std::endl;

                    delay -= 0.01f;
                    if (delay < 0.03f)
                        delay = 0.03f;
                }

                clock.restart();
            }
        }

        scoreText.setString("Score: " + std::to_string(score));

        // Highscore string
        std::string hs = "Top 5 Scores:\n";
        for (int i = 0; i < static_cast<int>(highScores.size()); i++)
            hs += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";

        highScoreText.setString(hs);

        // Center text
        sf::FloatRect bounds = highScoreText.getLocalBounds();
        highScoreText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        highScoreText.setPosition(400.f, 250.f);

        window.clear(sf::Color(30, 30, 30));

        if (showMenu) {
            menu.draw(window);
        }
        else {
            // Draw game
            if (!gameOver) {
                for (auto& segment : snake) {
                    block.setPosition(static_cast<float>(segment.x * tileSize), static_cast<float>(segment.y * tileSize));
                    window.draw(block);
                }

                foodShape.setPosition(static_cast<float>(food.x * tileSize), static_cast<float>(food.y * tileSize));
                window.draw(foodShape);

                window.draw(scoreText);
            }

            // Draw game over UI
            if (gameOver) {
                window.draw(gameOverPanel);
                window.draw(gameOverText);
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