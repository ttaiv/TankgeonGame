#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Tank.hpp"


class PlayerTank: public Tank {
  public:
    PlayerTank(sf::Vector2f initial_pos, float speed_scaler);
    PlayerTank(const PlayerTank&) = delete;
    PlayerTank& operator=(const PlayerTank&) = delete;
    
    void Update(sf::RenderWindow &window, LevelData &level_data);

    /**
     * @brief Sets has_shield_ to true for the player tank.
     * 
     */
    void SetShield();

    /**
     * @brief Sets has_shield_ to false for the player tank.
     * 
     */
    void BreakShield();

    /**
     * @brief Returns true if the player tank has a shield, false otherwise.
     * 
     * @return true 
     * @return false 
     */
    bool HasShield() const;

    void AddScore(int amount);

    int GetScore() const;

    void ResetScore();

  private:
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float in radians
     */
    sf::Texture shield_texture_;
    sf::Sprite ss_;
    bool has_shield_;
    int score_;
    
    float GetTurretRotationAngle(sf::RenderWindow &window);
    void UpdateShape(float rotation_angle, LevelData &level_data);

};