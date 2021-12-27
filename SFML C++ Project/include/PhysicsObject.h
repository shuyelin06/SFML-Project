#pragma once 

#include "Vector.h"

// PhysicsObject Class Declaration
class PhysicsObject {
    public: // Constructors
        // Default Constructor
        PhysicsObject(); 
        // Parameterized Constructor
        PhysicsObject(float x1, float y1, float theta1, float width1, float height1, float mass1, float inertia1);
    
    protected: // Member Variables
        // Positions
        float x, y; // Linear Position 
        float theta; // Rotational Position
        
        // Velocities
        float xVelocity, yVelocity; // Linear Velocity
        float omega; // Rotational Velocity

        // Accelerations
        float xAcceleration, yAcceleration; // Linear Acceleration
        float alpha; // Rotational Acceleration

        // Width, Height
        float width, height;
        
        // Mass, Inertia (About Center of Mass)
        float mass, inertia;
    
    public: // Class Methods
        void update(); // Update the Object
        bool intersects(PhysicsObject &o); // Check for Intersections
        void collision(PhysicsObject &o);

        // Accessor Methods
        float getX();
        float getY();
        float getTheta();
        
        float getXVelocity();
        float getYVelocity();

        float getWidth();
        float getHeight();
        
        Vector* getCorners();

        // Mutator Methods
        void setX(float x1);
        void setY(float y1);

        void setXVelocity(float newVelocity);
        void setYVelocity(float newVelocity);

        void addTorque(float torque);
        void addXForce(float xForce);
        void addYForce(float yForce);

        void setWidth(float width1);
        void setHeight(float height1);        
};

namespace ObjectHelperMethods {
    Vector* getAxes(PhysicsObject &p);
    Vector* getCorners(Vector* axes, float centerX, float centerY);

    bool withinAxis(float proj1, float proj2);
    bool checkProjections(Vector* originAxes, Vector* originCorners, Vector* otherAxes, Vector* otherCorners);
}