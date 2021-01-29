#ifndef FIGURES_H
#define FIGURES_H
#include <iostream>
#include <tuple>
#include <cmath>


template <class T>
struct  Square {
    using type = T;
    using vertex_t = std::pair<T,T>;
    vertex_t a,b;
    Square(T x1, T y1,T x2, T y2) :  a(x1,y1),  b(x2,y2)
    {}
};


template <class T>
struct Triangle {
    using type = T;
    using vertex_t = std::pair<T,T>;
    vertex_t a,b,c;
    Triangle(T x1, T y1, T x2, T y2, T x3, T y3) : a(x1,y1), b(x2,y2), c(x3,y3)
    {}
};


template <class T>
struct Octagon {
    using type = T;
    using vertex_t = std::pair<T,T>;
    vertex_t a;T R;
    Octagon(T x1, T y1, T R) : a(x1,y1), R(R)
    {}
};


template <class T>
bool check(T R) {
    if(R > 0) {
        return true;
    } else {
        std::cout << "Error" << std::endl;
        return false;
    }
}


template <class T>
bool check(T x1,T y1,T x2, T y2) {
    if((x2 - x1 != y2 - y1) || (x2 == x1 && y2 == y1)) {
        std::cout << "Error" << std::endl;
        return false;
    } else {
        return true;
    }
}


template <class T>
bool check(T x1, T y1, T x2, T y2, T x3, T y3) {
        T a1,a2,a3;
        a1 = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        a2 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
        a3 = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
	    if (a1 + a2 <= a3 || a2 + a3 <= a1 || a1 + a3 <= a2) {
            std::cout << "Error" << std::endl;
		    return false;
	    } else {
            return true;
        }
    }

template <template <class> class F, class T>
typename std::enable_if< std::is_same< F<T>, Square<T> >::value, F<T> >::type information(F<T> s) {
    std::cout << "Square :" << std::endl;
    T x,y,sq;
    x = (s.a.first + s.b.first) / 2;
    y = (s.b.second + s.a.second) / 2;
    std::cout << "Center point (" << x << "," << y << ")" << std::endl;
    x = (s.b.first - s.a.first);
    y = (s.b.second - s.a.second);
    sq = (pow(x,2) + pow(y,2)) / 2;
    std::cout << "Area : " << sq << std::endl;
    std::cout << "Coordinates :" << std::endl;
    x = s.a.first;
    y = s.a.second;
    std::cout << "(" << x << "," << y << ")" << std::endl;
    x = s.a.first;
    y = s.b.second;
    std::cout << "(" << x << "," << y << ")" << std::endl;
    x = s.b.first;
    y = s.b.second;
    std::cout << "(" << x << "," << y << ")" << std::endl;
    x = s.b.first;
    y = s.a.second;
    std::cout << "(" << x << "," << y << ")" << std::endl;
    return s;
}


template <template <class> class F, class T>
typename std::enable_if< std::is_same< F<T>, Octagon<T> >::value, F<T> >::type information(F<T> o) {
    std::cout << "Octagon :" << std::endl;
    std::cout << "Center point (" << o.a.first << "," << o.a.second << ")" << std::endl;
    T sq,x,y,angle;
    sq = 4 * sin(M_PI / 4) * o.R * o.R;
    std::cout << "Area : " << sq << std::endl;
    std::cout << "Coordinates :" << std::endl;
    for(int i = 0; i < 8;i++) {
        angle =  M_PI * i / 4;
        x = o.R * cos(angle) + o.a.first;
        y = o.R * sin(angle) + o.a.second;
        std::cout << "(" << x << "," << y << ")" << std::endl;
    }
    return o;
}


template <template <class> class F, class T>
typename std::enable_if< std::is_same< F<T>, Triangle<T> >::value, F<T> >::type information(F<T> t) {
    std::cout << "Triangle :" << std::endl;
    T sq,x1,y1,x2,y2,x3,y3;
    x1 = (t.a.first + t.b.first + t.c.first) / 3;
    y1 = (t.a.second + t.b.second + t.c.second) / 3;
    std::cout << "Center point (" << x1 << "," << y1 << ")" << std::endl;
    x1 = t.a.first; y1 = t.a.second; 
    x2 = t.b.first; y2 = t.b.second;
    x3 = t.c.first; y3 = t.c.second;
    sq = fabs(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2);
    std::cout << "Area : " << sq << std::endl;
    std::cout << "Coordinates :" << std::endl;
    std::cout << "(" << x1 << "," << y1 << ")" << std::endl;
    std::cout << "(" << x2 << "," << y2 << ")" << std::endl;
    std::cout << "(" << x3 << "," << y3 << ")" << std::endl;
    return t;
}


template <class T>
void information(std::tuple<std::pair<T,T>> Octagon,T R) {
    std::cout << "Octagon :" << std::endl;
    T sq, ox, oy;
    std::cout << "Center point (" << std::get<0>(Octagon).first << "," << std::get<0>(Octagon).second << ")" << std::endl;
    sq = 4 * sin(M_PI / 4) * R * R;
    std::cout << "Area : " << sq << std::endl;
    T angle;
    std::cout << "Coordinates :" << std::endl;
    for(int i = 0; i < 8;i++) {
        angle =  M_PI * i / 4;
        ox = R * cos(angle) + std::get<0>(Octagon).first;
        oy = R * sin(angle) + std::get<0>(Octagon).second;
        std::cout << "(" << ox << "," << oy << ")" << std::endl;
    }
}


template <class T>
void information(std::tuple<std::pair<T,T>, std::pair<T,T>> Square) {
    std::cout << "Square :" << std::endl;
    T cx, cy, sq;
    cx = (std::get<0>(Square).first + std::get<1>(Square).first) / 2;
    cy = (std::get<0>(Square).second + std::get<1>(Square).second) / 2;
    std::cout << "Center point (" << cx << "," << cy << ")" << std::endl;
    cy = std::get<1>(Square).second - std::get<0>(Square).second;
    cx = std::get<1>(Square).first - std::get<0>(Square).first; 
    sq = (pow(cx,2) + pow(cy,2)) / 2;
    std::cout << "Area : " << sq << std::endl;
    std::cout << "Coordinates :" << std::endl;
    cx = std::get<0>(Square).first;
    cy = std::get<0>(Square).second;
    std::cout << "(" << cx << "," << cy << ")" << std::endl;
    cx = std::get<0>(Square).first;
    cy = std::get<1>(Square).second;
    std::cout << "(" << cx << "," << cy << ")" << std::endl;
    cx = std::get<1>(Square).first;
    cy = std::get<1>(Square).second;
    std::cout << "(" << cx << "," << cy << ")" << std::endl;
    cx = std::get<1>(Square).first;
    cy = std::get<0>(Square).second;
    std::cout << "(" << cx << "," << cy << ")" << std::endl;
}


template <class T>
void information(std::tuple<std::pair<T,T>, std::pair<T,T>, std::pair<T,T>> Triangle) {
    std::cout << "Triangle :" << std::endl;
    T x1,x2,x3,y1,y2,y3,sq;
    x1 = (std::get<0>(Triangle).first + std::get<1>(Triangle).first + std::get<2>(Triangle).first) / 3;
    y1 = (std::get<0>(Triangle).second + std::get<1>(Triangle).second + std::get<2>(Triangle).second) / 3;
    std::cout << "Center point (" << x1 << "," << y1 << ")" << std::endl;
    x1 = std::get<0>(Triangle).first; y1 = std::get<0>(Triangle).second; 
    x2 = std::get<1>(Triangle).first; y2 = std::get<1>(Triangle).second;
    x3 = std::get<2>(Triangle).first; y3 = std::get<2>(Triangle).second;
    sq = fabs(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2);
    std::cout << "Area : " << sq << std::endl;
    std::cout << "Coordinates :" << std::endl;
    std::cout << "(" << x1 << "," << y1 << ")" << std::endl;
    std::cout << "(" << x2 << "," << y2 << ")" << std::endl;
    std::cout << "(" << x3 << "," << y3 << ")" << std::endl;
}

#endif