// Definition of PhysicsObject Methods
#include "PhysicsObject.h"

#include "Constants.hpp"
#include "Vector.h"

/*
>> PhysicsObject Constructors
*/
// Default Constructor
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

/*
>> PhysicsObject Update
*/
void PhysicsObject::update() {
    // Update Velocities
    xVelocity += xAcceleration / RenderConstants::Frames_Per_Second;
    yVelocity += yAcceleration / RenderConstants::Frames_Per_Second;

    omega += alpha;

    // Set Accelerations to 0
    xAcceleration = yAcceleration = alpha = 0;

    // Update Positions
    x += xVelocity / RenderConstants::Frames_Per_Second;
    y += yVelocity / RenderConstants::Frames_Per_Second;

    theta += omega;
}

/*
>> PhysicsObject Intersects
*/
bool PhysicsObject::intersects(PhysicsObject &o) {
    // Defining Variables
    Vector* originAxes = ObjectHelperMethods::getAxes(*this);
    Vector* otherAxes = ObjectHelperMethods::getAxes(o);

    Vector* originCorners = ObjectHelperMethods::getCorners(originAxes, x, y);
    Vector* otherCorners = ObjectHelperMethods::getCorners(otherAxes, o.x, o.y);

    // Taking all Corners Relative to the Other Object
    for(int i = 0; i < 4; i++) {
        originCorners[i] = originCorners[i].relativeToCenter(o.x, o.y);
        otherCorners[i] = otherCorners[i].relativeToCenter(x, y); 
    }

    // Finding result
    bool result = ObjectHelperMethods::checkProjections(originAxes, originCorners, otherAxes, otherCorners);

    // Freeing Memory
    delete[] originAxes;
    delete[] otherAxes;
    delete[] originCorners;
    delete[] otherCorners;

    // Returning Result
    return result;
}

/*
>> PhysicsObject Collision
*/
void PhysicsObject::collision(PhysicsObject &o) {
    // Updating X Velocities
    float C1X = mass * xVelocity + o.mass * o.xVelocity;
    float C2X = -PhysicsConstants::Restitution_Coefficient * (o.xVelocity - xVelocity);

    xVelocity = (C1X + mass * C2X) / (mass + o.mass) - C2X;
	o.xVelocity = (C1X + mass * C2X) / (mass + o.mass);

	// Updating Y Velocities
	float C1Y = mass * yVelocity + o.mass * o.yVelocity;
	float C2Y = -PhysicsConstants::Restitution_Coefficient * (o.yVelocity - yVelocity);

	yVelocity = (C1Y + mass * C2Y) / (mass + o.mass) - C2Y;
	o.yVelocity = (C1Y + mass * C2Y) / (mass + o.mass);
}

/*
>> PhysicsObject Accessors
*/
float PhysicsObject::getX() { return x; } // Get X Position
float PhysicsObject::getY() { return y; } // Get Y Position

float PhysicsObject::getTheta() { return theta; } // Get Angle of Rotation

float PhysicsObject::getXVelocity() { return xVelocity; } // Get X Velocity
float PhysicsObject::getYVelocity() { return yVelocity; } // Get Y Velocity

float PhysicsObject::getWidth() { return width; } // Get Width
float PhysicsObject::getHeight() { return height; } // Get Height

Vector* PhysicsObject::getCorners() { // Get Corners (Relative to (0,0))
    Vector* axes =  ObjectHelperMethods::getAxes(*this);
    Vector* corners = ObjectHelperMethods::getCorners(axes, x, y);
    
    delete[] axes;
    return corners;
}

/*
>> PhysicsObject Mutators
*/
void PhysicsObject::setX(float x1) { x = x1; } // Set X Position
void PhysicsObject::setY(float y1) { y = y1; } // Set Y Position

void PhysicsObject::setXVelocity(float newVelocity) { xVelocity = newVelocity; } // Set X Velocity
void PhysicsObject::setYVelocity(float newVelocity) { yVelocity = newVelocity; } // Set Y Velocity

void PhysicsObject::addTorque(float torque) { alpha += torque / inertia; } // Add a Torque
void PhysicsObject::addXForce(float xForce) { xAcceleration += xForce / mass; } // Add a X Force
void PhysicsObject::addYForce(float yForce) { yAcceleration += yForce / mass; } // Add a Y Force

void PhysicsObject::setWidth(float width1) { width = width1; } // Set Width 
void PhysicsObject::setHeight(float height1) { height = height1; }// Set Height

/*
>> ObjectHelperMethods
*/
// Find the axes of the given physics object
Vector* ObjectHelperMethods::getAxes(PhysicsObject &p) {
    Vector* axes = new Vector[2];

    // Find rotated x axis
    axes[0] = Vector::Standard_X().rotate(p.getTheta()).multiplyScalar(p.getWidth() / 2);
    // Find rotated y axis
    axes[1] = Vector::Standard_Y().rotate(p.getTheta()).multiplyScalar(p.getHeight() / 2);

    return axes;
}
// Find the corners of the given physics object
Vector* ObjectHelperMethods::getCorners(Vector* axes, float centerX, float centerY) {
    Vector* corners = new Vector[4];

    // Find every corner RELATIVE TO THE ORIGIN (0,0)
    corners[0] = (axes[0].multiplyScalar(-1) + axes[1]).displace(centerX, centerY);
    corners[1] = (axes[0] + axes[1]).displace(centerX, centerY);
    corners[2] = (axes[0] + axes[1].multiplyScalar(-1)).displace(centerX, centerY);
    corners[3] = (axes[0].multiplyScalar(-1) + axes[1].multiplyScalar(-1)).displace(centerX, centerY);

    return corners;
}
bool ObjectHelperMethods::withinAxis(float proj1, float proj2) {
    if(-1 <= proj1 && proj1 <= 1) return true;
    else if(-1 <= proj2 && proj2 <= 1) return true;
    else if(proj1 <= -1 && 1 <= proj2) return true;
    else return false;
}
bool ObjectHelperMethods::checkProjections(Vector* originAxes, Vector* originCorners, Vector* otherAxes, Vector* otherCorners) {
    // Checking First Projection
    if(!ObjectHelperMethods::withinAxis(
        originCorners[0].projectionScalar(otherAxes[0]),
        originCorners[2].projectionScalar(otherAxes[0])
    )) return false;

    // Checking Second Projection
    if(!ObjectHelperMethods::withinAxis(
        originCorners[1].projectionScalar(otherAxes[1]),
        originCorners[3].projectionScalar(otherAxes[1])
    )) return false;

    // Checking Third Projection
    if(!ObjectHelperMethods::withinAxis(
        otherCorners[0].projectionScalar(originAxes[1]),
        otherCorners[2].projectionScalar(originAxes[1])
    )) return false;

    // Checking Fourth Projection
    if(!ObjectHelperMethods::withinAxis(
        otherCorners[1].projectionScalar(originAxes[0]),
        otherCorners[3].projectionScalar(originAxes[0])
    )) return false;

    return true;
}