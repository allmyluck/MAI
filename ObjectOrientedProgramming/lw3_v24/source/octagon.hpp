#ifndef OCTAGON_HPP
#define OCTAGON_HPP

#include "point_figure.hpp"

class Octagon : public Figure {
    private:
        Point z;
        double R;
    public:
        Octagon();
        Octagon(Point x, double Rad);
        void output() override;
        double get_area() override;
        Point get_centre() override;   
};

#endif