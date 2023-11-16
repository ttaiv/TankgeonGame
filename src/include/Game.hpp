#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerTank.hpp"
#include "Level.hpp"

class Game {
  public:
    Game(sf::RenderWindow &window);
    /**
     * @brief Advances game. Is called every frame. 
     * Handles updating and drawing current level and loading new one if needed.
     * 
     */
    void Advance();

  private:
    sf::RenderWindow &window_;
    PlayerTank player_;
    Level current_level_;
    int current_level_num_ = 1;

    bool LoadNextLevel();
};