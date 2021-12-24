#include <SFML/Graphics.hpp>
#include <math.h>

#include "PhysicsObject.h"


float distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main()
{
    // Render Main Window
    sf::RenderWindow window(sf::VideoMode(750, 750), "SFML Project");
    window.setFramerateLimit(60); // Capping FPS

    // New Physics Object
    float centerX = window.getSize().x / 2;
    float centerY = window.getSize().y / 2;

    PhysicsObject newObject;

    newObject.setYVelocity(-5.f);

    newObject.setWidth(50.f);
    newObject.setHeight(75.f);

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(newObject.getWidth(), newObject.getHeight()));
    rectangle.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        // Event Handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float theta = atan2(centerY - newObject.getY(), centerX - newObject.getX());
        float magnitude = distance(newObject.getX(), newObject.getY(), centerX, centerY) / 750;

        newObject.addXForce(magnitude * cos(theta));
        newObject.addYForce(magnitude * sin(theta));

        newObject.update();
        rectangle.setPosition(newObject.getX(), newObject.getY());

        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
