#pragma once

#include <math.h>
#include <ostream>
#include <istream>

// Vector that represents a 2-dimensional (mathematical) vector
class Vector
{
public:
    // default constructor
    Vector();
    // constructor with values
    Vector(double const value1, double const value2);
    // check equality
    bool operator==(const Vector &other);
    // check inequality
    bool operator!=(const Vector &other);
    // add 2 vectors
    Vector operator+(const Vector &other);
    // multiply vector with a constant from the right
    Vector operator*(const double constant);
    // subtraction between 2 vectors
    Vector operator-(const Vector &other);
    // divide a vector
    Vector operator/(const double constant);

    // friends
    friend Vector operator*(const double constant, const Vector &other);
    friend Vector operator-(const Vector &other);
    
    // get the length of the vector
    double length();

    // friends
    friend std::ostream & operator<<(std::ostream &ostream, const Vector &other);
    friend std::istream &operator>>(std::istream &istream, Vector &other);

private:
    double component1;
    double component2;
};

// multiply vector with a constant from the left
Vector operator*(const double constant, const Vector &other);
// negate a vector
Vector operator-(const Vector &other);
// printable ostream
std::ostream &operator<<(std::ostream &ostream, const Vector &other);
// readable istream
std::istream &operator>>(std::istream &istream, Vector &other);
