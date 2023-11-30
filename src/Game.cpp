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
    if(current_level_.GetPlayerTank().ExplosionAnimationOver()){
      gameState_ = GameOverLose;
      UpdateHighScore(GetPlayerScore());  
    }
  } catch (const std::runtime_error& e) {
    if(current_level_.GetLevelData().enemies.empty()){
      gameState_ = GameOverWin;
      UpdateHighScore(GetPlayerScore());
    }
  }

  current_level_.UpdateLevel(window_);
  current_level_.DrawLevel(window_);
} 

void Game::StartScreen(){
  gameState_ = Start;
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
      current_level_num_=1;
      current_level_.LoadFromFile(1, window_.getSize());
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

  sf::Text score_text;
  score_text.setFont(font_);
  score_text.setString("Your score: " + std::to_string(GetPlayerScore()));
  score_text.setCharacterSize(40);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(
    window_.getSize().x / 2.0 - score_text.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - score_text.getLocalBounds().height / 2.0 + 200
  );

  window_.draw(score_text);

  sf::Text new_high_score_text;
  new_high_score_text.setFont(font_);
  new_high_score_text.setString("New high score!");
  new_high_score_text.setCharacterSize(40);
  new_high_score_text.setPosition(
    window_.getSize().x / 2.0 - new_high_score_text.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - new_high_score_text.getLocalBounds().height / 2.0 + 100
  );

  if (new_high_score_){
    frame_counter_++;
    if (frame_counter_ < 35) {
      new_high_score_text.setFillColor(sf::Color::Black);
    } else if (frame_counter_ > 80) {
      frame_counter_ = 0;
    } else {
      new_high_score_text.setFillColor(sf::Color::Yellow);
    }
    window_.draw(new_high_score_text);
  }
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

  sf::Text score_text;
  score_text.setFont(font_);
  score_text.setString("Your score: " + std::to_string(GetPlayerScore()));
  score_text.setCharacterSize(40);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(
    window_.getSize().x / 2.0 - score_text.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - score_text.getLocalBounds().height / 2.0 + 200
  );

  window_.draw(score_text);

  sf::Text new_high_score_text;
  new_high_score_text.setFont(font_);
  new_high_score_text.setString("New high score!");
  new_high_score_text.setCharacterSize(40);
  new_high_score_text.setPosition(
    window_.getSize().x / 2.0 - new_high_score_text.getLocalBounds().width / 2.0, 
    window_.getSize().y / 2.0 - new_high_score_text.getLocalBounds().height / 2.0 + 100
  );

  if (new_high_score_){
    frame_counter_++;
    if (frame_counter_ < 35) {
      new_high_score_text.setFillColor(sf::Color::Black);
    } else if (frame_counter_ > 80) {
      frame_counter_ = 0;
    } else {
      new_high_score_text.setFillColor(sf::Color::Yellow);
    }
    window_.draw(new_high_score_text);
  } 
}

int Game::GetLevelNum(){ return current_level_num_; }

bool Game::GetShieldStatus() { return current_level_.GetPlayerTank().HasShield(); }

bool Game::GetPlayerAnimationStatus() {return current_level_.GetPlayerTank().ExplosionAnimationOver();}

void Game::PauseMusic(){playing_sound_.pause();}

void Game::ContinueMusic() {playing_sound_.play();}

int Game::GetPlayerScore() const { return current_level_.GetPlayerTank().GetScore(); }

void Game::UpdateHighScore(int game_score) {
  int current_high_score;
  
  std::ifstream high_score_file_in("../src/High_score.txt");
  if (!high_score_file_in.is_open()) {
    throw std::runtime_error("Failed to open the file with high score");
  }

  high_score_file_in >> current_high_score;
  high_score_file_in.close();

  if (game_score > current_high_score) {
    std::ofstream high_score_file_out("../src/High_score.txt");
    
    if (!high_score_file_out.is_open()) {
      throw std::runtime_error("Failed to open the file with high score");
    }

    high_score_file_out << game_score;
    high_score_file_out.close();

    new_high_score_ = true;
  }
}