#pragma once
#include "EnemyTank.hpp"
#include <SFML/Graphics.hpp>
#include <random>

class BurstTank : public EnemyTank {
  public:
    BurstTank(sf::Vector2f initial_pos, PlayerTank &player);
    BurstTank(const BurstTank &other) = delete;
    BurstTank& operator=(const BurstTank &other) = delete;

    void Update(LevelData &level_data_) override;

  private:
    void UpdateShape(float rotation_angle, LevelData &level_data_);

    std::random_device rd_;
    std::mt19937 gen_{rd_()};
    std::uniform_real_distribution<float> dis_{0, M_PI / 8};
    std::uniform_int_distribution<int> sign_dis{0, 1};

    float GetRandomAngle();
};