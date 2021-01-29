#include "point_figure.hpp"


Point::Point() : ox(0), oy(0)
{}


Point::Point(double a, double b): ox(a), oy(b)
{}


double Point::x() {
    return ox;
}


double Point::y() {
    return oy;
}


void Point::P_output() {
    std::cout << "Point : " << "(" << x() << "," <<  y() << ")" << std::endl;
}