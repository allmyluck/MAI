#include "fazzynumber.h"

fazzynumber::fazzynumber(double x, double y) {
    a = x;
    e = y;
}

void fazzynumber::add(fazzynumber b) {
    double a1,e1;
    a1 = a + b.a;
    e1 = e + b.e;
    l = a1 - e1;
    c = a1;
    r = a1 + e1; 
}

void fazzynumber::sub(fazzynumber b) {
    double a1,e1;
    a1 = a - b.a;
    e1 = e + b.e;
    l = a1 - e1;
    c = a1;
    r = a1 + e1;  
}

void fazzynumber::mul(fazzynumber b) {
    double a1,e1,a1e2,a2e1;
    a1 = a * b.a;
    e1 = e * b.e;
    a1e2 = a * b.e;
    a2e1 = b.a * e;
    l = a1 - a1e2 - a2e1 + e1;
    c = a1;
    r = a1 + a1e2 + a2e1 + e1 ;
}

void fazzynumber::opp() {
    l = 1/(a + e);
    c = 1/a;
    r = 1/(a - e);     
}

void fazzynumber::div(fazzynumber b) {
    l = (a - e)/(b.a + b.e);
    c = a/b.a;
    r = (a + e)/(b.a - b.e);
}
    
void fazzynumber::print() {
    cout <<"(" << a - e << "," << a << "," << a + e << ")" << endl;
}

void fazzynumber::comp(fazzynumber b) {
    if(a > b.a) {
        cout << "A(x) > B(x)" << endl;
    } else if (a < b.a) {
        cout << "B(x) > A(x)"<< endl;
    } else {
       cout << "A(x) = B(x)" << endl;
    }
}

double fazzynumber::getleft() {
    return l;
}

double fazzynumber::getright() {
    return r;
}

double fazzynumber::getcentre() {
    return c;
}
    
double fazzynumber::getx() {
    return a;
}