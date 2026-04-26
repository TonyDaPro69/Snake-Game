#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    selectedIndex = 0;
    difficulty = "Easy";

    if (!font.loadFromFile("ChangaOne-Regular.ttf")) {
        std::cout << "Font failed to load\n";
    }

    // Background panel
    panel.setSize(sf::Vector2f(500.f, 380.f));
    panel.setFillColor(sf::Color(20, 20, 40, 220));
    panel.setOutlineThickness(4.f);
    panel.setOutlineColor(sf::Color(255, 215, 0));
    panel.setPosition(width / 2.f - 250.f, 100.f);

    // Title
    titleText.setFont(font);
    titleText.setString("SNAKE GAME");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color(255, 255, 255));
    titleText.setPosition(width / 2.f - 170.f, 120.f);

    // Subtitle
    subtitleText.setFont(font);
    //subtitleText.setString("Classic Arcade Mode");
    subtitleText.setCharacterSize(24);
    subtitleText.setFillColor(sf::Color(180, 220, 255));
    subtitleText.setPosition(width / 2.f - 120.f, 190.f);

    // Menu item 1
    items[0].setFont(font);
    items[0].setString("> Start Game");
    items[0].setCharacterSize(38);
    items[0].setFillColor(sf::Color(255, 215, 0));
    items[0].setPosition(width / 2.f - 130.f, 270.f);

    // Menu item 2
    items[1].setFont(font);
    items[1].setString("Difficulty: " + difficulty);
    items[1].setCharacterSize(38);
    items[1].setFillColor(sf::Color::White);
    items[1].setPosition(width / 2.f - 120.f, 330.f);

    // Menu item 3
    items[2].setFont(font);
    items[2].setString("Exit");
    items[2].setCharacterSize(38);
    items[2].setFillColor(sf::Color::White);
    items[2].setPosition(width / 2.f - 120.f, 390.f);

    // Help text
    helpText.setFont(font);
    helpText.setString("Use W / S to move   ENTER to select");
    helpText.setCharacterSize(20);
    helpText.setFillColor(sf::Color(210, 210, 210));
    helpText.setPosition(width / 2.f - 130.f, 450.f);
}



void Menu::draw(sf::RenderWindow& window) {
    window.draw(panel);
    window.draw(titleText);
    window.draw(subtitleText);

    for (int i = 0; i < itemCount; i++) {
        window.draw(items[i]);
    }

    window.draw(helpText);
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        items[selectedIndex].setFillColor(sf::Color::White);

        if (selectedIndex == 0)
            items[selectedIndex].setString("Start Game");
        if (selectedIndex == 1)
            items[selectedIndex].setString("Difficulty: " + difficulty);
        if (selectedIndex == 2)
            items[selectedIndex].setString("Exit");

        selectedIndex--;

        items[selectedIndex].setFillColor(sf::Color(255, 215, 0));

        if (selectedIndex == 0)
            items[selectedIndex].setString("> Start Game");
        if (selectedIndex == 1)
            items[selectedIndex].setString("> Difficulty: " + difficulty);
        if (selectedIndex == 2)
            items[selectedIndex].setString("> Exit");
    }
}

void Menu::moveDown() {
    if (selectedIndex < itemCount - 1) {
        items[selectedIndex].setFillColor(sf::Color::White);

        if (selectedIndex == 0)
            items[selectedIndex].setString("Start Game");
        if (selectedIndex == 1)
            items[selectedIndex].setString("Difficulty: " + difficulty);
        if (selectedIndex == 2)
            items[selectedIndex].setString("Exit");

        selectedIndex++;

        items[selectedIndex].setFillColor(sf::Color(255, 215, 0));

        if (selectedIndex == 0)
            items[selectedIndex].setString("> Start Game");
        if (selectedIndex == 1)
            items[selectedIndex].setString("> Difficulty: " + difficulty);
        if (selectedIndex == 2)
            items[selectedIndex].setString("> Exit");
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}

std::string Menu::getDifficulty() const {
    return difficulty;
}

void Menu::nextDifficulty() {
    if (difficulty == "Easy")
        difficulty = "Medium";
    else if (difficulty == "Medium")
        difficulty = "Hard";
    else
        difficulty = "Easy";

    if (selectedIndex == 1)
        items[1].setString("> Difficulty: " + difficulty);
    else
        items[1].setString("Difficulty: " + difficulty);
}