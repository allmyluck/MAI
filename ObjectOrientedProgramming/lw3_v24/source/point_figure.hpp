#ifndef POINT_FIGURE_HPP
#define POINT_FIGURE_HPP
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>


class Point {
    private:
        double ox,oy;
    public:
        Point();
        Point(double a, double b);
        double x();
        double y();
        void P_output();
};


class Figure {
    public:
        virtual void output() = 0;
        virtual double get_area() = 0;
        virtual Point get_centre() = 0;
};

#endif