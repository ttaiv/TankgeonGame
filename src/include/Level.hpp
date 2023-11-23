#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "CollisionManager.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Wall.hpp"
#include "Spike.hpp"
#include "PlayerTank.hpp"
#include "SniperTank.hpp"
#include "StationaryTank.hpp"
#include "Projectile.hpp"
#include "Shield.hpp"
#include "OBB.hpp"
#include <string>
#include <fstream>

struct LevelData {
  std::vector<Wall> walls;
  std::vector<Spike> spikes;
  std::list<std::unique_ptr<EnemyTank>> enemies;
  std::list<Projectile> projectiles;
  std::list<Shield> shields;
};


class Level {
  public:
    static constexpr int LEVEL_FILE_WIDTH = 32;
    static constexpr int LEVEL_FILE_HEIGHT = 9;

    Level();
    // Disallow copying
    Level(const Level &other) = delete;
    Level& operator=(const Level &other) = delete;

    /**
     * @brief Loads new level data from a text file. First clears all data of the current level.
     * 
     * @param level_number 
     * @param window_size 
     */
    void LoadFromFile(int level_number, sf::Vector2u window_size);
    void UpdateLevel(sf::RenderWindow &window);
    void DrawLevel(sf::RenderWindow &window);
    bool IsCompleted() const;
    const LevelData& GetLevelData();
    
    /**
     * @brief Getter function that returns the player tank.
     * 
     * @return const PlayerTank& 
     */
    const PlayerTank& GetPlayerTank() const;

    
  private:
    LevelData level_data_;
    PlayerTank player_; 

    void HandleProjectileCollisions();
    
/**
 * @brief Handles item pick ups by checking if the player collides with some item.
 * If a collision with an item is detected then the correct actions are executed
 * depending on the item type.
 */
    void HandleItemPickUps();

    void FillGridFromFile(std::vector<std::string> &level_grid, const std::string &filepath);

    void SetBorderWalls(sf::Vector2u window_size);

    void Clear();


    sf::Vector2u CountNeighboringObstacles(const std::vector<std::string> &level_grid,
      std::array<std::array<bool, LEVEL_FILE_WIDTH>, LEVEL_FILE_HEIGHT> &visited, int start_x, int start_y, char obstacle);
};