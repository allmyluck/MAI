#include "triangle.hpp"

Triangle::Triangle() : z1(0,0), z2(0,0), z3(0,0)
{}

Triangle::Triangle(Point a, Point b, Point c) : z1(a), z2(b), z3(c)
{
    double x1,x2,x3;
    x1 = sqrt(pow(z2.x() - z1.x(), 2) + pow(z2.y() - z1.y(), 2));
	x2 = sqrt(pow(z3.x() - z2.x(), 2) + pow(z3.y() - z2.y(), 2));
	x3 = sqrt(pow(z1.x() - z3.x(), 2) + pow(z1.y() - z3.y(), 2));
	if (x1 + x2 <= x3 || x2 + x3 <= x1 || x1 + x3 <= x2) {
		throw std::logic_error("This is not triangle");
	}
}

void Triangle::output() {
    std::cout << "Coordinates of triangle: " << std::endl;
    Point(z1.x(), z1.y()).P_output();
    Point(z2.x(), z2.y()).P_output();
    Point(z3.x(), z3.y()).P_output();
}

double Triangle:: get_area() {
    return fabs(((z1.x() - z3.x()) * (z2.y() - z3.y()) - (z2.x() - z3.x()) * (z1.y() - z3.y())) / 2); 
}


Point Triangle::get_centre() {
    return Point((z1.x() + z2.x() + z3.x()) / 3, (z1.y() + z2.y() + z3.y()) / 3);
}