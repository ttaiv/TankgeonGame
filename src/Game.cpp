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

int Game::GetLevelNum(){
      return current_level_num_;
    }

bool Game::GetShieldStatus() {
      return current_level_.GetPlayerTank().hasShield();
    }