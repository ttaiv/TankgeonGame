#pragma once
#include "Item.hpp"

class Shield : public Item {
  public:
    Shield(sf::Vector2f position);

    /**
     * @brief Draws the shield into the window given as a parameter.
     * 
     * @param window 
     */
    virtual void Draw(sf::RenderWindow &window) const override;

    /**
     * @brief Returns the shieldShape.
     * 
     * @return sf::RectangleShape 
     */
    sf::RectangleShape GetShape() const;

  private:
    sf::Vector2f position_;
    sf::RectangleShape shieldShape_;
};
