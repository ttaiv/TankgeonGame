#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "include/EnemyTank.hpp"
#include "include/PlayerTank.hpp"
#include "include/Projectile.hpp"
#include "include/Wall.hpp"
#include "include/Spike.hpp"
using namespace std;

int main() 
{

  
  sf::RenderWindow window;
  window.setFramerateLimit(60);
  window.create(sf::VideoMode::getFullscreenModes()[0],"Tankgeon!");
  window.setPosition(sf::Vector2i(0,0));
  window.setFramerateLimit(60);
  EnemyTank enemy(sf::Vector2f(200, 200), 0);
  PlayerTank player(sf::Vector2f(100, 100), 3);
  std::vector<Projectile> projectiles;

  //*** Temporary creation of the walls around the screen, these should probably be in the level class once implemented(?) ***

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

  

  vector<Wall> walls;
  vector<Spike> spikes;
  walls.push_back(topWall);
  walls.push_back(bottomWall);
  walls.push_back(leftWall);
  walls.push_back(rightWall);
  walls.push_back(leftVerticalWall);
  walls.push_back(rightVerticalWall);
  spikes.push_back(middleSpikes);

//******************************************************************************************************************************


  // Game loop
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
      // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
    }

    window.clear();
    player.Update(window, projectiles);
    player.Draw(window);
    enemy.Update(projectiles, player.GetShape());
    enemy.Draw(window);

    for (auto &w: walls) {
      w.Draw(window);
    }

    for (auto &s: spikes) {
      s.Draw(window);
    }

    
    // Note iterating over by reference!
    for (auto &proj: projectiles) {
      proj.Update(walls);
      proj.Draw(window);
    }

    window.display();
  }
  return 0;
}
