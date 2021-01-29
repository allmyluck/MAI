#include <iostream>
#include <cmath>
// расчет точек правильного n-угольника
int main() {
    int center_y, center_x, n, R;
    std::cin >> n >> center_x >> center_y >> R;
    double angle;
     for(int i = 0; i < n; i++) {
        angle = (2 * M_PI * i) / n;
        std::cout << R * cos(angle) + center_x << std::endl;
        std::cout << R * sin(angle) + center_y << std::endl;
    }
    return 0;
}