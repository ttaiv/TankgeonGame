#include "include/Level.hpp"
#include <iostream>

Level::Level(): player_(sf::Vector2f(100, 100), 3) {} // Player position will be updated in LoadFromFile call

void Level::SetBorderWalls(sf::Vector2u window_size) {
  Wall top_wall(sf::Vector2f(0, 0), sf::Vector2f(window_size.x, 30));
  Wall bottom_wall(sf::Vector2f(0, window_size.y - 0.09f * window_size.y), sf::Vector2f(window_size.x, 0.09f * window_size.y));
  Wall left_wall(sf::Vector2f(0, 0), sf::Vector2f(10, window_size.y));
  Wall right_wall(sf::Vector2f(window_size.x - 10, 0), sf::Vector2f(20, window_size.y));
  level_data_.walls.push_back(top_wall);
  level_data_.walls.push_back(bottom_wall);
  level_data_.walls.push_back(left_wall);
  level_data_.walls.push_back(right_wall);
}

// At the moment not needed as spikes (holes) and walls are built as single blocks.
sf::Vector2u Level::CountNeighboringObstacles(const std::vector<std::string> &level_grid,
  std::array<std::array<bool, LEVEL_FILE_WIDTH>, LEVEL_FILE_HEIGHT> &visited, int start_x, int start_y, char obstacle) {
  sf::Vector2u counts(0, 0);
  // Count x neighbors
  for (auto x = start_x + 1; x < LEVEL_FILE_WIDTH; ++x) {
    if (level_grid[start_y][x] == obstacle) {
      visited[start_y][x] = true;
      counts.x += 1;
    } else {
      break;
    }
  }
  // Count y neighbors
    for (auto y = start_y + 1; y < LEVEL_FILE_HEIGHT; ++y) {
    if (level_grid[y][start_x] == obstacle) {
      visited[y][start_x] = true;
      counts.y += 1;
    } else {
      break;
    }
  }
  return counts;
}

void Level::LoadFromFile(int level_number, sf::Vector2u window_size) {
  Clear();
  std::vector<std::string> level_grid;
  std::string filename = "level" + std::to_string(level_number) + ".txt";
  std::string filepath = "../src/levels/" + filename;
  // Fill level grid. It will be 9 x 32 matrix of chars.
  FillGridFromFile(level_grid, filepath);
  // Set border walls
  SetBorderWalls(window_size);
  // Build level using the grid.
  const int x_scaler = window_size.x / LEVEL_FILE_WIDTH;
  const int y_scaler = window_size.y / LEVEL_FILE_HEIGHT;
  // Create 9 x 32 array to keep track of already visited tiles, initialized to false.
  std::array<std::array<bool, LEVEL_FILE_WIDTH>, LEVEL_FILE_HEIGHT> visited {};
  for (auto y = 0; y < LEVEL_FILE_HEIGHT; ++y) {
    for (auto x = 0; x < LEVEL_FILE_WIDTH; ++x) {
      if (visited[y][x]) {
        continue;
      }
      visited[y][x] = true;
      char tile = level_grid[y][x];
      sf::Vector2u neighbor_count, dimensions;
      switch (tile)
      {
      case '#':
        // Border wall
        break;
      case ' ':
        // just blank
        break;
      case 'p':
        // player starting position
        player_.SetPosition(sf::Vector2f(x * x_scaler, y * y_scaler));
        break;
      case 'r':
        // red sniper tank
        // level_data_.enemies.pua(sf::Vector2f(x * x_scaler, y * y_scaler), 3.0f, player_);
        level_data_.enemies.push_front(std::make_unique<SniperTank>(sf::Vector2f(x * x_scaler, y * y_scaler), player_));
        break;
      case 's':
        // shield
        level_data_.shields.emplace_front(sf::Vector2f(x * x_scaler, y * y_scaler));
        break;
      case 'w':
        // walls are built with single blocks
        level_data_.walls.emplace_back(sf::Vector2f(x * x_scaler, y * y_scaler), sf::Vector2f(1 * x_scaler, 1 * y_scaler));
        break;
      case 'h':
        // hole, count neighboring h chars to calculate the total size
        // neighbor_count = CountNeighboringObstacles(level_grid, visited, x, y, 'h');
        // dimensions = neighbor_count + sf::Vector2u(1, 1);
        level_data_.spikes.emplace_back(sf::Vector2f(x * x_scaler, y * y_scaler), sf::Vector2f(1 * x_scaler, 1 * y_scaler));
        break;
      default:
        break;
      }
    }
  }
}

void Level::FillGridFromFile(std::vector<std::string> &level_grid, const std::string &filepath) {
  std::ifstream level_file(filepath);
  if (!level_file.is_open()) {
    throw std::runtime_error("Failed to open level file with path: " + filepath);
  }
  // File open successful.
  // Fill and validate grid.
  std::string line;
  int row = 0; // counter
  while (std::getline(level_file, line)) {
    // Remove possible carriage return
    if (line.back() == '\r') {
      line.pop_back();
    }
    // require 32 columns, first and last being '#'.
    if (line.length() != LEVEL_FILE_WIDTH || line.front() != '#' || line.back() != '#') {
      throw std::runtime_error(
        "Row length " + std::to_string(line.length()) + " on row " + std::to_string(row)
          + " in level file with path " + filepath + " was not 32 " + 
          "or the # chars were not in the correct place."
      );
    }
    // Row ok, add it to grid.
    level_grid.push_back(line);
    ++row;
  }
  if (level_grid.size() != LEVEL_FILE_HEIGHT) {
    // require 9 rows
    throw std::runtime_error(
      "Level file with path " + filepath + " had " + std::to_string(level_grid.size()) + " rows, 9 required"
    );
  }
  // Grid ready and validated.
}

bool Level::IsCompleted() const {
  // Add check whether player has reached door.
  if (level_data_.enemies.empty()) {
    return true;
  }
  return false;
}

void Level::UpdateLevel(sf::RenderWindow &window) {
  // Update enemy positions and make them shoot. Erase enemies for which explosion animation has ended.
  for (auto it = level_data_.enemies.begin(); it != level_data_.enemies.end();) {
    (*it)->Update(level_data_);
    if((*it)->ExplosionAnimationOver()){
      it = level_data_.enemies.erase(it);
    } else {
      ++it;
    }
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
  for (auto &it : level_data_.enemies) {
    it->Draw(window);
    if(it->IsHit()){
      it->DrawExplosion(window);
    }
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
    for (auto &enemy : level_data_.enemies) {
      enemy_collision = CollisionManager::ProjectileTank(*projectile_it, *enemy);
      if (enemy_collision) {
        // No need to check other enemies
        enemy->SetHitTrue();
        break;
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
      if (player_.HasShield()) {
        //Player has a shield. No game over but break the shield.
        player_.BreakShield();
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
      if (!player_.HasShield()){
        //Player doesn't have shield, enable it and remove it from the field.
        player_.SetShield();
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

const PlayerTank& Level::GetPlayerTank() const {
      return player_;
    }

void Level::Clear() {
  level_data_.enemies.clear();
  level_data_.projectiles.clear();
  level_data_.shields.clear();
  level_data_.spikes.clear();
  level_data_.walls.clear();
}