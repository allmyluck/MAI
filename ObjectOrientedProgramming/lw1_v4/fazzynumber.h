#ifndef FAZZYNUMBER_H
#define FAZZYNUMBER_H
#include <iostream>
#include <cstdlib>
using namespace std;


class fazzynumber {
    private:
        double a,e,l,c,r;
    public:
    fazzynumber(double x, double y);
    void add(fazzynumber b) ;
    void sub(fazzynumber b);
    void mul(fazzynumber b);
    void opp();
    void div(fazzynumber b);
    void print();
    void comp(fazzynumber b);
    double getleft();
    double getright();
    double getcentre();
    double getx();
};

#endif
