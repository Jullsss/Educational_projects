#include <iostream>

using namespace std;

class Rect {
    float _a, _b;
    float _x, _y;
public:
    Rect (float a = 1.f, float b = 1.f, float x = 0.f, float y = 0.f) : _a(a), _b(b), _x(x), _y(y) {};
    float get_x() const {return _x;}
    float get_y() const {return _y;}
    float get_a() const {return _a;}
    float get_b() const {return _b;}
    float get_sum_x() const {return _x + _a;}
    float get_sum_y() const {return _y + _b;}
    //float get_area () const {return _a * _b;}
    bool cross (Rect r2) const {
        if ((get_sum_y() >= r2._y && get_sum_y() <= r2.get_sum_y()) ||
            (r2.get_sum_y() >= _y && r2.get_sum_y() <= get_sum_y())) {
                if ((get_sum_x() >= r2._x && get_sum_x() <= r2.get_sum_x()) ||
                    (r2.get_sum_x() >= _x && r2.get_sum_x() <= get_sum_x())) {
                        return true;
                }
        }
        return false;
    }
    void contain (Rect &r2) {
        Rect r;
        r._x = min (_x, r2._x);
        r._y = min (_y, r2._y);
        r._a = max (_x + _a, r2._x + r2._a);
        r._b = max (_y + _b, r2._y + r2._b);
        _x = r._x;
        _y = r._y;
        _a = r._a - _x;
        _b = r._b - _y;
    }
    void intersection (Rect &r2) {
        Rect r;
        if (cross(r2)) {
            r._x = max (_x, r2._x);
            r._y = max (_y, r2._y);
            r._a = min (_x + _a, r2._x + r2._a);
            r._b = min (_y + _b, r2._y + r2._b);
        }
        _x = r._x;
        _y = r._y;
        _a = r._a - _x;
        _b = r._b - _y;
    }
    void moverect (float c, float d) {
        _x = _x + c;
        _y = _y + d;
    }
    void change (float c, float d) {
        _a = _a + c;
        _b = _b + d;
    }
    void print () const {
        cout << "a = " << get_a() << endl;
        cout << "b = " << get_b() << endl;
        cout << "x = " << get_x() << endl;
        cout << "y = " << get_y() << endl;
    }
};

int main()
{
    int x;
    Rect r1 (2.f, 2.f, 3.f, 4.f);
    Rect r2 (2.f, 2.f, 4.f, 3.f);
    cout << "MENU" << endl;
    cout << "Please select a number from 1 to 4." << endl;
    cout << "1: Move the rectangle." << endl;
    cout << "2: Change the size of the rectangle." << endl;
    cout << "3: Build the smallest rectangle containing 2 specified rectangles." << endl;
    cout << "4: Building a rectangle that is the intersection of 2 rectangles." << endl;

    while (1) {
        cin >> x;
        switch (x) {
            case 1: {
                r1.moverect(2, 4);
                r1.print();
                break;
            };
            case 2: {
                r1.change(2, 4);
                r1.print();
                break;
            };
            case 3: {
                r1.contain (r2);
                r1.print();
                break;
            };
            case 4: {
                r1.intersection (r2);
                r1.print();
                break;
            };
        }
    }
    return 0;
}
