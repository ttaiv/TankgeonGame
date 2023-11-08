#pragma once
#include <SFML/Graphics.hpp>

class Ordnance {
  public:
    Ordnance();
    bool IsActive() const;
    void SetInactive();
    void SetActive();

    void Draw(sf::RenderWindow &window) const ;
    void UpdateAndDraw(sf::RenderWindow &window);

    virtual void Update() = 0;

  private:
    bool is_active_;
};