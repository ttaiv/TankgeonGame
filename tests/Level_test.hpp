#pragma once
#include "../src/include/Level.hpp"

namespace LevelTest {
  void testCreation() {
    Level level;
    const int window_width = 1920;
    const int window_height = 1080; // Hard coded window size
    const int x_scale = window_width / Level::LEVEL_FILE_WIDTH;
    const int y_scale = window_height / Level::LEVEL_FILE_HEIGHT;
    // Load test level 000
    level.LoadFromFile(0, sf::Vector2u(window_width, window_height));
    // Check that enemy position is correct
    // Enemy tank should be at (4, 2)
    auto &enemy = level.GetLevelData().enemies.front();
    sf::Vector2f position = enemy->GetShape().getPosition();
    sf::Vector2f expected_position = sf::Vector2f(4 * x_scale, 2 * y_scale);
    if (position != expected_position) {
      throw std::runtime_error("Enemy position in test is incorrect");
    }

  }
}