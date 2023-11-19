#include "include/Game.hpp"
#include <iostream>


Game::Game(sf::RenderWindow &window) : window_(window) {
    current_level_.LoadFromFile(1, window.getSize());
}

void Game::Advance() {
  if (current_level_.IsCompleted() && false) {
    std::cout << "Level complete, should load new now.";
  }
  current_level_.UpdateLevel(window_);
  current_level_.DrawLevel(window_);
}