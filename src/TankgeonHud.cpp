#include "include/TankgeonHud.hpp"
#include <iostream>

TankgeonHud::TankgeonHud(const sf::RenderWindow& window)
  : sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y / 10)) {
        setViewport(sf::FloatRect(0, 0.92f, 1.f, 0.08f));
        font_.loadFromFile("../src/fonts/arial.ttf");
    }

void TankgeonHud::updateView(const sf::RenderWindow& window) {
    setCenter(window.getSize().x / 2, window.getSize().y / 20);  // Adjust the y-value based on your preferred position
    setSize(window.getSize().x, window.getSize().y / 10);
}

void TankgeonHud::draw(sf::RenderWindow &window, int level_num, bool shield_status) const {
        sf::RectangleShape hudRect(sf::Vector2f(getSize().x, getSize().y));
        hudRect.setFillColor(sf::Color::White);
        window.draw(hudRect);

        sf::Text title_text_;
        title_text_.setFont(font_);
        title_text_.setString("Tankgeon! beta");
        title_text_.setCharacterSize(30);
        title_text_.setFillColor(sf::Color::Black);
        title_text_.setPosition(getCenter().x - getSize().x / 2 + 10.f, getCenter().y - title_text_.getLocalBounds().height / 2.f);


        sf::Text level_text;
        level_text.setFont(font_);
        level_text.setString("Level: " + std::to_string(level_num));
        level_text.setCharacterSize(30);
        level_text.setFillColor(sf::Color::Black);
        level_text.setPosition(getCenter().x - level_text.getLocalBounds().width / 2, getCenter().y - level_text.getLocalBounds().height / 2);

        sf::Text shield_text;
        shield_text.setFont(font_);
        shield_text.setString("Shield:");
        shield_text.setCharacterSize(30);
        shield_text.setFillColor(sf::Color::Black);
        shield_text.setPosition(getSize().x - 120 - shield_text.getLocalBounds().width, getCenter().y - level_text.getLocalBounds().height / 2);

        sf::RectangleShape frameRect_;
        frameRect_.setSize(sf::Vector2f(100, getSize().y));
        frameRect_.setFillColor(sf::Color::Black);
        frameRect_.setPosition(window.getSize().x - 100, 0);

        sf::RectangleShape whiteSquare_;
        whiteSquare_.setSize(sf::Vector2f(80, getSize().y - 20));
        whiteSquare_.setFillColor(sf::Color::White);
        whiteSquare_.setPosition(window.getSize().x - 90, 10);

        sf::RectangleShape shield_;
        shield_.setSize(sf::Vector2f(52, 50));
        shield_.setFillColor(sf::Color::Cyan);
        shield_.setPosition((whiteSquare_.getPosition().x + (whiteSquare_.getSize().x - 50) / 2), (whiteSquare_.getPosition().y + (whiteSquare_.getSize().y - 50) / 2));

        window.draw(title_text_);
        window.draw(level_text);
        window.draw(shield_text);
        window.draw(frameRect_);
        window.draw(whiteSquare_);
        
        if (shield_status){  
          window.draw(shield_);
        }
    }
