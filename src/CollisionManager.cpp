#include "include/CollisionManager.hpp"

ProjectileWallCollisionResult CollisionManager::ProjectileWall(Projectile &projectile, const Wall &wall) {
  sf::FloatRect projectile_box = projectile.GetShape().getGlobalBounds();
  sf::FloatRect wall_bounds = wall.GetShape().getGlobalBounds();
  if (wall_bounds.intersects(projectile_box)) {
    // Collision happened.
    if (projectile.RicochetLimitReached()) {
      return ProjectileWallCollisionResult::Destroy; // Projectile should be destroyed
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
    return ProjectileWallCollisionResult::Ricochet;
  }
  return ProjectileWallCollisionResult::NoCollision;
}

bool CollisionManager::ProjectileTank(Projectile &projectile, Tank &tank) {
  sf::FloatRect projectile_box = projectile.GetShape().getGlobalBounds();
  sf::FloatRect tank_bounds = tank.GetShape().getGlobalBounds();
  if (projectile.Hurts() && tank_bounds.intersects(projectile_box)) {
    return true;
  }
  return false;
}

bool CollisionManager::ProjectileProjectile(Projectile &projectile1, Projectile &projectile2) {
  sf::FloatRect projectile_box1 = projectile1.GetShape().getGlobalBounds();
  sf::FloatRect projectile_box2 = projectile2.GetShape().getGlobalBounds();
  if (projectile_box1.intersects(projectile_box2)) {
    return true;
  }
  return false;
}