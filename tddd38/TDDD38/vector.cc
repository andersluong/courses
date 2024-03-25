#include "Vector.h"

// implement all the functions declared in Vector.h here
Vector::Vector() {
    data = new double[0][0];
}

Vector::Vector(int rowLength, int colLength) {
    data = new double[rowLength][colLength];
}

