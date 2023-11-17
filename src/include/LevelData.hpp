#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Wall.hpp"
#include "Spike.hpp"
#include "PlayerTank.hpp"
#include "EnemyTank.hpp"
#include "Projectile.hpp"

class Tank; //forward declaration to avoid circular declaration


struct LevelData
{
  std::vector<Wall> walls_;
  std::vector<Spike> spikes_;
  std::list<EnemyTank> enemies_;
  std::vector<Projectile> projectiles_;
};