#include <SFML/Graphics.hpp>

class PlayerTank {
  public:
    PlayerTank(sf::Vector2f initial_pos, int initial_speed);

    void UpdatePos();
    void Draw(sf::RenderWindow &window) const ;

  private:
    sf::Vector2f pos;
    int speed;
    sf::RectangleShape tankShape;
};