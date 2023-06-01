#include <iostream>
#include "date.h"

using namespace std;

Data :: Data (const Data & X) {
    _d = X._d;
    _m = X._m;
    _y = X._y;
};
int Data :: get_d () const {return _d;}
int Data :: get_m () const {return _m;}
int Data :: get_y () const {return _y;}
void Data :: operator= (const Data & X) {
    _d = X._d;
    _m = X._m;
    _y = X._y;
}
