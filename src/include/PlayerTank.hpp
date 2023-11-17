#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Tank.hpp"


class PlayerTank: public Tank {
  public:
    PlayerTank(sf::Vector2f initial_pos, float speed_scaler, LevelData &level_data);
    
    void Update(sf::RenderWindow &window);

  private:
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float in radians
     */
    sf::Texture textureNoTurret_;
    sf::Texture textureTurret_;
    float GetTurretRotationAngle(sf::RenderWindow &window);

    void UpdateShape(float rotation_angle);
};