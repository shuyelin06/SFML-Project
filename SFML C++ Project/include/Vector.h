#pragma once
// All vectors are in the standard basis, around the origin (0,0)
struct Vector {
    // Member Variables
    float x;
    float y;

    // Constructors
    Vector(); // Default Constructor
    Vector(float x1, float y1); // Parameterized Constructor

    // Helper Methods
    static Vector Standard_X();
    static Vector Standard_Y();

    float dot(Vector v2); // Dot product between two vectors
    float distance(Vector v2); // Distance between two vectors

    float projectionScalar(Vector v2);

    Vector displace(float x1, float y1);
    Vector relativeToCenter(float x1, float y1);
    
    Vector multiplyScalar(float f);
    Vector rotate(float angle); // Rotate the vector about its origin 
    
    Vector operator+(Vector v2); // Add two vectors together
};