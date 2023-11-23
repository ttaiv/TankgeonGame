#pragma once
#include "EnemyTank.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

class StationaryTank : public EnemyTank {
  public:
    StationaryTank(sf::Vector2f initial_pos, PlayerTank &player);
    StationaryTank(const StationaryTank &other) = delete;
    StationaryTank& operator=(const StationaryTank &other) = delete;

    void Update(LevelData &level_data_) override;

  private:

    std::random_device rd_;
    std::mt19937 gen_{rd_()};
    std::uniform_real_distribution<float> dis_{0, M_PI / 4};
    std::uniform_int_distribution<int> sign_dis{0, 1};

    float GetRandomAngle();
};