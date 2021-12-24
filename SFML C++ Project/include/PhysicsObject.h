#pragma once 

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
        // Update: Main Method
        void update();

        // Accessor Methods
        float getX();
        float getY();

        float getTheta();

        float getWidth();
        float getHeight();
        
        // Mutator Methods
        void setWidth(float width1);
        void setHeight(float height1);
        
        void setXVelocity(float newVelocity);
        void setYVelocity(float newVelocity);

        void addTorque(float torque);
        void addXForce(float xForce);
        void addYForce(float yForce);
};