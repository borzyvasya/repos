#include <iostream>
#include <iomanip>
#include <mkl.h>
#include <omp.h>

using namespace std;

const int n = 10;       // Размер системы
const int nrhs = 1;    // Кол-во правых частей
const int ldb = n;


int main() {
    double dl[n - 1] = { -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

    double d[n] = { 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0 };

    double du[n - 1] = { -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0 };

    double b[n] = { 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0 };

    int info = LAPACKE_dgtsv(LAPACK_ROW_MAJOR, n, nrhs, dl, d, du, b, ldb);

    if (info == 0) {
        cout << fixed << setprecision(8) << "Solution x:\n";

        #pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            #pragma omp critical
            cout << "x[" << i << "] = " << b[i] << endl;
        }

    }
    else 
        cerr << "Error in LAPACKE_dgtsv: info = " << info << endl;

    return EXIT_SUCCESS;
}
