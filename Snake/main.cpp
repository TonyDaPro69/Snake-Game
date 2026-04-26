#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
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

    sf::RectangleShape block(sf::Vector2f(tileSize, tileSize));
    sf::RectangleShape foodShape(sf::Vector2f(tileSize, tileSize));

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
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(150, 150);
    gameOverText.setString("GAME OVER");

    // ?? Highscore text
    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(sf::Color::White);

    // ?? Menu Button
    sf::RectangleShape menuButton(sf::Vector2f(250, 60));
    menuButton.setFillColor(sf::Color::Blue);
    menuButton.setPosition(275, 420);

    sf::Text menuButtonText;
    menuButtonText.setFont(font);
    menuButtonText.setString("Return to Menu");
    menuButtonText.setCharacterSize(24);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(300, 435);

    int score = 0;
    std::vector<int> highScores;

    sf::Clock clock;
    float delay = 0.15f;

    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // ?? Button click
            if (event.type == sf::Event::MouseButtonPressed) {
                if (gameOver) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (menuButton.getGlobalBounds().contains(mousePos)) {
                        // ?? LEAVE EMPTY (partner will implement menu)
                    }
                }
            }
        }

        if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            snake = { {10,10}, {9,10}, {8,10} };
            direction = { 1, 0 };
            food = { rand() % width, rand() % height };
            score = 0;
            gameOver = false;
        }

        if (!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction.y == 0)
                direction = { 0, -1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction.y == 0)
                direction = { 0, 1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction.x == 0)
                direction = { -1, 0 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction.x == 0)
                direction = { 1, 0 };

            if (clock.getElapsedTime().asSeconds() > delay) {
                for (int i = snake.size() - 1; i > 0; i--)
                    snake[i] = snake[i - 1];

                snake[0] += direction;

                // Collision
                if (snake[0].x < 0 || snake[0].x >= width ||
                    snake[0].y < 0 || snake[0].y >= height) {

                    gameOver = true;
                    highScores.push_back(score);
                }

                for (int i = 1; i < snake.size(); i++) {
                    if (snake[0] == snake[i]) {
                        gameOver = true;
                        highScores.push_back(score);
                    }
                }

                // Sort + keep top 5
                std::sort(highScores.begin(), highScores.end(), std::greater<int>());
                if (highScores.size() > 5)
                    highScores.resize(5);

                if (snake[0] == food) {
                    snake.push_back(snake.back());
                    food = { rand() % width, rand() % height };
                    score++;
                }

                clock.restart();
            }
        }

        scoreText.setString("Score: " + std::to_string(score));

        // ?? Highscore string
        std::string hs = "Top 5 Scores:\n";
        for (int i = 0; i < highScores.size(); i++)
            hs += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";

        highScoreText.setString(hs);

        // Center text
        sf::FloatRect bounds = highScoreText.getLocalBounds();
        highScoreText.setOrigin(bounds.width / 2, bounds.height / 2);
        highScoreText.setPosition(400, 300);

        window.clear(sf::Color(30, 30, 30));

        // Draw game
        if (!gameOver) {
            for (auto& segment : snake) {
                block.setPosition(segment.x * tileSize, segment.y * tileSize);
                window.draw(block);
            }

            foodShape.setPosition(food.x * tileSize, food.y * tileSize);
            window.draw(foodShape);

            window.draw(scoreText);
        }

        // Draw game over UI
        if (gameOver) {
            window.draw(gameOverText);
            window.draw(highScoreText);
            window.draw(menuButton);
            window.draw(menuButtonText);
        }

        window.display();
    }

    return 0;
}