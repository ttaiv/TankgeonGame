#include <SFML/Graphics.hpp>
#include "include/Game.hpp"
#include "include/TankgeonHud.hpp"
#include "tests/Level_test.hpp"

int main() 
{

  // LevelTest::testCreation();

  sf::RenderWindow window;
  sf::View defaultView;
  window.create(sf::VideoMode::getFullscreenModes()[0],"Tankgeon!",sf::Style::Fullscreen);
  window.setPosition(sf::Vector2i(0,0));
  window.setFramerateLimit(60);
  window.setMouseCursorVisible(false);

  sf::Cursor cursor;
  if (cursor.loadFromSystem(sf::Cursor::Cross))
    window.setMouseCursor(cursor);

  sf::Texture texture;
  texture.loadFromFile("../src/assets/Inverted_sight.png");
  sf::Sprite sprite(texture);
  sprite.setScale(sf::Vector2f(0.1,0.1));
  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

  
  Game game(window);
  TankgeonHud hud(window, game);
  
  int delayClock_=0;
  // Game loop
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        window.close();
      else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
        if (game.gameState_ == Gameplay){
          game.gameState_ = Pause;
          game.PauseMusic();
        }else if (game.gameState_ == Pause){
          game.gameState_ = Gameplay;
          game.ContinueMusic();
        }
      }
    }
    sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    window.clear();

    if (game.gameState_ == Start){
      game.StartScreen();
    
    }else if (game.gameState_ == Gameplay) {
      game.Advance();
      hud.updateView(window);
      window.setView(hud);
      hud.draw(window);
      defaultView = window.getDefaultView();
      window.setView(defaultView);
    
    } else if (game.gameState_ == Pause){
      game.PauseScreen();
    
    } else if (game.gameState_ == GameOverLose || game.gameState_ == GameOverWin){
      game.EndScreen();
        if (delayClock_ >= 3*60) {
          delayClock_=0;
          game.ResetMenuMusic();
          game.StartScreen();
        }
      delayClock_++;
    }

    window.draw(sprite);
    window.display();
    
  }
  return 0;
} 
  
