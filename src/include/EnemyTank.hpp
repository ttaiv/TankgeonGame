#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Tank.hpp"
#include "PlayerTank.hpp"
#include <random>

class EnemyTank: public Tank {
  public:
    EnemyTank(sf::Vector2f initial_pos, float speed_scaler, PlayerTank &player, int fire_cooldown = ENEMY_FIRE_COOLDOWN);
    EnemyTank(const EnemyTank &other) = delete;
    EnemyTank& operator=(const EnemyTank &other) = delete;
    
    /*
    Update and UpdateShape are overriden by derived concrete enemy tank classes
    to implement different behaviour for different enemy tanks.
    */

    /**
     * @brief Make tank shoot and move
     * 
     * @param level_data
     */
    void virtual Update(LevelData &level_data_) = 0;
    
    bool WillBeHit(LevelData &level_data_) const;
    bool CanSeePlayer(LevelData &level_data_) const;

    int GetPoints() const;

  protected:
    /**
     * @brief Handle moving and rotating the tank shape
     * 
     * @param wanted rotation_angle 
     * @param level_data
     */
    // void virtual UpdateShape(float rotation_angle, LevelData &level_data_);


    float GetAngleToPlayer();
    bool IsTooClose();
    const PlayerTank &player_;
    int points_;

    // To generate random numbers
    std::random_device rd_;
    std::mt19937 gen_{rd_()};
};