#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.hpp"

// This class is probably unnecessary and will possibly get deleted

class Ordnance {
  public:
    Ordnance();
    bool IsActive() const;
    void SetInactive();
    void SetActive();

    void Draw(sf::RenderWindow &window) const ;
    void UpdateAndDraw(sf::RenderWindow &window);

    // virtual void Update(std::vector<Wall> &walls) = 0;

  private:
    bool is_active_;
};