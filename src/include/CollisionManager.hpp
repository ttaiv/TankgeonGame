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
   * projectile ricochet or return ProjectileWallCollisionResult::Destroy to signal that 
   * projectile should be removed from level.
   * 
   * @param projectile 
   * @param wall 
   * @return ProjectileWallCollisionResult
   */
  ProjectileWallCollisionResult ProjectileWall(Projectile &projectile, const Wall &wall);

  /**
 * @brief 
 * 
 * @param projectile 
 * @param tank 
 * @return true, if tank and projectile collide and projectile is active
 * @return false, if tank and projectile do not collide or projectile is not active
 */
  bool ProjectileTank(Projectile &projectile, Tank &tank);

  /**
   * @param two projectiles
   * @return true, if projectiles collide
   * @return false, if projectiles do not collide
   */
  bool ProjectileProjectile(Projectile &projectile1, Projectile &projectile2);
}
