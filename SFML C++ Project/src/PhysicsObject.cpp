// Definition of PhysicsObject Methods
#include "PhysicsObject.h"

// Constructors
PhysicsObject::PhysicsObject() {
    x = y = theta = 0; // Setting Positions
    
    xVelocity = yVelocity = omega = 0; // Setting Velocities
    xAcceleration = yAcceleration = alpha = 0; // Setting Accelerations

    width = height = 1; // Setting width/height
    mass = inertia = 1; // setting mass/inertia
};

PhysicsObject::PhysicsObject(float x1, float y1, float theta1, float width1, float height1, float mass1, float inertia1) {
    // Setting Positions
    x = x1;
    y = y1;

    theta = theta1;

    // Setting Velocities
    xVelocity = yVelocity = omega = 0; 
    
    // Setting Accelerations
    xAcceleration = yAcceleration = alpha = 0; 

    // Setting Width/Height
    width = width1;
    height = height1;

    // Setting Mass/Inertia
    mass = mass1;
    inertia = inertia1;
}

// Accessor Methods
float PhysicsObject::getX() { return x; }
float PhysicsObject::getY() { return y; }

float PhysicsObject::getTheta() { return theta; }
float PhysicsObject::getWidth() { return width; }
float PhysicsObject::getHeight() { return height; }

// Mutator Methods
void PhysicsObject::setWidth(float width1) { width = width1; }
void PhysicsObject::setHeight(float height1) { height = height1; }

void PhysicsObject::setXVelocity(float newVelocity) { xVelocity = newVelocity; }
void PhysicsObject::setYVelocity(float newVelocity) { yVelocity = newVelocity; }

void PhysicsObject::addTorque(float torque) { alpha += torque / inertia; }
void PhysicsObject::addXForce(float xForce) { xAcceleration += xForce / mass; }
void PhysicsObject::addYForce(float yForce) { yAcceleration += yForce / mass; }

// Main Method Updating Position, Velocity, and Mass
void PhysicsObject::update() {
    // Update Velocities
    xVelocity += xAcceleration;
    yVelocity += yAcceleration;

    omega += alpha;

    // Set Accelerations to 0
    xAcceleration = yAcceleration = alpha = 0;

    // Update Positions
    x += xVelocity;
    y += yVelocity;

    theta += omega;
}
