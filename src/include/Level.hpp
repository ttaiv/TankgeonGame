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
#include "BurstTank.hpp"
#include "Projectile.hpp"
#include "Shield.hpp"
#include "OBB.hpp"
#include <string>
#include <fstream>

/**
 * @brief Struct that contains level data. Used to pass level data for tanks.
 * 
 */
struct LevelData {
  std::vector<Wall> walls;
  std::vector<Spike> spikes;
  std::list<std::unique_ptr<EnemyTank>> enemies;
  std::list<Projectile> projectiles;
  std::list<Shield> shields;
};

/**
 * @brief Class that represents a level in the game. When necessary, loads level data from a text file.
 * 
 */
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
    /**
     * @brief Updates the level by updating all tanks and projectiles. Also handles collisions.
     * 
     * @param window that displays the game
     */
    void UpdateLevel(sf::RenderWindow &window);
    /**
     * @brief Draws the level by drawing all tanks, projectiles, and walls.
     * 
     * @param window that displays the game
     */
    void DrawLevel(sf::RenderWindow &window);
    /**
     * @brief Checks if the level is completed. A level is completed if all enemies are destroyed.
     * 
     * @return true if the level is completed
     * @return false if the level is not completed
     */
    bool IsCompleted() const;
    /**
     * @brief Getter function that returns the level data.
     * 
     * @return const LevelData& 
     */
    const LevelData& GetLevelData();
    /**
     * @brief Getter function that returns the player tank.
     * 
     * @return const PlayerTank& 
     */
    PlayerTank& GetPlayerTank();

    void ResetPlayer();

    
  private:
    LevelData level_data_;
    PlayerTank player_; 
    sf::Texture background_texture_;
    sf::Sprite background_;

    /**
     * @brief Checks if projectiles collide with anything. If a collision is detected then the correct actions are executed.
     * 
     */
    void HandleProjectileCollisions();
    /**
     * @brief Handles item pick ups by checking if the player collides with some item.
     * If a collision with an item is detected then the correct actions are executed
     * depending on the item type.
     */
    void HandleItemPickUps();
    /**
     * @brief Fills two dimensional vector with level data from a text file.
     * 
     * @param level_grid 
     * @param filepath 
     */
    void FillGridFromFile(std::vector<std::string> &level_grid, const std::string &filepath);
    /**
     * @brief Creates boundary walls for the level.
     * 
     * @param window_size 
     */
    void SetBorderWalls(sf::Vector2u window_size);
    /**
     * @brief Clears all level data.
     * 
     */
    void Clear();

    // Not needed in current implementation
    sf::Vector2u CountNeighboringObstacles(const std::vector<std::string> &level_grid,
      std::array<std::array<bool, LEVEL_FILE_WIDTH>, LEVEL_FILE_HEIGHT> &visited, int start_x, int start_y, char obstacle);
};