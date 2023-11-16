#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "include/EnemyTank.hpp"
#include "include/PlayerTank.hpp"
#include "include/Projectile.hpp"
#include "include/Wall.hpp"
#include "include/Spike.hpp"
#include "include/Level.hpp"
#include "include/Game.hpp"
using namespace std;

int main() 
{
  
  sf::RenderWindow window;
  window.create(sf::VideoMode::getFullscreenModes()[0],"Tankgeon!");
  window.setPosition(sf::Vector2i(0,0));
  window.setFramerateLimit(60);

  Game game(window);

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
    game.Advance();
    window.display();
  }
  return 0;
}
