#include <iostream>
#include <typeinfo>

using namespace std;

class B {
    int x;
public:
    B (int a = 0) { x = a;}
    B (B & b) {x = b.x;}
    B (const B & b) {x = b.x;}
    virtual int g() const { return 222;}
    friend B operator+ (B& b1, B& b2);
};

class D : public B {
    int z;
public:
    static int y;
    D () {}
    D (int b) { z = b; }
};

int D :: y = 0;

// ne menyt

B operator+ (B& b1, B& b2) {
    return b1.x + b2.x;
}

int x = 1;

void f (float y) {
    cout << "::f(float) \n";
}

void f (char y) {
    cout << "::f(char) \n";
}
template <class T> void f (T t){
    cout << "f<> \n";
}

namespace kkk {
    int x = 2;
    void f (int c) {
        cout << c << "kkk::f(int) \n";
    }
}

using namespace kkk;

int main () {
    try {
        const D d;
        D && rrr = D();
        //const B & rb = d;
        //const D & rd = dynamic_cast <const D &>(rb);
        f(::x);
        f(10.5);
        cout << --d.y << endl << d.g() << endl;
        throw rrr;
    }
    catch( B&) { cout << "error BBB " << endl; }
    catch( ... ) { cout << "error ... " << endl; }
    return 0;
}
