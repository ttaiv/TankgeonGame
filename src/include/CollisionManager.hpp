#pragma once
#include "Projectile.hpp"
#include "Wall.hpp"
#include "Level.hpp"

namespace CollisionManager {
  /**
   * @brief
   * Check for collision between wall and projectile. If collision occurs, either make
   * projectile ricochet or return false to indicate that projectile should be destroyed.
   * 
   * @param projectile 
   * @param wall 
   * @return false if projectile does not collide wall or collides and ricochets
   * @return true if projectile collides wall and should be destroyed
   */
  bool ProjectileWall(Projectile &projectile, Wall &wall);
}