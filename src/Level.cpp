#include "include/Level.hpp"
#include <iostream>

Level::Level(sf::RenderWindow &window) : player_(PlayerTank(sf::Vector2f(200, 200), 3.0f))
{
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
    Shield testShield(sf::Vector2f(gapCenterX - 50, verticalWallYPosition - 50));
    Shield anotherTestShield(sf::Vector2f(gapCenterX, verticalWallYPosition + 630));
    
<<<<<<< src/Level.cpp
    level_data_.walls_.push_back(topWall);
    level_data_.walls_.push_back(bottomWall);
    level_data_.walls_.push_back(leftWall);
    level_data_.walls_.push_back(rightWall);
    level_data_.walls_.push_back(leftVerticalWall);
    level_data_.walls_.push_back(rightVerticalWall);
    level_data_.spikes_.push_back(middleSpikes);
    shields_.push_back(testShield);
    shields_.push_back(anotherTestShield);

    // Note use of emplace back which does not need copying
    level_data_.enemies_.emplace_back(sf::Vector2f(200, 200), 3.0f, player_);
    level_data_.enemies_.emplace_back(sf::Vector2f(200, 200), 3.0f, player_);
  
}

bool Level::IsCompleted() const {
  // Add check whether player has reached door.
  if (level_data_.enemies_.empty()) {
    return true;
  }
  return false;
}

void Level::UpdateLevel(sf::RenderWindow &window) {
  // Update enemy positions and make them shoot.
  for (auto &it : level_data_.enemies_) {
    it.Update(level_data_);
  }
  // Update positions of projectiles.
  for (auto &projectile: level_data_.projectiles_) {
    projectile.Move();
  }
  // Handle projectile collisions
  HandleProjectileCollisions();
  // Update player tank position and make it shoot.
  player_.Update(window, level_data_);
  HandleItemPickUps();
}

void Level::DrawLevel(sf::RenderWindow &window) {
  for (const auto &it : shields_) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.walls_) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.spikes_) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.enemies_) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.projectiles_) {
    it.Draw(window);
  }
  player_.Draw(window);
}

void Level::HandleProjectileCollisions() {
  for (auto projectile_it = level_data_.projectiles_.begin(); projectile_it != level_data_.projectiles_.end();) {
    // Check for collisions between wall and projectile.
    ProjectileWallCollisionResult result = NoCollision;
    for (const Wall &wall : level_data_.walls_) {
      result = CollisionManager::ProjectileWall(*projectile_it, wall);
      if (result == ProjectileWallCollisionResult::Ricochet || result == ProjectileWallCollisionResult::Destroy) {
        // No need to check other walls
        break;
      }
    }
    if (result == ProjectileWallCollisionResult::Destroy) {
      // Remove projectile and move to next one.
      projectile_it = level_data_.projectiles_.erase(projectile_it);
      continue;
    }
    // Check for collisions with other projectiles
    bool projectile_collision = false;
    for (auto other_projectile_it = std::next(projectile_it); other_projectile_it != level_data_.projectiles_.end();) {
      projectile_collision = CollisionManager::ProjectileProjectile(*projectile_it, *other_projectile_it);
      if (projectile_collision) {
        level_data_.projectiles_.erase(other_projectile_it);
        // No need to check other projectiles
        break;
      } else {
        ++other_projectile_it;
      }
    }
    if (projectile_collision) {
      // Remove projectile and move to next one
      projectile_it = level_data_.projectiles_.erase(projectile_it);
      continue;
    }
    // Check for collisions with enemy tanks.
    bool enemy_collision = false;
    for (auto enemy_it = level_data_.enemies_.begin(); enemy_it != level_data_.enemies_.end();) {
      enemy_collision = CollisionManager::ProjectileTank(*projectile_it, *enemy_it);
      if (enemy_collision) {
        // No need to check other enemies
        level_data_.enemies_.erase(enemy_it);
        break;
      } else {
        ++enemy_it;
      }
    }
    if (enemy_collision) {
      // Remove projectile and move to next one.
      projectile_it = level_data_.projectiles_.erase(projectile_it);
      continue;
    }
    // Check for collision with player tank
    if (CollisionManager::ProjectileTank(*projectile_it, player_)) {
      //Projectile has hit a player, check if they have a shield.
      if (player_.hasShield()) {
        //Player has a shield. No game over but break the shield.
        player_.breakShield();
        std::cout << "Player was hit, but the shield saved them!" << std::endl;
        projectile_it = projectiles_.erase(projectile_it);
        continue;
      } else {
        // Game over
        std::cout << "Player was hit" << std::endl;
        projectile_it = projectiles_.erase(projectile_it);
        continue;
      }
    }
    //No collisions
    ++projectile_it;
  } 

void Level::HandleItemPickUps(){
  OBB tankOBB = OBB(player_.GetShape());
 
  //Check if player is over a shield.
  for (auto shield = shields_.begin(); shield != shields_.end();){
    OBB shieldOBB = OBB(shield->GetShape());
    
    if(tankOBB.collides(shieldOBB)){
      //Player is over a shield. Check if player already has a shield.
      if (!player_.hasShield()){
        //Player doesn't have shield, enable it and remove it from the field.
        player_.setShield();
        shield = shields_.erase(shield);
      } else {
        //Player already has a shield. Do nothing.
        shield++;
      }
    } else {
      shield++;
    }
  }
}
const LevelData& Level::GetLevelData(){ return level_data_; }
