#pragma once
#include "Obstacle.hpp"

class Wall: public Obstacle 
{
  public:
    virtual bool IsProjectilePassable() {return false;}
    virtual bool IsTankPassable() {return false;}
    

  private:
};