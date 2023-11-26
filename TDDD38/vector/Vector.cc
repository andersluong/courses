#include "Vector.h"

#include <iostream>

// implement all the functions declared in Vector.h here

Vector::Vector()
{
    component1 = 0.0;
    component2 = 0.0;
}

Vector::Vector(double const value1, double const value2)
{
    component1 = value1;
    component2 = value2;
}

bool Vector::operator==(const Vector &other)
{
    if (this == &other)
    {
        return true;
    }
    if (component1 == other.component1 && component2 == other.component2)
    {
        return true;
    }

    return false;
};

bool Vector::operator!=(const Vector &other)
{
    return !operator==(other);
};

Vector Vector::operator+(const Vector &other)
{
    Vector resultVector = Vector();
    resultVector.component1 = this->component1 + other.component1;
    resultVector.component2 = this->component2 + other.component2;

    return resultVector;
}

Vector Vector::operator*(const double constant)
{
    return Vector(constant * this->component1, constant * this->component2);
}

Vector Vector::operator-(const Vector &other)
{
    return Vector(this->component1 - other.component1, this->component2 - other.component2);
}

Vector Vector::operator/(const double constant)
{
    return Vector(this->component1 / constant, this->component2 / 2);
}

double Vector::length()
{
    return pow(pow(this->component1, 2) + pow(this->component2, 2), 0.5);
}

Vector operator*(const double constant, const Vector &other)
{
    return Vector(constant * other.component1, constant * other.component2);
}

Vector operator-(const Vector &other)
{
    return Vector(other.component1 * -1, other.component2 * -1);
}

std::ostream &operator<<(std::ostream &ostream, const Vector &other)
{
    return ostream << '(' << other.component1 << ", " << other.component2 << ')';
}

std::istream &operator>>(std::istream &istream, Vector &other)
{
    char readChar;
    std::string value1, value2;
    bool start1 = false;
    bool start2 = false;
    istream >> std::ws;
    while (readChar != ')') {
        readChar = istream.get();
        if (istream.eof()) {
            istream.setstate(std::ios::failbit);
            return istream;
        }
        if (readChar == '(') {
            start1 = true;
            start2 = false;
            continue;
        } else if (readChar == ',') {
            start2 = true;
            start1 = false;
            continue;
        }

        if (start1) {
            value1 += readChar;
        } else if (start2 && readChar != ' ') {
            value2 += readChar;
        }
    }
    other.component1 = std::stod(value1);
    other.component2 = std::stod(value2);
    return istream;
}
