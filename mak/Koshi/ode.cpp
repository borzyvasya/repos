#include <iostream>
#include <iomanip>

using namespace std;

int NRHS;
const int p = 8, NZ = 2;
const double EPS = 1e-04;

void runExplicitEuler(int, double, double, double[], double[], double[]);
void runImplicitEuler(int, double, double, double[], double[], const double[]);
void computeMinMax(int, const double[], const double[], const double[], double&, double&, double&);

void explicitEuler(double&, double, double[]);
void implicitEuler(double&, double, double[]);
void deriv(double, double[], double[]);

bool checkConvergence(double, double, double); // Функция для проверки сходимости

int main() {
    const int n = 10, m = n + 1;
    double xout[m] = { NAN }, yout1[m] = { NAN }, yout2[m] = { NAN }, testout[m] = { NAN };
    double miny, maxy, ystep;

    // [0, 1] - отрезок в параметрах
    runExplicitEuler(n, 0.0, 1.0, xout, yout1, testout);
    runImplicitEuler(n, 0.0, 1.0, xout, yout2, testout);
    computeMinMax(m, yout1, yout2, testout, miny, maxy, ystep);

    return EXIT_SUCCESS;
}

void runExplicitEuler(int n, double xbeg, double xend, double xout[], double yout1[], double testout[]) {
    double x = xbeg;
    double y[NZ] = { 1.0, 0.5 };  // y1(0) = 1, y2(0) = 0.5
    double h = (xend - xbeg) / n; // чтобы шаг был равен 0,1

    xout[0] = x;
    yout1[0] = y[0];
    NRHS = 0;

    cout << "EULER EXPLICIT SCHEME, with h = " << h << endl;
    cout << "FOR X = " << setw(p) << fixed << setprecision(4) << x
        << ", Y = " << setw(p) << y[0] << endl;

    for (int i = 0; i < n; ++i) {
        explicitEuler(x, h, y);

        // Проверка сходимости на каждом шаге
        if (checkConvergence(y[0], yout1[i], EPS)) {
            cout << "Convergence reached at step " << i << ", X = " << x << ", Y = " << y[0] << endl;
            break; // Выход из цикла, если сходимость достигнута
        }

        xout[i + 1] = x;
        yout1[i + 1] = y[0];
        cout << "FOR X = " << setw(p) << x
            << ", Y = " << y[0] << endl;
    }

    cout << "NRHS = " << NRHS << endl;
}

void runImplicitEuler(int n, double xbeg, double xend, double xout[], double yout2[], const double testout[]) {
    double x = xbeg;
    double y[NZ] = { 1.0, 0.5 };  // y1(0) = 1, y2(0) = 0.5
    double h = (xend - xbeg) / n;

    xout[0] = x;
    yout2[0] = y[0];
    NRHS = 0;

    cout << "\nEULER IMPLICIT SCHEME, with h = " << h << endl;
    cout << "FOR X = " << setw(p) << fixed << setprecision(4) << x
        << ", Y = " << setw(p) << y[0] << endl;

    for (int i = 0; i < n; ++i) {
        implicitEuler(x, h, y);

        // Проверка сходимости на каждом шаге
        if (checkConvergence(y[0], yout2[i], EPS)) {
            cout << "Convergence reached at step " << i << ", X = " << x << ", Y = " << y[0] << endl;
            break; // Выход из цикла, если сходимость достигнута
        }

        xout[i + 1] = x;
        yout2[i + 1] = y[0];
        cout << "FOR X = " << setw(p) << x
            << ", Y = " << y[0] << endl;
    }

    cout << "NRHS = " << NRHS << endl;
}

void computeMinMax(int m, const double yout1[], const double yout2[], const double testout[],
    double& miny, double& maxy, double& ystep) {
    miny = maxy = yout1[0];

    for (int i = 0; i < m; ++i) {
        miny = fmin(miny, fmin(yout1[i], fmin(yout2[i], testout[i])));
        maxy = fmax(maxy, fmax(yout1[i], fmax(yout2[i], testout[i])));
    }

    ystep = (maxy - miny) / 10.0;
}

void explicitEuler(double& x, double h, double y[]) {
    double dydx[NZ], yprev[NZ];
    deriv(x, y, dydx);

    for (int i = 0; i < NZ; i++) {
        yprev[i] = y[i];
        y[i] = yprev[i] + h * dydx[i];
    }

    x += h;
}

void implicitEuler(double& x, double h, double y[]) {
    double yprev[NZ], f1[NZ], f2[NZ], dydx[NZ];
    deriv(x, y, dydx);
    for (int i = 0; i < NZ; i++) {
        yprev[i] = y[i];
        f1[i] = dydx[i];
        y[i] = yprev[i] + h * f1[i];
    }

    x += h;
    deriv(x, y, dydx);
    for (int i = 0; i < NZ; i++) {
        f2[i] = dydx[i];
        y[i] = yprev[i] + h * (f1[i] + f2[i]) / 2.0;
    }
}


void deriv(double x, double y[], double dydx[]) {
    double num = y[0] * y[0];
    double denom = y[1] - x;

    if (fabs(denom) < EPS) denom = (denom >= 0 ? EPS : -EPS);

    NRHS += 1;

    dydx[0] = num / denom;
    dydx[1] = y[0] + 1.0;
}

bool checkConvergence(double ycurrent, double yprev, double eps) {
    return fabs(ycurrent - yprev) < eps;  // если разница меньше eps
}
