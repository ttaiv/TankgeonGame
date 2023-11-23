#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "OBB.hpp"
#include "constants.hpp"
#include <SFML/Audio.hpp>

struct LevelData;

class Tank : public sf::Transformable {
  public:
    /**
     * @brief Construct a new Tank object
     * 
     * @param initial position
     * @param base speed of the tank
     */
    Tank(sf::Vector2f initial_pos, float speed_scaler, int fire_cooldown);
    Tank(const Tank&) = delete;
    Tank& operator=(const Tank&) = delete;
    
    /**
     * @brief Get the Shape object
     * 
     * @return const sf::RectangleShape& 
     */
    const sf::RectangleShape& GetShape() const;

    /**
     * @brief Draws the shape on the window
     * 
     * @param window 
     */
    void Draw(sf::RenderWindow &window) const ;

    /**
     * @brief Creates and shoots a new projectile. Projectile is added to level.
     * 
     * @param vector of projectiles 
     * @param angle as radians
     */
    void Shoot(float angle, LevelData &level_data_, int ricochet_limit, int projectile_speed);

    bool GoForward(float margin, const LevelData &level_data_);
    bool GoBack(float margin, const LevelData &level_data_);
    bool TurnLeft(float margin, const LevelData &level_data_);
    bool TurnRight(float margin, const LevelData &level_data_);

    void SetPosition(sf::Vector2f position);
    bool ExplosionAnimationOver();

    void DrawExplosion(sf::RenderWindow &window);

    void SetHitTrue();
    
    bool IsHit();
    /**
     * @brief Scales the tank based on the screen size.
     * 
     * @param window_size 
     */
    void ScaleShape(sf::Vector2u window_size);

  protected:
    float speed_scaler_;
    int fire_cooldown_;
    int fire_cooldown_timer_ = 0;
    bool explosion_over_ = false;
    bool is_hit_ = false;
    int explosion_frames_ = 1;
    int shots_fired_ = 0;
    int frame_counter_ = 0;

    sf::RectangleShape tank_shape_;
    sf::RectangleShape turret_shape_;
    sf::CircleShape shield_shape_;
    sf::Texture explosion_texture_;
    sf::Sprite explosion_;
    sf::SoundBuffer fire_sound_buffer_;
    sf::SoundBuffer explosion_sound_buffer_;
    sf::Sound fire_sound_;
    sf::Sound explosion_sound_;
    sf::Texture chassis_texture_;
    sf::Texture turret_texture_;


    /**
     * @brief Takes in the planned next position and returns if it's crashing or not. margin parameter is to
     * scale the "hitbox" of the tank accordingly.
     * 
     * @param next_pos 
     * @param walls 
     * @param spikes 
     * @param margin 
     * @return true 
     * @return false 
     */
    bool IsCollided(sf::Vector2f next_pos, float margin, const LevelData &level_data_) const;

    bool CanShoot();

};