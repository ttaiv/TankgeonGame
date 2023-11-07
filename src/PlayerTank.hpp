#include <SFML/Graphics.hpp>

class PlayerTank {
  public:
    PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed);

    void UpdatePos();
    void Draw(sf::RenderWindow &window) const ;
    void UpdatePosAndDraw(sf::RenderWindow &window);

  private:
    sf::Vector2f pos;
    sf::Vector2f speed;
    sf::RectangleShape tankShape;
};