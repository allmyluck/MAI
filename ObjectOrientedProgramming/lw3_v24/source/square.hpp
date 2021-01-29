#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "point_figure.hpp"

class Square : public Figure {
    private:
        Point z1,z2;
    public:
        Square();
        Square(Point x, Point y);
        void output() override;
        double get_area() override;
        Point get_centre() override;   
};

#endif