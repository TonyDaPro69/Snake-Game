#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Menu {
private:
    static const int itemCount = 4;
    sf::Text items[itemCount];
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text helpText;
    sf::Font font;
    sf::RectangleShape panel;
    int selectedIndex;
    std::string difficulty;

public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();

    int getSelectedIndex() const;
    std::string getDifficulty() const;
    void nextDifficulty();
};