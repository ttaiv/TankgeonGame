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
#include "include/TankgeonHud.hpp"
using namespace std;

int main() 
{
  
  sf::RenderWindow window;
  sf::View defaultView;
  window.create(sf::VideoMode::getFullscreenModes()[0],"Tankgeon!");
  window.setPosition(sf::Vector2i(0,0));
  window.setFramerateLimit(60);

  Game game(window);
  TankgeonHud hud(window);
  bool startScreenDisplayed = false;
  int proceed = 0;
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

    if (!startScreenDisplayed) {
      proceed = game.StartScreen();
    }

    if (startScreenDisplayed || proceed == 1){
      window.clear();
      game.Advance();
      hud.updateView(window);
      window.setView(hud);
      hud.draw(window, game.GetLevelNum(), game.GetShieldStatus());
      defaultView = window.getDefaultView();
      window.setView(defaultView);
      window.display();
      startScreenDisplayed = true;
    } 
  }
  return 0;
}
