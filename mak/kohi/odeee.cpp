#include <iostream>
#include <iomanip>

using namespace std;

int NRHS;  // Счётчик числа вызовов производной (для тестирования)
const int p = 8, NZ = 2;  // p - количество знаков для вывода, NZ - количество переменных в системе
const double EPS = 1e-04;  // Порог для сходимости

void runExplicitEuler(int, double, double, double[], double[], double[]);
void runImplicitEuler(int, double, double, double[], double[], const double[]);
void computeMinMax(int, const double[], const double[], const double[], double&, double&, double&);
void explicitEuler(double&, double, double[]);
void implicitEuler(double&, double, double[]); // Correct definition of implicitEuler
void deriv(double, double[], double[]);  // Вычисление производных
void reduceStep(double&); // Уменьшаем шаг в два раза
bool checkConvergence(double, double, double); // Проверка сходимости


int main() {
    const int n = 10, m = n + 1;  // n - количество шагов, m - количество точек
    double xout[m] = { NAN }, yout1[m] = { NAN }, yout2[m] = { NAN }, testout[m] = { NAN };
    double miny, maxy, ystep;

    // Решение задачи Коши для явной и неявной схемы Эйлера
    runExplicitEuler(n, 0.0, 1.0, xout, yout1, testout);
    runImplicitEuler(n, 0.0, 1.0, xout, yout2, testout);

    // Вычисление минимальных и максимальных значений для графика
    computeMinMax(m, yout1, yout2, testout, miny, maxy, ystep);

    return EXIT_SUCCESS;
}

void runExplicitEuler(int n, double xbeg, double xend, double xout[], double yout1[], double testout[]) {
    double x = xbeg;
    double y[NZ] = { 1.0, 0.5 };  // Начальные условия: y1(0) = 1, y2(0) = 0.5
    double h = (xend - xbeg) / n;  // Начальный шаг
    double yprev = y[0];  // Для отслеживания изменений y1

    xout[0] = x;
    yout1[0] = y[0];
    NRHS = 0;

    cout << "EULER EXPLICIT SCHEME, with h = " << h << endl;
    cout << "FOR X = " << setw(p) << fixed << setprecision(4) << x
        << ", Y = " << setw(p) << y[0]
        << ", TEST = " << setw(p) << testout[0] << endl;

    for (int i = 0; i < n; ++i) {
        explicitEuler(x, h, y);  // Выполнение явной схемы Эйлера

        // Проверка сходимости: если изменения между yprev и y[0] меньше порога, уменьшаем шаг
        if (checkConvergence(yprev, y[0], EPS)) {
            cout << "Convergence reached at step " << i << ", X = " << x << ", Y = " << y[0] << endl;
            reduceStep(h);  // Уменьшаем шаг в 2 раза
            cout << "Reducing step to: " << h << endl;
        }

        xout[i + 1] = x;
        yout1[i + 1] = y[0];

        cout << "FOR X = " << setw(p) << x
            << ", Y = " << y[0]
            << ", TEST = " << testout[i + 1] << endl;

        yprev = y[0];  // Обновляем предыдущее значение для следующей проверки
    }

    cout << "NRHS = " << NRHS << endl;
}

void explicitEuler(double& x, double h, double y[]) {
    double dydx[NZ];
    deriv(x, y, dydx);  // Вычисление производных

    for (int i = 0; i < NZ; i++) {
        y[i] += h * dydx[i];  // Обновляем значения переменных с помощью явной схемы
    }

    x += h;  // Переходим к следующей точке
}

void deriv(double x, double y[], double dydx[]) {
    double num = y[0] * y[0];  // Числитель для производной y1
    double denom = y[1] - x;  // Знаменатель для производной y1

    if (fabs(denom) < EPS) denom = (denom >= 0 ? EPS : -EPS);  // Защита от деления на ноль

    NRHS++;  // Увеличиваем счётчик вызовов производной

    dydx[0] = num / denom;  // Вычисление производной для y1
    dydx[1] = y[0] + 1.0;  // Вычисление производной для y2
}

void runImplicitEuler(int n, double xbeg, double xend, double xout[], double yout2[], const double testout[]) {
    double x = xbeg;
    double y[NZ] = { 1.0, 0.5 };  // Начальные условия
    double h = (xend - xbeg) / n;  // Начальный шаг

    xout[0] = x;
    yout2[0] = y[0];
    NRHS = 0;

    cout << "\nEULER IMPLICIT SCHEME, with h = " << h << endl;
    cout << "FOR X = " << setw(p) << fixed << setprecision(4) << x
        << ", Y = " << setw(p) << y[0]
        << ", TEST = " << setw(p) << testout[0] << endl;

    for (int i = 0; i < n; ++i) {
        implicitEuler(x, h, y);  // Выполнение неявной схемы Эйлера

        xout[i + 1] = x;
        yout2[i + 1] = y[0];

        cout << "FOR X = " << setw(p) << x
            << ", Y = " << y[0]
            << ", TEST = " << testout[i + 1] << endl;
    }

    cout << "NRHS = " << NRHS << endl;
}

void reduceStep(double& h) {
    h *= 0.5;
}

bool checkConvergence(double yprev, double ycurrent, double eps) {
    return fabs(ycurrent - yprev) < eps;
}

