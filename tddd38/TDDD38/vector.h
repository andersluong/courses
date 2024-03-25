#pragma once

// Declare your class here
class Vector {
    public:
        Vector();
        Vector(int size);
        ~Vector();
        operator==(const Vector& v);
        double get(int i);
        void set(int i, double x);
        int size();

    private:
        double* data;
}