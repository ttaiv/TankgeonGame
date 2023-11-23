#include "include/Game.hpp"
#include <iostream>


Game::Game(sf::RenderWindow &window) : window_(window) {
  current_level_.LoadFromFile(1, window.getSize());
  font_.loadFromFile("../src/fonts/arial.ttf");
  hype_sound_buffer_.loadFromFile("../src/assets/sounds/Hype.wav");
  start_sound_buffer_.loadFromFile("../src/assets/sounds/StartMusic.wav");
}

void Game::Advance() {
  try{
    if (current_level_.IsCompleted()) {
      std::cout << "Level " << current_level_num_ << " complete" << std::endl;
      current_level_.LoadFromFile(++current_level_num_, window_.getSize());
    }
  } catch (const std::runtime_error& e) {
    gameState_ = GameOverWin;
  }

  current_level_.UpdateLevel(window_);
  current_level_.DrawLevel(window_);
} 

void Game::StartScreen(){
  sf::Texture backgroundTexture;
  backgroundTexture.loadFromFile("../src/assets/CiiPlayTanks.png");
  sf::Sprite background(backgroundTexture);
  background.setScale(
    static_cast<float>(window_.getSize().x) / backgroundTexture.getSize().x,
    static_cast<float>(window_.getSize().y) / backgroundTexture.getSize().y
  );
  if(!is_playing_){
    playing_sound_.setBuffer(start_sound_buffer_);
    playing_sound_.setLoop(true);
    playing_sound_.play();
    is_playing_=true;
  }
  window_.draw(background);
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
      playing_sound_.setBuffer(hype_sound_buffer_);
      playing_sound_.setLoop(true);
      playing_sound_.setVolume(60);
      playing_sound_.play();
      gameState_ = Gameplay;
    }
  }
  window_.draw(start_button);
  window_.draw(start_text_);
  
}

void Game::PauseScreen(){
  sf::RectangleShape background(sf::Vector2f(window_.getSize().x, window_.getSize().y));
  background.setFillColor(sf::Color::Black);
  window_.draw(background);

  sf::Text title_text_;
  title_text_.setFont(font_);
  title_text_.setString("Paused");
  title_text_.setCharacterSize(50);
  title_text_.setFillColor(sf::Color::White);
  title_text_.setPosition(
    window_.getSize().x / 2.0 - title_text_.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - title_text_.getLocalBounds().height / 2.0
  );
  window_.draw(title_text_);
  playing_sound_.pause();
}

void Game::EndScreenWin(){
  sf::RectangleShape background(sf::Vector2f(window_.getSize().x, window_.getSize().y));
  background.setFillColor(sf::Color::Black);
  window_.draw(background);

  sf::Text title_text_;
  title_text_.setFont(font_);
  title_text_.setString("You win");
  title_text_.setCharacterSize(50);
  title_text_.setFillColor(sf::Color::White);
  title_text_.setPosition(
    window_.getSize().x / 2.0 - title_text_.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - title_text_.getLocalBounds().height / 2.0
  );
  window_.draw(title_text_);  
}

void Game::EndScreenLose(){
  sf::RectangleShape background(sf::Vector2f(window_.getSize().x, window_.getSize().y));
  background.setFillColor(sf::Color::Black);
  window_.draw(background);

  sf::Text title_text_;
  title_text_.setFont(font_);
  title_text_.setString("You Lose");
  title_text_.setCharacterSize(50);
  title_text_.setFillColor(sf::Color::White);
  title_text_.setPosition(
    window_.getSize().x / 2.0 - title_text_.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - title_text_.getLocalBounds().height / 2.0
  );
  window_.draw(title_text_); 
}

int Game::GetLevelNum(){ return current_level_num_; }

bool Game::GetShieldStatus() { return current_level_.GetPlayerTank().HasShield(); }

void Game::PauseMusic(){
  playing_sound_.pause();
}

void Game::ContinueMusic(){
  playing_sound_.play();
}