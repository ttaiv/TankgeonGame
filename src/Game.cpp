#include "include/Game.hpp"
#include <iostream>


Game::Game(sf::RenderWindow &window) : window_(window) {
  current_level_.LoadFromFile(1, window.getSize());
}

void Game::Advance() {
  if (current_level_.IsCompleted()) {
    std::cout << "Level " << current_level_num_ << " complete" << std::endl;
    current_level_.LoadFromFile(++current_level_num_, window_.getSize());
  }
  current_level_.UpdateLevel(window_);
  current_level_.DrawLevel(window_);
}
int Game::StartScreen(){
  sf::RectangleShape hudRect(sf::Vector2f(window_.getSize().x, window_.getSize().y));
  hudRect.setFillColor(sf::Color::White);
  window_.draw(hudRect);

  sf::Text title_text_;
  title_text_.setString("Tankgeon! beta");
  title_text_.setCharacterSize(30);
  title_text_.setFillColor(sf::Color::Black);
  title_text_.setPosition(window_.getSize().x / 2.0, window_.getSize().y / 2.0);
  window_.draw(title_text_);

  sf::Text start_text_;
  title_text_.setString("Start");
  title_text_.setCharacterSize(30);
  title_text_.setFillColor(sf::Color::Black);
  title_text_.setPosition(window_.getSize().x / 2.0, window_.getSize().y / 1.5);
  window_.draw(start_text_);

  return 0;

}

int Game::GetLevelNum(){
      return current_level_num_;
    }

bool Game::GetShieldStatus() {
      return current_level_.GetPlayerTank().hasShield();
    }