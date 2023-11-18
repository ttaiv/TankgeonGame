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
    float wallHeight = 400;
    float verticalWallYPosition = (windowHeight - wallHeight - 80) / 2.0f;

    Wall topWall(sf::Vector2f(0, 0), sf::Vector2f(windowWidth, 10));
    Wall bottomWall(sf::Vector2f(0, windowHeight - 80), sf::Vector2f(windowWidth, 120));
    Wall leftWall(sf::Vector2f(0, 0), sf::Vector2f(10, windowHeight));
    Wall rightWall(sf::Vector2f(windowWidth - 10, 0), sf::Vector2f(10, windowHeight));
    Wall leftVerticalWall(sf::Vector2f(gapCenterX - halfGapSize, verticalWallYPosition), sf::Vector2f(wallThickness, wallHeight));
    Wall rightVerticalWall(sf::Vector2f(gapCenterX + halfGapSize, verticalWallYPosition), sf::Vector2f(wallThickness, wallHeight));
    Spike middleSpikes(sf::Vector2f(gapCenterX - 100, verticalWallYPosition), sf::Vector2f(wallThickness + 180, wallHeight - 25));
    Shield testShield(sf::Vector2f(gapCenterX - 50, verticalWallYPosition - 80));
    Shield anotherTestShield(sf::Vector2f(gapCenterX, verticalWallYPosition + 500));
    
    level_data_.walls.push_back(topWall);
    level_data_.walls.push_back(bottomWall);
    level_data_.walls.push_back(leftWall);
    level_data_.walls.push_back(rightWall);
    level_data_.walls.push_back(leftVerticalWall);
    level_data_.walls.push_back(rightVerticalWall);
    level_data_.spikes.push_back(middleSpikes);
    level_data_.shields.emplace_back(testShield);
    level_data_.shields.emplace_back(anotherTestShield);
    

    float enemy_1_x = 530;
    float enemy_1_y = windowSize.y / 2.0f;
    float enemy_2_x = windowSize.x - 100;
    float enemy_2_y = (windowSize.y / 2.0f) - 80;

    // Note use of emplace back which does not need copying
    level_data_.enemies.emplace_back(sf::Vector2f(enemy_1_x, enemy_1_y), 3.0f, player_);
    level_data_.enemies.emplace_back(sf::Vector2f(enemy_2_x, enemy_2_y), 3.0f, player_);
  
}

bool Level::IsCompleted() const {
  // Add check whether player has reached door.
  if (level_data_.enemies.empty()) {
    return true;
  }
  return false;
}

void Level::UpdateLevel(sf::RenderWindow &window) {
  // Update enemy positions and make them shoot.
  for (auto &it : level_data_.enemies) {
    it.Update(level_data_);
  }
  // Update positions of projectiles.
  for (auto &projectile: level_data_.projectiles) {
    projectile.Move();
  }
  // Handle projectile collisions
  HandleProjectileCollisions();
  // Update player tank position and make it shoot.
  player_.Update(window, level_data_);
  HandleItemPickUps();
}

void Level::DrawLevel(sf::RenderWindow &window) {
  for (const auto &it : level_data_.shields) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.walls) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.spikes) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.enemies) {
    it.Draw(window);
  }
  for (const auto &it : level_data_.projectiles) {
    it.Draw(window);
  }
  player_.Draw(window);
}

void Level::HandleProjectileCollisions() {
  for (auto projectile_it = level_data_.projectiles.begin(); projectile_it != level_data_.projectiles.end();) {
    // Check for collisions between wall and projectile.
    ProjectileWallCollisionResult result = NoCollision;
    for (const Wall &wall : level_data_.walls) {
      result = CollisionManager::ProjectileWall(*projectile_it, wall);
      if (result == ProjectileWallCollisionResult::Ricochet || result == ProjectileWallCollisionResult::Destroy) {
        // No need to check other walls
        break;
      }
    }
    if (result == ProjectileWallCollisionResult::Destroy) {
      // Remove projectile and move to next one.
      projectile_it = level_data_.projectiles.erase(projectile_it);
      continue;
    }
    // Check for collisions with other projectiles
    bool projectile_collision = false;
    for (auto other_projectile_it = std::next(projectile_it); other_projectile_it != level_data_.projectiles.end();) {
      projectile_collision = CollisionManager::ProjectileProjectile(*projectile_it, *other_projectile_it);
      if (projectile_collision) {
        level_data_.projectiles.erase(other_projectile_it);
        // No need to check other projectiles
        break;
      } else {
        ++other_projectile_it;
      }
    }
    if (projectile_collision) {
      // Remove projectile and move to next one
      projectile_it = level_data_.projectiles.erase(projectile_it);
      continue;
    }
    // Check for collisions with enemy tanks.
    bool enemy_collision = false;
    for (auto enemy_it = level_data_.enemies.begin(); enemy_it != level_data_.enemies.end();) {
      enemy_collision = CollisionManager::ProjectileTank(*projectile_it, *enemy_it);
      if (enemy_collision) {
        // No need to check other enemies
        level_data_.enemies.erase(enemy_it);
        break;
      } else {
        ++enemy_it;
      }
    }
    if (enemy_collision) {
      // Remove projectile and move to next one.
      projectile_it = level_data_.projectiles.erase(projectile_it);
      continue;
    }
    // Check for collision with player tank
    if (CollisionManager::ProjectileTank(*projectile_it, player_)) {
      //Projectile has hit a player, check if they have a shield.
      if (player_.hasShield()) {
        //Player has a shield. No game over but break the shield.
        player_.breakShield();
        std::cout << "Player was hit, but the shield saved them!" << std::endl;
        projectile_it = level_data_.projectiles.erase(projectile_it);
        continue;
      } else {
        // Game over
        std::cout << "Player was hit" << std::endl;
        projectile_it = level_data_.projectiles.erase(projectile_it);
        continue;
      }
    }
    //No collisions
    ++projectile_it;
  }
}

void Level::HandleItemPickUps() {
  OBB tankOBB = OBB(player_.GetShape());
 
  //Check if player is over a shield.
  for (auto shield = level_data_.shields.begin(); shield != level_data_.shields.end();){
    OBB shieldOBB = OBB(shield->GetShape());
    
    if(tankOBB.collides(shieldOBB)){
      //Player is over a shield. Check if player already has a shield.
      if (!player_.hasShield()){
        //Player doesn't have shield, enable it and remove it from the field.
        player_.setShield();
        level_data_.shields.erase(shield);
        break;
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