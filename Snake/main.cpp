#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

    const int tileSize = 20;
    const int width = 800 / tileSize;
    const int height = 600 / tileSize;

    std::srand(static_cast<unsigned>(time(0)));

    // Snake
    std::vector<sf::Vector2i> snake = { {10,10}, {9,10}, {8,10} };
    sf::Vector2i direction(1, 0);

    // Food
    sf::Vector2i food(rand() % width, rand() % height);

    sf::RectangleShape block(sf::Vector2f(tileSize, tileSize));
    sf::RectangleShape foodShape(sf::Vector2f(tileSize, tileSize));

    // ?? NORMAL COLORS
    block.setFillColor(sf::Color::Green);   // Snake
    foodShape.setFillColor(sf::Color::Red); // Food

    // FONT
    sf::Font font;
    font.loadFromFile("ChangaOne-Regular.ttf");

    // SCORE TEXT
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // GAME OVER TEXT
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(150, 250);
    gameOverText.setString("GAME OVER\nPress R to Restart");

    int score = 0;

    sf::Clock clock;
    float delay = 0.15f;

    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Restart
        if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            snake = { {10,10}, {9,10}, {8,10} };
            direction = { 1, 0 };
            food = { rand() % width, rand() % height };
            score = 0;
            gameOver = false;
        }

        if (!gameOver) {
            // Controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction.y == 0)
                direction = { 0, -1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction.y == 0)
                direction = { 0, 1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction.x == 0)
                direction = { -1, 0 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction.x == 0)
                direction = { 1, 0 };

            // Movement
            if (clock.getElapsedTime().asSeconds() > delay) {
                for (int i = snake.size() - 1; i > 0; i--) {
                    snake[i] = snake[i - 1];
                }

                snake[0] += direction;

                // Wall collision
                if (snake[0].x < 0 || snake[0].x >= width ||
                    snake[0].y < 0 || snake[0].y >= height) {
                    gameOver = true;
                }

                // Self collision
                for (int i = 1; i < snake.size(); i++) {
                    if (snake[0] == snake[i]) {
                        gameOver = true;
                    }
                }

                // Food collision
                if (snake[0] == food) {
                    snake.push_back(snake.back());
                    food = { rand() % width, rand() % height };
                    score++;
                }

                clock.restart();
            }
        }

        // Update score
        scoreText.setString("Score: " + std::to_string(score));

        // ?? DARK BACKGROUND
        window.clear(sf::Color(30, 30, 30));

        // Draw snake
        for (auto& segment : snake) {
            block.setPosition(segment.x * tileSize, segment.y * tileSize);
            window.draw(block);
        }

        // Draw food
        foodShape.setPosition(food.x * tileSize, food.y * tileSize);
        window.draw(foodShape);

        // Draw score
        window.draw(scoreText);

        // Draw game over
        if (gameOver) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}