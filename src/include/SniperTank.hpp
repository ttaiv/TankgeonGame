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

    enum MovementOption {
      TurnLeft = 0,
      TurnRight,
      GoForward1,
      GoForward2,
      GoBack,
      MovementCount // Count enum values
    };

    MovementOption ChooseMovement();

    std::uniform_int_distribution<int> movement_dis_{0, MovementCount - 1};
    int movement_timer_ = 0;
    MovementOption current_movement_ = MovementOption::GoForward1;
};