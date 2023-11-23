#pragma once
#include "EnemyTank.hpp"
#include <SFML/Graphics.hpp>

class SniperTank : public EnemyTank {
  public:
    SniperTank(sf::Vector2f initial_pos, PlayerTank &player);
    SniperTank(const SniperTank &other); //Custom copy constructor to keep textures
    SniperTank& operator=(const SniperTank &other) = delete;

    void Update(LevelData &level_data_) override;
    void UpdateShape(float rotation_angle, LevelData &level_data_) override;

  private:

    sf::Texture chassis_texture_;
    sf::Texture turret_texture_;
};