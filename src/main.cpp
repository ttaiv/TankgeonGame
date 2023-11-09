#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "include/EnemyTank.hpp"
#include "include/PlayerTank.hpp"
#include "include/Projectile.hpp"
using namespace std;

int main() 
{
  int displayWidth = 600;
  int displayLength = 600;
  sf::RenderWindow window(sf::VideoMode(displayWidth, displayLength), "Tankgeon!");
  window.setFramerateLimit(60);
  EnemyTank enemy(sf::Vector2f(200, 200), sf::Vector2f(0, 0));
  PlayerTank player(sf::Vector2f(100, 100), sf::Vector2f(3, 3));
  std::vector<Projectile> projectiles;

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
    
    // Note iterating over by reference!
    for (auto &proj: projectiles) {
      proj.Update();
      proj.Draw(window);
    }

    window.display();
  }
  return 0;
}
