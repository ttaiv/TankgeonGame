#include "include/Level.hpp"
#include <iostream>

Level::Level(PlayerTank player) : player_(player) {}

void Level::SetUpLevel(int level_number, sf::RenderWindow &window) {
  if (level_number == 1) {
    sf::Vector2u windowSize = window.getSize();
    unsigned int windowWidth = windowSize.x;
    unsigned int windowHeight = windowSize.y;
    
    float wallThickness = 40;
    float gapSize = 1000;
    float gapCenterX = windowWidth / 2.0f;
    float halfGapSize = gapSize / 2.0f;
    float wallHeight = 600;
    float verticalWallYPosition = (windowHeight - wallHeight) / 2.0f;

    Wall topWall(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, 10));
    Wall bottomWall(sf::Vector2f(0, windowHeight - 10), sf::Vector2f(windowWidth, 10));
    Wall leftWall(sf::Vector2f(0, 0), sf::Vector2f(10, windowHeight));
    Wall rightWall(sf::Vector2f(windowWidth - 10, 0), sf::Vector2f(10, windowHeight));
    Wall leftVerticalWall(sf::Vector2f(gapCenterX - halfGapSize - wallThickness, verticalWallYPosition), sf::Vector2f(wallThickness, wallHeight));
    Wall rightVerticalWall(sf::Vector2f(gapCenterX + halfGapSize, verticalWallYPosition), sf::Vector2f(wallThickness, wallHeight));
    Spike middleSpikes(sf::Vector2f(gapCenterX - 100, verticalWallYPosition + 50), sf::Vector2f(wallThickness + 200, wallHeight - 100));
    
    walls_.push_back(topWall);
    walls_.push_back(bottomWall);
    walls_.push_back(leftWall);
    walls_.push_back(rightWall);
    walls_.push_back(leftVerticalWall);
    walls_.push_back(rightVerticalWall);
    spikes_.push_back(middleSpikes);

    // Note use of emplace back which does not need copying
    enemies_.emplace_back(sf::Vector2f(200, 200), 3);
    enemies_.emplace_back(sf::Vector2f(200, 400), 3);
  }
}
void Level::UpdateLevel(sf::RenderWindow &window) {
  // Update enemy positions and make them shoot.
  for (auto &it : enemies_) {
    it.Update(projectiles_, player_.GetShape(), walls_, spikes_);
  }
  // Update positions of projectiles.
  for (auto &projectile: projectiles_) {
    projectile.Move();
  }
  // Handle projectile collisions
  HandleProjectileCollisions();
  // Update player tank position and make it shoot.
  player_.Update(window, projectiles_, walls_, spikes_);
}

void Level::DrawLevel(sf::RenderWindow &window) {
  for (const auto &it : walls_) {
    it.Draw(window);
  }
  for (const auto &it : spikes_) {
    it.Draw(window);
  }
  // Has to be it instead of &it, why?? T: Teemu
  for (const auto &it : enemies_) {
    it.Draw(window);
  }
  for (const auto &it : projectiles_) {
    it.Draw(window);
  }
  player_.Draw(window);
}

void Level::HandleProjectileCollisions() {
  for (auto projectile_it = projectiles_.begin(); projectile_it != projectiles_.end();) {
    // Check for collisions between wall and projectile.
    ProjectileWallCollisionResult result = NoCollision;
    for (Wall &wall : walls_) {
      result = CollisionManager::ProjectileWall(*projectile_it, wall);
      if (result == Ricochet || result == Destroy) {
        // No need to check other walls
        break;
      }
    }
    if (result == Destroy) {
      // Remove projectile and move to next one.
      projectile_it = projectiles_.erase(projectile_it);
      continue;
    }
    // Check for collisions with enemy tanks.
    bool enemy_collision = false;
    for (auto enemy_it = enemies_.begin(); enemy_it != enemies_.end();) {
      enemy_collision = CollisionManager::ProjectileTank(*projectile_it, *enemy_it);
      if (enemy_collision) {
        // No need to check other enemies
        enemies_.erase(enemy_it);
        break;
      } else {
        ++enemy_it;
      }
    }
    if (enemy_collision) {
      // Remove projectile and move to next one.
      projectile_it = projectiles_.erase(projectile_it);
      continue;
    }
    // Check for collision with player tank
    if (CollisionManager::ProjectileTank(*projectile_it, player_)) {
      // Game over
      std::cout << "Player was hit" << std::endl;
      projectile_it = projectiles_.erase(projectile_it);
      continue;
    }
    ++projectile_it; // No collisions
  }
}
