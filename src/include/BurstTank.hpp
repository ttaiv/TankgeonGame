#pragma once
#include "EnemyTank.hpp"
#include <SFML/Graphics.hpp>


class BurstTank : public EnemyTank {
  public:
    BurstTank(sf::Vector2f initial_pos, PlayerTank &player);
    BurstTank(const BurstTank &other) = delete;
    BurstTank& operator=(const BurstTank &other) = delete;

    void Update(LevelData &level_data_) override;

  private:
    void UpdateShape(float rotation_angle, LevelData &level_data_);

    // Go forward is most probable.
    enum MovementOption {
      TurnLeft = 0,
      TurnRight,
      GoForward1,
      GoForward2, // Extra value for GoForward
      GoForward3, // Extra value for GoForward
      GoBack,
      MovementCount // count of the enum values
    };

    std::uniform_real_distribution<float> angle_dis_{0, M_PI / 8};
    std::uniform_int_distribution<int> angle_sign_dis_{0, 1};
    std::uniform_int_distribution<int> movement_dis_{0, MovementCount - 1};

    MovementOption current_movement_;
    int movement_timer_ = 0;

    float GetRandomAngle();
};