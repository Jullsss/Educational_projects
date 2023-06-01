//Дата: Число, Месяц, Год

#include <iostream>
//#include "date.h"

using namespace std;

class Data {
    int _d, _m, _y;
public:
    Data (int d = 0, int m = 0, int y = 0) : _d(d), _m(m), _y(y) {};
    Data (const Data & X) {
        _d = X._d;
        _m = X._m;
        _y = X._y;
    };
    int get_d () const {return _d;}
    int get_m () const {return _m;}
    int get_y () const {return _y;}
    void operator= (const Data & X) {
        _d = X._d;
        _m = X._m;
        _y = X._y;
    }
    virtual void date () const = 0;
    virtual ~Data () {}
};

class Day : public Data {
    int _day;
public:
    Day (int d) : Data (d, 0, 0), _day(d) {}
    virtual void date () const {}
};

class Month : public Data {
public:
    Month (int m) : Data (0, m, 0) {}
    virtual void date () const {}
};

class Year : public Data {
public:
    Year (int y) : Data (0, 0, y) {}
    virtual void date () const {}
};

int main(int argc, char **argv)
{
    Data * examples[3];
    examples[0] = new Day(7);
    examples[1] = new Month(6);
    examples[2] = new Year(2000);

    for ( int i = 0; i < 3; ++i ) {
        if (examples[i]->get_d() == 0) {
            if (examples[i]->get_m() == 0) {
                cout << "Year " << examples[i]->get_y() << endl;
            } else {
                cout << "Month " << examples[i]->get_m() << endl;
            }
        } else {
            cout << "Day " << examples[i]->get_d() << endl;
        }
    }

    for ( int i = 0; i < 3; ++i )
        delete examples[i];

    Data *X = new Day (6);
    cout << "X Day " << X->get_d() << endl;

    Data *Y(X);
    cout << "Y Day " << Y->get_d() << endl;

    Data *Z = X;
    cout << "Z Day " << Z->get_d() << endl;
    delete X;
    return 0;
}
