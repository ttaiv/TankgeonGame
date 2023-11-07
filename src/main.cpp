#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "PlayerTank.hpp"
using namespace std;


float rotateToMouse(sf::RectangleShape shape,sf::RenderWindow &window ) 
{
    sf::Vector2f curPos = shape.getPosition();
    sf::Vector2i position = sf::Mouse::getPosition(window);

    // now we have both the sprite position and the cursor
    // position lets do the calculation so our sprite will
    // face the position of the mouse
    const float PI = 3.14159265;

    float dx = curPos.x - position.x;
    float dy = curPos.y - position.y;

    return (atan2(dy, dx)) * 180 / PI +180;
}
/*void shoot(sf::Vector2f playerPos){
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(10,10));
    sf::Vector2f curPos = shape.getPosition();
    
}*/


int main()
{
    int displayWidth = 600;
    int displayLength = 600;

    sf::RenderWindow window(sf::VideoMode(displayWidth, displayLength), "Tankgeon!");
    window.setFramerateLimit(60);

    sf::RectangleShape shape;
    shape.setOrigin(50,50);
    shape.setSize(sf::Vector2f(100,100));
    //shape.setFillColor(sf::Color::Green);

    sf::Vector2f pos(displayWidth/2,displayLength/2);
    int xSpeed = 2;
    int ySpeed = 5;
    shape.setPosition(pos);
    float rotOffset = cos(shape.getRotation() * 3.14 / 180) + sin(shape.getRotation() * 3.14 / 180);

    PlayerTank player(sf::Vector2f(100, 100), 2);

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {pos.x-=xSpeed; shape.setPosition(pos);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {pos.x+=xSpeed;shape.setPosition(pos);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {pos.y-=ySpeed;shape.setPosition(pos);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {pos.y+=ySpeed;shape.setPosition(pos);}
        shape.setPosition(pos);
        shape.setRotation(rotateToMouse(shape,window));
        /*pos.x +=xSpeed;
        pos.y +=ySpeed;
        shape.setPosition(pos);
        shape.getTransform().transformPoint(pos);
        shape.rotate(0.01);
        if(pos.x < 0 || pos.x>=displayLength-rotOffset*100) xSpeed = -xSpeed;
        if(pos.y<0  || pos.y>=displayWidth-rotOffset*100) ySpeed = -ySpeed;


        sf::Vector2f direction(0,0);
        //first get the direction the entity is pointed
        direction.x = (float) cos(shape.getRotation()*3.14/180);
        direction.y = (float) sin(shape.getRotation()*3.14/180);
        if (direction.x != 0 || direction.y !=0) {
            direction.x = sqrt(direction.x*direction.x);
            direction.y=sqrt(direction.y*direction.y);
        }
        //Then scale it by the current speed to get the velocity
        pos.x = direction.x * xSpeed;
        pos.y = direction.y * ySpeed;*/


        window.clear();
        player.Draw(window);
        window.draw(shape);
        window.display();
    }

    return 0;
}
