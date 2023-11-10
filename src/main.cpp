#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "include/EnemyTank.hpp"
#include "include/PlayerTank.hpp"
#include "include/Projectile.hpp"
#include "include/Wall.hpp"
#include "include/Spike.hpp"
#include "include/Level.hpp"
using namespace std;

int main() 
{

  
  sf::RenderWindow window;
  window.create(sf::VideoMode::getFullscreenModes()[0],"Tankgeon!");
  window.setPosition(sf::Vector2i(0,0));
  window.setFramerateLimit(60);
  
  PlayerTank player(sf::Vector2f(100, 100), 3);
  Level level1(player);
  level1.SetUpLevel(1, window);



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
    level1.updateLevel(window);
    level1.DrawLevel(window);

    window.display();
  }
  return 0;
}
