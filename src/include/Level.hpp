#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <list>
#include "Projectile.hpp"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Spike.hpp"
#include "PlayerTank.hpp"
#include "EnemyTank.hpp"
#include "CollisionManager.hpp"
#include "Shield.hpp"
#include "OBB.hpp"

class Level {
  public:
    Level(PlayerTank player, sf::RenderWindow &window);
    // Disallow copying
    Level(const Level &other) = delete;
    Level& operator=(const Level &other) = delete;

    void UpdateLevel(sf::RenderWindow &window);
    void DrawLevel(sf::RenderWindow &window);
    bool IsCompleted() const;

  private:
    std::vector<Wall> walls_;
    std::vector<Spike> spikes_;
    std::vector<Shield> shields_;
    std::list<EnemyTank> enemies_;
    PlayerTank player_;
    std::vector<Projectile> projectiles_;

    void HandleProjectileCollisions();
    
/**
 * @brief Handles item pick ups by checking if the player collides with some item.
 * If a collision with an item is detected then the correct actions are executed
 * depending on the item type.
 */
    void HandleItemPickUps();

};