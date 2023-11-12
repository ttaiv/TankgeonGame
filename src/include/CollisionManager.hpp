#pragma once
#include "Projectile.hpp"
#include "Wall.hpp"
#include "Tank.hpp"

enum ProjectileWallCollisionResult {
  NoCollision,
  Ricochet,
  Destroy
};

namespace CollisionManager {
  /**
   * @brief
   * Check for collision between wall and projectile. If collision occurs, either make
   * projectile ricochet or return false to indicate that projectile should be destroyed.
   * 
   * @param projectile 
   * @param wall 
   * @return ProjectileWallCollisionResult
   */
  ProjectileWallCollisionResult ProjectileWall(Projectile &projectile, Wall &wall);

  bool ProjectileTank(Projectile &projectile, Tank &tank);
}