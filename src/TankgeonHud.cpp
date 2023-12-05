#include "include/TankgeonHud.hpp"
#include <iostream>

TankgeonHud::TankgeonHud(const sf::RenderWindow& window, Game& game)
  : sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y / 10)), game_(game) {
        setViewport(sf::FloatRect(0, 0.92f, 1.f, 0.08f));
        font_.loadFromFile("../src/assets/fonts/arial.ttf");
    }

void TankgeonHud::updateView(const sf::RenderWindow& window) {
    setCenter(window.getSize().x / 2, window.getSize().y / 20);  // Adjust the y-value based on your preferred position
    setSize(window.getSize().x, window.getSize().y / 10);
}

void TankgeonHud::draw(sf::RenderWindow &window) const {
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
        level_text.setString("Level: " + std::to_string(game_.GetLevelNum()));
        level_text.setCharacterSize(30);
        level_text.setFillColor(sf::Color::Black);
        level_text.setPosition(getCenter().x - level_text.getLocalBounds().width / 2, getCenter().y - level_text.getLocalBounds().height / 2);

        sf::Text score_text;
        sf::Text score_width;
        score_width.setFont(font_);
        score_width.setCharacterSize(30);
        score_width.setString("Score: 000000");
        score_text.setFont(font_);
        score_text.setString("Score: " + std::to_string(game_.GetPlayerScore()));
        score_text.setCharacterSize(30);
        score_text.setFillColor(sf::Color::Black);
        score_text.setPosition(getSize().x - score_width.getLocalBounds().width, getCenter().y - score_text.getLocalBounds().height / 2);

        window.draw(title_text_);
        window.draw(level_text);
        window.draw(score_text);
    }
