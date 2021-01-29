#include "octagon.hpp"

Octagon::Octagon() : z(0,0), R(0)
{}

Octagon::Octagon(Point x, double Rad) : z(x), R(Rad)
{
    if(R <= 0) {
        throw std::logic_error("always R > 0");
    }
}

void Octagon::output() {
    std::cout << "Coordinates of octagon: " << std::endl;
    double angle;
    for(int i = 0; i < 8;i++) {
        angle =  M_PI * i / 4;
        Point(R * cos(angle) + z.x(),R * sin(angle) + z.y()).P_output() ;
    }
}

double Octagon:: get_area() {
    return 4 * sin(M_PI / 4) * R * R;
}

Point Octagon::get_centre() {
    return z;
}