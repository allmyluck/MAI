#include "square.hpp"

Square::Square() : z1(0,0), z2(0,0)
{}

Square::Square(Point a, Point b) : z1(a), z2(b)
{
    if((z1.x() - z2.x() != z1.y() - z2.y()) || (z1.x() == z2.x() && z1.y() == z2.y())) {
        throw std::logic_error("This are not opposite coordinates");
    }
}

void Square::output() {
    std::cout << "Coordinates of square: " << std::endl;
    Point(z1.x(),z1.y()).P_output();
    Point(z1.x(),z2.y()).P_output();
    Point(z2.x(),z2.y()).P_output();
    Point(z2.x(),z1.y()).P_output();
}

double Square:: get_area() {
    return (pow((z1.x() - z2.x()),2) + pow((z1.y() - z2.y()),2)) / 2;
}

Point Square::get_centre() {
    return Point((z1.x() + z2.x()) / 2, (z1.y() + z2.y()) / 2);
}
