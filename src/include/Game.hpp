#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerTank.hpp"
#include "Level.hpp"
#include <SFML/Audio.hpp>
enum GameState {
  Start,
  Gameplay,
  Pause,
  GameOverWin,
  GameOverLose
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

    void EndScreenWin();

    void EndScreenLose();

    void PauseMusic();

    void ContinueMusic();

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

    bool GetPlayerAnimationStatus();
       

    GameState gameState_ = Start;

  private:
    sf::RenderWindow &window_;
    Level current_level_;
    int current_level_num_ = 1;
    sf::Font font_;
    sf::SoundBuffer hype_sound_buffer_;
    sf::SoundBuffer start_sound_buffer_;
    sf::Sound playing_sound_;
    bool is_playing_ = false;

    bool LoadNextLevel();
};