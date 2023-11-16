#include "include/Game.hpp"
#include <iostream>


Game::Game(sf::RenderWindow &window) 
  : window_(window), player_(sf::Vector2f(100, 100), 3), current_level_(player_, window) {}

void Game::Advance() {
  if (current_level_.IsCompleted() && false) {
    std::cout << "Level complete, should load new now.";
  }
  current_level_.UpdateLevel(window_);
  current_level_.DrawLevel(window_);
}