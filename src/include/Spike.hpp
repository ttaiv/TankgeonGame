#pragma once
#include "Obstacle.hpp"

class Wall: public Obstacle 
{
  public:
    bool IsProjectilePassable() override {return true;}
    bool IsTankPassable() override {return false;}

  private:
};