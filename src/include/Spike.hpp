#pragma once
#include "Obstacle.hpp"

class Wall: public Obstacle 
{
  public:
    bool IsProjectilePassable() override { return true; }
    bool IsTankPassable() override { return false; } //onko mahdollista mennä piikin läpi jos on esim armorii?

  private:
};