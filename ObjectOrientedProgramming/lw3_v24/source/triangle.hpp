#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "point_figure.hpp"

class Triangle : public Figure {
    private: 
        Point z1, z2, z3;
    public:
        Triangle();
        Triangle(Point a, Point b, Point c);
        void output() override;
        double get_area() override;
        Point get_centre() override;
};

#endif