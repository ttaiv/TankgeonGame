#include "include/Game.hpp"
#include <iostream>


Game::Game(sf::RenderWindow &window) : window_(window) {
  current_level_.LoadFromFile(1, window.getSize());
  font_.loadFromFile("../src/fonts/arial.ttf");
  hype_sound_buffer_.loadFromFile("../src/assets/sounds/Hype.wav");
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
  sf::RectangleShape background(sf::Vector2f(window_.getSize().x, window_.getSize().y));
  background.setFillColor(sf::Color::White);
  window_.draw(background);
  playing_sound_.setBuffer(hype_sound_buffer_);
  playing_sound_.play();
  sf::Text title_text_;
  title_text_.setFont(font_);
  title_text_.setString("Tankgeon! beta");
  title_text_.setCharacterSize(40);
  title_text_.setFillColor(sf::Color::Black);
  title_text_.setPosition(
    window_.getSize().x / 2.0 - title_text_.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - title_text_.getLocalBounds().height / 2.0
  );
  window_.draw(title_text_);

  sf::Text start_text_;
  start_text_.setFont(font_);
  start_text_.setString("Start!");
  start_text_.setCharacterSize(20);
  start_text_.setFillColor(sf::Color::White);

  sf::RectangleShape start_button(sf::Vector2f(start_text_.getLocalBounds().width * 2, start_text_.getLocalBounds().height * 2));
  start_button.setFillColor(sf::Color::Black);

  start_text_.setPosition(    
    window_.getSize().x / 2.0 - start_text_.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - start_text_.getLocalBounds().height / 2.0 + 95
  );
  start_button.setPosition(    
    window_.getSize().x / 2.0 - start_button.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - start_button.getLocalBounds().height / 2.0 + 100
  );
  
  sf::Vector2i mouse_position = sf::Mouse::getPosition(window_);
  if (start_button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position))) {
    start_button.setFillColor(sf::Color::Green);
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      return 1;
    }
  }


  window_.draw(start_button);
  window_.draw(start_text_);
  
  window_.display();

  return 0;

}

int Game::GetLevelNum(){
      return current_level_num_;
    }

bool Game::GetShieldStatus() {
      return current_level_.GetPlayerTank().hasShield();
    }