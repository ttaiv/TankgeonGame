#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class PlayerTank {
  public:
    PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed);

    void UpdatePosAndRotation(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window) const ;
    void UpdateAndDraw(sf::RenderWindow &window);
    void Shoot();

  private:
    sf::Vector2f pos;
    sf::Vector2f speed;
    sf::RectangleShape tankShape;
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float
     */
    float GetRotationAngle(sf::RenderWindow &window);

};