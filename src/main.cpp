#include <SFML/Graphics.hpp>
#include "include/Game.hpp"
#include "include/TankgeonHud.hpp"

int main() 
{


  sf::RenderWindow window;
  sf::View defaultView;
  window.create(sf::VideoMode::getFullscreenModes()[0],"Tankgeon!");
  window.setPosition(sf::Vector2i(0,0));
  window.setFramerateLimit(60);

  Game game(window);
  TankgeonHud hud(window);
  // Game loop
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed)
        window.close();
      else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
        if (game.gameState_ == Gameplay){
          game.gameState_ = Pause;
        }else if (game.gameState_ == Pause){
          game.gameState_ = Gameplay;
        }
      }
    }
    

    if (game.gameState_ == Start){
      window.clear();
      game.StartScreen();
      window.display();
    
    }else if (game.gameState_ == Gameplay) {
      window.clear();
      game.Advance();
      hud.updateView(window);
      window.setView(hud);
      hud.draw(window, game.GetLevelNum(), game.GetShieldStatus());
      defaultView = window.getDefaultView();
      window.setView(defaultView);
      window.display();
    
    } else if (game.gameState_ == Pause){
      window.clear();
      game.PauseScreen();
      window.display();
    
    } else if (game.gameState_ == GameOverWin){
      window.clear();
      game.EndScreenWin();
      window.display();
    
    } else if (game.gameState_ == GameOverLose){
      window.clear();
      game.EndScreenLose();
      window.display();
    }
  }
  return 0;
} 
  
