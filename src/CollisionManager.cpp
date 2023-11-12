#include "include/CollisionManager.hpp"

bool CollisionManager::ProjectileWall(Projectile &projectile, Wall &wall) {
  sf::FloatRect projectile_box = projectile.GetShape().getGlobalBounds();
  sf::FloatRect wall_bounds = wall.GetShape().getGlobalBounds();
  if (wall_bounds.intersects(projectile_box)) {
    // Collision happened.
    if (projectile.RicochetLimitReached()) {
      return true; // Projectile should be destroyed
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
  }
  return false;
}