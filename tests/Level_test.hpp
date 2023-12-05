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
    // Check that player position is correct
    // Player tank should be at (15, 3)
    const PlayerTank &player = level.GetPlayerTank();
    position = player.GetShape().getPosition();
    expected_position = sf::Vector2f(15 * x_scale, 3 * y_scale);
    if (position != expected_position) {
      throw std::runtime_error("Player position in test is incorrect");
    }
    // Check that wall position is correct
    // Wall should be at (7, 6)
    // 4th wall is the first non-border wall
    const Wall &wall = level.GetLevelData().walls[4]; 
    position = wall.GetShape().getPosition();
    expected_position = sf::Vector2f(7 * x_scale, 6 * y_scale);
    if (position != expected_position) {
      throw std::runtime_error("Wall position in test is incorrect");
    }
    // Check that spike position is correct
    // Spike should be at (27, 5)
    const Spike &spike = level.GetLevelData().spikes.front();
    position = spike.GetShape().getPosition();
    expected_position = sf::Vector2f(27 * x_scale, 5 * y_scale);
    if (position != expected_position) {
      throw std::runtime_error("Spike position in test is incorrect");
    }
    // Check that shield position is correct
    // Shield should be at (28, 1)
    const Shield &shield = level.GetLevelData().shields.front();
    position = shield.GetShape().getPosition();
    expected_position = sf::Vector2f(28 * x_scale, 1 * y_scale);
    if (position != expected_position) {
      throw std::runtime_error("Shield position in test is incorrect");
    }
  }
}