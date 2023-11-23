#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerTank.hpp"
#include "Level.hpp"
enum GameState {
  Start,
  Gameplay,
  Pause,
  GameOver
};

class Game {
  public:
    Game(sf::RenderWindow &window);
    /**
     * @brief Advances game. Is called every frame. 
     * Handles updating and drawing current level and loading new one if needed.
     * 
     */
    void Advance();

    void StartScreen();

    void PauseScreen();

    void EndScreen();

    /**
     * @brief Getter function to let the hud know the current level.
     * 
     * @return int 
     */
    int GetLevelNum();

    /**
     * @brief Getter function to let the hud know wether the player has a shield.
     * 
     * @return true 
     * @return false 
     */
    bool GetShieldStatus();

    void SetGameState();
       

    GameState gameState_ = Start;

  private:
    sf::RenderWindow &window_;
    Level current_level_;
    int current_level_num_ = 1;
    sf::Font font_;
    

    bool LoadNextLevel();
};