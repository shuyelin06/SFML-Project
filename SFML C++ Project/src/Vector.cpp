#include "Vector.h"
#include "math.h"

// Constructors
Vector::Vector() { x = y = 0; }
Vector::Vector(float x1, float y1) {
    x = x1;
    y = y1;
}

// Static Methods
Vector Vector::Standard_X() {
    Vector Standard_X(1,0);
    return Standard_X;
}
Vector Vector::Standard_Y() {
    Vector Standard_Y(0,1);
    return Standard_Y;
}

// Helper Methods
float Vector::dot(Vector v2) { return (x * v2.x + y * v2.y); }
float Vector::distance(Vector v2) { return sqrt(pow(v2.x - x, 2) + pow(v2.y - y, 2)); }

float Vector::projectionScalar(Vector v2) { return (dot(v2) / v2.dot(v2)); }

Vector Vector::displace(float x1, float y1) { return Vector(x + x1, y + y1); }
Vector Vector::relativeToCenter(float x1, float y1) { return Vector(x - x1, y - y1); }

Vector Vector::multiplyScalar(float f) { return Vector(x * f, y * f); }
Vector Vector::rotate(float angle) { return Vector(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)); }

Vector Vector::operator+(Vector v2) {
    Vector temp;

    temp.x = x + v2.x;
    temp.y = y + v2.y;
    
    return temp;
}