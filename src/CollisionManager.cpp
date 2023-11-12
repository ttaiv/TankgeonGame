#include "include/CollisionManager.hpp"

ProjectileWallCollisionResult CollisionManager::ProjectileWall(Projectile &projectile, Wall &wall) {
  sf::FloatRect projectile_box = projectile.GetShape().getGlobalBounds();
  sf::FloatRect wall_bounds = wall.GetShape().getGlobalBounds();
  if (wall_bounds.intersects(projectile_box)) {
    // Collision happened.
    if (projectile.RicochetLimitReached()) {
      return Destroy; // Projectile should be destroyed
    }
    // Calculate intersection and make projectile ricochet.
    sf::FloatRect intersection;
    wall_bounds.intersects(projectile_box, intersection);
    if (intersection.width > intersection.height) {
      // Collision is more vertical
      projectile.RicochetY();
    } else {
      // Collision is more horizontal
      projectile.RicochetX();
    }
    return Ricochet;
  }
  return NoCollision;
}

/**
 * @brief 
 * 
 * @param projectile 
 * @param tank 
 * @return true, if tank and projectile collide and projectile is active
 * @return false, if tank and projectile do not collide or projectile is not active
 */
bool CollisionManager::ProjectileTank(Projectile &projectile, Tank &tank) {
  sf::FloatRect projectile_box = projectile.GetShape().getGlobalBounds();
  sf::FloatRect tank_bounds = tank.GetShape().getGlobalBounds();
  if (projectile.Hurts() && tank_bounds.intersects(projectile_box)) {
    return true;
  }
  return false;
}