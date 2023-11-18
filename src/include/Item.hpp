#pragma once
#include <SFML/Graphics.hpp>

class Item {
  public:
    /**
     * @brief A pure virtual function that draws the item in the window given as a parameter.
     * 
     * @param window 
     */
    virtual void Draw(sf::RenderWindow &window) const = 0;  
};
