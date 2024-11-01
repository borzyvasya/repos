/////////////////////////////////////////////////////////////////
//                                                             //                        
//                     DISLIN driver                           //
//                                                             //
//          Dr. Malik S. Maxutov , MGSU 2021                   //
//                                                             //
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <float.h>
#include <algorithm>
#include "discpp.h"
//
//   Globals
//
const int N = 100;
const double  one = 1.0, four = 4.0;
const double full = 3.6e+02, half = 1.8e+02;
bool RevMode = true;
//
void Plot(double xdeg[], double y1[], double y2[], int n);
using namespace std;
int main()
{
    double xdeg[N], y1[N], y2[N];
    double Pi, fpi, step, x;
    int n = 100, i;
    Pi = atan(one) * four; fpi = Pi / half;
    //
    step = full / (n - 1);
    //
    for (i = 0; i < n; i++)
    {
        xdeg[i] = i * step;     x = xdeg[i] * fpi;
        y1[i] = sin(x); y2[i] = cos(x);
    }
    cout << "for DISLIN plotting routine start, please press any key .." << endl;
    cin.get();
    Plot(xdeg, y1, y2, n);
    return EXIT_SUCCESS;
}
void Plot(double xdeg[], double y1[], double y2[], int n)
{
    Dislin g;
    char   cdev[] = "XWIN";
    double xlab = half / 6, ylab = one / 4;
    double miny, maxy, xbeg, xend;
    //
    xbeg = xdeg[0]; xend = xdeg[n - 1];
    maxy = max(*max_element(y1, y1 + n), *max_element(y2, y2 + n));
    miny = min(*min_element(y1, y1 + n), *min_element(y2, y2 + n));
    //
    g.metafl(cdev);
    g.setpag("da4l");
    if (RevMode)g.scrmod("revers");
    g.disini();
    g.pagera();
    g.hwfont();
    g.axspos(450, 1800);
    g.axslen(2200, 1200);

    g.name("X-axis", "x");
    g.name("Y-axis", "y");

    g.labdig(-1, "x");
    g.ticks(10, "xy");

    g.titlin("Demonstration of CURVE", 1);
    g.titlin("SIN(X), COS(X)", 3);

    g.graf(xbeg, xend, xbeg, xlab, miny, maxy, miny, ylab);
    g.title();

    g.color("red");
    g.curve(xdeg, y1, n);
    g.color("blue");
    g.curve(xdeg, y2, n);

    g.color("green");
    g.dash();
    g.xaxgit();
    g.disfin();

}
