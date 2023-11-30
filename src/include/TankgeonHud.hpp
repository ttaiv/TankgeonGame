#include <SFML/Graphics.hpp>
#include "Game.hpp"

class TankgeonHud : public sf::View {
  public:
    
    TankgeonHud(const sf::RenderWindow& window, Game& game);

    void updateView(const sf::RenderWindow& window);

    void draw(sf::RenderWindow &window) const;
  
  private:
    sf::Font font_;
    Game& game_;
};