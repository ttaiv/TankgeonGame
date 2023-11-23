#pragma once
#include "EnemyTank.hpp"
#include <SFML/Graphics.hpp>

class SniperTank : public EnemyTank {
  public:
    SniperTank(sf::Vector2f initial_pos, PlayerTank &player);
    SniperTank(const SniperTank &other) = delete;
    SniperTank& operator=(const SniperTank &other) = delete;

    void Update(LevelData &level_data_) override;

  private:
    void UpdateShape(float rotation_angle, LevelData &level_data_);
};