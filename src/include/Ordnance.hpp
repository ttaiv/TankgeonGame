#include <SFML/Graphics.hpp>
#pragma once

class Ordnance {
  public:
    bool IsActive() const { return is_active_; }
    void SetInactive() { is_active_ = false; }
    void SetActive() { is_active_ = true; }

    void Draw(sf::RenderWindow &window) const ;
    void UpdateAndDraw(sf::RenderWindow &window);

    virtual void Update() = 0;

  private:
    bool is_active_;
};