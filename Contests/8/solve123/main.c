#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    enum {
        PERCENT = 100, //Converting a percent to a fraction
        ROUND = 10000 //"Round" rounds the numbers to the nearest integer
        //To avoid rounding 4 digits after the decimal point, multiply our number by 10000
        //To round a number to n decimal places, multiply by 10 ^ n
    };
    double kurs = atof(argv[1]);
    for (int i = 2; i < argc; i++) {
        double x = atof(argv[i]) * kurs / (PERCENT * 1.0);
        kurs += x;
        kurs = round(kurs * ROUND) / (ROUND * 1.0);
    }
    printf ("%.4lf\n", kurs);
    return 0;
}
