#include <SFML/Graphics.hpp>

#include <vector>

#include "Constants.hpp"
#include "PhysicsObject.h"
#include <iostream>

int main()
{
    // Render Main Window
    sf::RenderWindow window(
        sf::VideoMode(RenderConstants::Resolution_X, RenderConstants::Resolution_Y), 
        "SFML Project"
    );
    window.setFramerateLimit(RenderConstants::Frames_Per_Second); // Capping FPS

    std::vector<PhysicsObject> objects = {};

    // New Physics Object
    PhysicsObject newObject(1.f, 1.f, 2.f, 1.5f, 2.f, 1.f, 1.f);
    newObject.setYVelocity(7.f);
    objects.push_back(newObject);

    PhysicsObject newObject2(1.f, 10.f, 5.f, 4.f, 2.f, 1.f, 1.f);
    newObject2.setYVelocity(-1.f);
    objects.push_back(newObject2);

    PhysicsObject newObject3(1.f, 30.f, 6.f, 1.5f, 2.f, 1.f, 1.f);
    newObject3.setYVelocity(-10.f);
    objects.push_back(newObject3);

    while (window.isOpen())
    {
        // Event Handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Object Updating
        for(auto& o: objects) { o.update(); }
        
        // Collision Checking
        for(std::size_t i = 0; i < objects.size() - 1; i++) {
            PhysicsObject& o1 = objects[i];

            for(std::size_t j = i + 1; j < objects.size(); j++) {
                PhysicsObject& o2 = objects[j];

                if(o1.intersects(o2)) {
                    o1.collision(o2);
                }
            }
        }

        // Rendering
        window.clear(sf::Color::Black);
        for(std::size_t i = 0; i < objects.size(); i++) {
            Vector* corners = objects[i].getCorners();

            sf::VertexArray lines(sf::LinesStrip, 5);      
            for(int j = 0; j < 5; j++) {
                lines[j] = sf::Vector2f(
                    corners[j % 4].x * RenderConstants::Pixels_Per_Meter, 
                    RenderConstants::Resolution_Y - corners[j % 4].y * RenderConstants::Pixels_Per_Meter
                    );
            }

            window.draw(lines);
            delete[] corners;
        }
        window.display();
    }

    return 0;
}
