#include <SFML/Graphics.hpp>

class TankgeonHud : public sf::View {
  public:
    
    TankgeonHud(const sf::RenderWindow& window);

    void updateView(const sf::RenderWindow& window);

    void draw(sf::RenderWindow &window, int level_num, bool shield_status) const;
  
  private:
    sf::Font font_;
    
};