#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Tank.hpp"


class PlayerTank: public Tank {
  public:
    PlayerTank(sf::Vector2f initial_pos, float speed_scaler);
    
    void Update(sf::RenderWindow &window, LevelData &level_data);

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

    void UpdateShape(float rotation_angle, LevelData &level_data);
};