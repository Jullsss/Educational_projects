#include <iostream>

using namespace std;

struct A {
    int b;
    A(int a = 0) {b = a;}
    //A () {}
    virtual ~A() { if (!b) cout << "horosho\n";}
};

struct B : A {
    ~B () { cout << "Vse budet ";}
};

class complex {
    double re, im;
public:
    friend complex operator * (const complex & a, double b);
    ...
};

complex operator * (const complex & a, double b) {
    complex temp (a.re * b, a.im * b);
    return temp;
}


int main () {
    A a = 1;
    A * p = new B;
    delete p;
    return 0;
}
