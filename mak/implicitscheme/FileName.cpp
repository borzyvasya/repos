#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <iomanip>
#include <algorithm>
#include <discpp.h>

using namespace std;

bool RevMode = true, implicit = false;
const int jmax = 11, nmax = 200000, maxex = 20, ns = 5, p = 7;
const double half = 0.5, one = 1.0, six = 6.0, tmax = 3600.0, eps =
1.e-03, check = -87.0;

const double L = 1.0;      // длина стержня
const double scale = 100.0; // масштабный коэффициент температуры
const double tol = 0.1;  // пороговое значение времени для начальных условий

const double alpha = 1.1e-4; // теплопроводность меди 


void FTCS(double[], double[], double[], double);
void FTCS_TMS(double[], double[], double[], double);
void Test(double[], double[], double);
double RMS(double[], double[], double);
void Plot(double[], double[], double[], double[], double[], double[], double[], int);
void Thomas(double[], double[], double[], double[], double[], const int);

int main() {
    int i, j, NP = 0;
    double dis, tcal[jmax], sol[jmax], xl[jmax];
    double t1[jmax], t2[jmax], t3[jmax], t4[jmax], t5[jmax];
    for (i = 1; i <= ns; i++)
    {
        if (implicit)
        {
            dis = 1.99 / double(i + 7);
            FTCS(xl, tcal, sol, dis);
        }
        else
        {
            dis = 1.99 / double(i);
            FTCS_TMS(xl, tcal, sol, dis);
        }
        switch (i)
        {
        case(1):
            for (j = 0; j < jmax; j++)t1[j] =
                tcal[j];
            break;
        case(2):
            for (j = 0; j < jmax; j++)t2[j] =
                tcal[j];
            break;
        case(3):
            for (j = 0; j < jmax; j++)t3[j] =
                tcal[j];
            break;
        case(4):
            for (j = 0; j < jmax; j++)t4[j] =
                tcal[j];
            break;
        case(5):
            for (j = 0; j < jmax; j++)t5[j] =
                tcal[j];
            break;
        }
    }
    Plot(xl, t1, t2, t3, t4, t5, sol, jmax);
    cin.get();
    return EXIT_SUCCESS;
}

void Test(double te[], double x[], double time)
{
    int  j, m;
    double dxm, dam, dtm, Pi;
    Pi = atan(1.) * 4.;
    for (j = 0; j < jmax; j++)
    {
        te[j] = 100.0;
        for (m = 0; m < maxex - 1; m++)
        {
            dam = (2. * (m + 1) - 1.);
            dxm = dam * Pi * x[j]; dtm = - alpha * dam * dam * Pi * Pi * time;
            if (dtm < check)dtm = check;
            dtm = exp(dtm);
            if (dtm < eps) break;
            te[j] = te[j] - 400.0 / dam / Pi * sin(dxm) * dtm;
        }
    }
}

void FTCS(double x[], double td[], double te[], double s)
{
    int i, j, n, jmap;
    double delx, delt, t, ajm;
    jmap = jmax - 1;  ajm = double(jmap);
    delx = L / ajm; delt = delx * delx * s / alpha;
    double tn[jmax], dum[jmax];
    for (i = 0; i < jmax; i++)tn[i] = 0.0;
    n = 0; t = 0;
    //
    for (j = 0; j < jmax; j++)x[j] = delx * j;
    //
    do
    {
        tn[0] = 1.0; tn[jmax - 1] = 1.0;
        if (t < tol) {
            tn[0] = 0.5;
            tn[jmax - 1] = 0.5;
        }
        td[0] = scale * tn[0]; td[jmax - 1] = scale * tn[jmax -
            1];
        for (j = 1; j < jmap; j++)dum[j] = (1. - 2. * s) * tn[j]
            + s * (tn[j - 1] + tn[j + 1]);
        for (j = 1; j < jmap; j++)tn[j] = dum[j];
        for (j = 1; j < jmap; j++)td[j] = scale * tn[j];
        t = t + delt; n = n + 1;
        if (n >= nmax)break;
        cout << fixed << setprecision(2);
        cout << "t = " << setw(p) << t << " ";  for (i = 0; i
            < jmax; i++)cout << " " << setw(p) << td[i];
        cout << endl;
    } while (t <= tmax - delt);
    //
    Test(te, x, t);

    cout << endl << endl;

    cout << "t = " << setw(p) << t << " ";  
    for (i = 0; i < jmax; i++) cout << " " << setw(p) << te[i];

    cout << endl << "x = " << setw(p) << " ";  
    for (i = 0; i < jmax; i++) cout << " " << setw(p) << x[i];
    cout << endl << endl;

    cout << setprecision(4) << " Error estimate, RMS = "
        << RMS(te, td, ajm) << "; Delta x = " << delx << "; Delta t = " 
        << delt << "; Parameter S = " << s << endl;
}


void FTCS_TMS(double x[], double td[], double te[], double
    s)
{
    //
    //
    //
    int const jmap = jmax - 1, n = jmap - 1;
    int i, j, nlt;
    double delx, delt, t, ajm;
    double subd[n], diag[n], superd[n], b[n], u[n], tn[jmax];
    for (i = 0; i < n; i++)b[i] = 0.0;
    for (i = 0; i < n; i++)u[i] = 0.0;
    for (i = 0; i < n; i++)subd[i] = -s;
    for (i = 0; i < n; i++)diag[i] = 1.0 + 2.0 * s;
    for (i = 0; i < n; i++)superd[i] = -s;

    ajm = double(jmap);
    delx = L / ajm; delt = delx * delx * s / alpha;
    //                        forming an initial condition 
   //
    for (j = 0; j < jmax; j++)x[j] = delx * j;
    for (i = 0; i < jmax; i++)tn[i] = 0.0;
    nlt = 0; t = 0.0;
    //                                Let’s Go!
    do
    {
        tn[0] = 1.0; tn[jmap] = 1.0; // setting an boundary conditions
            if (t < tol) {
                tn[0] = 0.5;
                tn[jmap] = 0.5;
            }
            td[0] = scale * tn[0]; td[jmap] = scale * tn[jmap];
            for (j = 1; j < jmap; j++)b[j - 1] = tn[j];
            if (nlt == 0)
            {
            }
            else
                b[0] = s;
            b[n - 1] = s;
            b[0] = tn[1] + s; b[n - 1] = tn[jmap - 1] + s;
            Thomas(subd, diag, superd, b, u, n);
            for (j = 1; j < jmap; j++)tn[j] = u[j - 1]; //b[j - 1];
            for (j = 1; j < jmap; j++)td[j] = scale * tn[j];
            //
            t = t + delt; nlt = nlt + 1;
            for (j = 0; j < n; j++)u[j] = 0.0;
            if (nlt >= nmax) break;

            cout << fixed << setprecision(2);

            cout << "t = " << setw(p) << t << " ";  
            for (i = 0; i < jmax; i++)
                cout << " " << setw(p) << td[i];

            cout << endl;
    } 
    
    while (t <= tmax - delt);
    Test(te, x, t);
    cout << endl << endl;


    cout << "t = " << setw(p) << t << " ";  
    for (i = 0; i < jmax; i++)
        cout << " " << setw(p) << te[i];

    cout << endl << "x = " << setw(p) << " ";  
    for (i = 0; i < jmax; i++) 
        cout << " " << setw(p) << x[i];

    cout << endl << endl;
    cout << setprecision(4) << " Error estimate, RMS = "
        << RMS(te, td, ajm) << "; Delta x = " << delx << "; Delta t = " << 
        delt << "; Parameter S = " << s << endl;
}

double RMS(double te[], double td[], double ajm)
{
    int j;
    double rms, dmp, avs, sum = 0.0;
    for (j = 0; j < jmax; ++j)
    {
        dmp = te[j] - td[j];
        sum += dmp * dmp;
    }
    // estimate the errors
    avs = sum / (1.0 + ajm); rms = sqrt(avs);
    return rms;
}

void Thomas(double a[], double b[], double c[], double r[],
    double u[], const int n)
{
    int j;
    double bet;
    double gam[jmax] = { 0.0 };
    if (b[0] == 0.0)
    {
        cerr <<
            "tridag: rewrite equations" << endl;
        exit(1);
    }
    bet = b[0]; u[0] = r[0] / bet;
    /*
    *    Forward subsitution
    */
    for (j = 1; j < n; ++j)
    {
        gam[j] = c[j - 1] / bet; bet = b[j] - a[j] * gam[j];
        assert(bet != 0.0);
        u[j] = (r[j] - a[j] * u[j - 1]) / bet;
    }
    /*
    *    Back sustitution
    */
    for (j = n - 1; j >= 0; --j)
        u[j] = u[j] - gam[j + 1] * u[j + 1];
}

void Plot(double x[], double y1[], double y2[], double
    y3[], double y4[], double y5[], double sl[], int n)
{
    Dislin g;
    int i;
    char
        cdev[] = "XWIN";
    double xlab = 1.0, ylab;
    double miny, maxy, xbeg, xend;
    
    
    xbeg = x[0]; xend = x[n - 1];
    miny = y1[0];
    for (i = 0; i < n; ++i)miny = fmin(miny, y1[i]);
    for (i = 0; i < n; ++i)miny = fmin(miny, y2[i]);
    for (i = 0; i < n; ++i)miny = fmin(miny, y3[i]);
    for (i = 0; i < n; ++i)miny = fmin(miny, y4[i]);
    for (i = 0; i < n; ++i)miny = fmin(miny, y5[i]);
    for (i = 0; i < n; ++i)miny = fmin(miny, sl[i]);

    maxy = y1[0];
    for (i = 0; i < n; ++i)maxy = fmax(maxy, y1[i]);
    for (i = 0; i < n; ++i)maxy = fmax(maxy, y2[i]);
    for (i = 0; i < n; ++i)maxy = fmax(maxy, y3[i]);
    for (i = 0; i < n; ++i)maxy = fmax(maxy, y4[i]);
    for (i = 0; i < n; ++i)maxy = fmax(maxy, y5[i]);
    for (i = 0; i < n; ++i)maxy = fmax(maxy, sl[i]);
    ylab = (maxy - miny) / 10.0;
    g.metafl(cdev);
    g.setpag("da4l");
    if (RevMode)g.scrmod("revers");
    g.disini();
    g.pagera();
    g.hwfont();
    g.axspos(450, 1800);
    g.axslen(2200, 1200);
    g.name("Lenght, L", "x");
    g.name("Temperature, T", "y");
    g.labdig(-1, "x");
    g.ticks(10, "xy");
    g.titlin("Diff usion Equation", 1);
    g.graf(xbeg, xend, xbeg, xlab, miny, maxy, miny, ylab);
    g.title();
    g.thkcrv(2);
    g.color("green");
    g.curve(x, sl, n);
    g.color("red");
    g.curve(x, y1, n);
    g.color("white");
    g.curve(x, y2, n);
    g.color("blue");
    g.curve(x, y3, n);
    g.color("cyan");
    g.curve(x, y4, n);
    g.color("yellow");
    g.curve(x, y5, n);
    g.color("fore");
    g.dash();
    g.xaxgit();
    g.disfin();
}