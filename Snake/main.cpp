#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");

    const int tileSize = 20;

    // Snake body (list of positions)
    std::vector<sf::Vector2i> snake = { {10,10}, {9,10}, {8,10} };

    sf::Vector2i direction(1, 0);

    sf::RectangleShape block(sf::Vector2f(tileSize, tileSize));
    block.setFillColor(sf::Color::Green);

    sf::Clock clock;
    float delay = 0.15f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && direction.y == 0)
            direction = { 0, -1 };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && direction.y == 0)
            direction = { 0, 1 };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && direction.x == 0)
            direction = { -1, 0 };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && direction.x == 0)
            direction = { 1, 0 };

        // Movement timing
        if (clock.getElapsedTime().asSeconds() > delay) {
            // move body (follow the head)
            for (int i = snake.size() - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }

            // move head
            snake[0] += direction;

            clock.restart();
        }

        // Draw
        window.clear();

        for (auto& segment : snake) {
            block.setPosition(segment.x * tileSize, segment.y * tileSize);
            window.draw(block);
        }

        window.display();
    }

    return 0;
}