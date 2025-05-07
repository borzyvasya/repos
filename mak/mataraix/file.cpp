#include <iostream>
#include <iomanip>

using namespace std;

const int N = 10;
const double EPS = 0.00001;  
const double EPS1 = 0.0001; 
const double OMEGA = 1.056;

void generate_matrix(double A[][N], double b[]);
void print_matrix(double A[][N], double b[]);
void simple_iteration(double A[][N], double b[], double x[], double, double);
void gauss_seidel(double A[][N], double b[], double x[], double, double);
void sor(double A[][N], double b[], double x[], double, double, double);
void output_solutions(double A[][N], double b[], double x[], const string&);

/*
|| x^(k + 1) − x ^ (k) || < eps
|| Ax^k - b || < eps1
*/


int main() {
    double A[N][N], b[N], x[N];

    generate_matrix(A, b);
    cout << "Matrix A and b:" << endl;
    print_matrix(A, b);

    cout << "--------------------------------------------------" << endl;
    cout << "Simple Iterations (Jacobi Method):" << endl;
    simple_iteration(A, b, x, EPS, EPS1);
    output_solutions(A, b, x, "Simple Iterations");

    cout << "--------------------------------------------------" << endl;
    cout << "Gauss-Seidel Method:" << endl;
    gauss_seidel(A, b, x, EPS, EPS1);
    output_solutions(A, b, x, "Gauss-Seidel");

    cout << "--------------------------------------------------" << endl;
    cout << "Successive Over-Relaxation (SOR) Method:" << endl;
    sor(A, b, x, EPS, EPS1, OMEGA);
    output_solutions(A, b, x, "SOR");

    cout << "--------------------------------------------------" << endl;

    return EXIT_SUCCESS;
}

void generate_matrix(double A[][N], double b[]) {
    double tempA[][N] = {
        {10, -1, 2, 0, 0, 0, 0, 0, 0, 0},
        {-1, 11, -1, 3, 0, 0, 0, 0, 0, 0},
        {2, -1, 10, -1, 0, 0, 0, 0, 0, 0},
        {0, 3, -1, 8, -2, 0, 0, 0, 0, 0},
        {0, 0, 0, -2, 7, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 12, -1, 0, 0, 0},
        {0, 0, 0, 0, 0, -1, 9, -1, 0, 0},
        {0, 0, 0, 0, 0, 0, -1, 7, -2, 0},
        {0, 0, 0, 0, 0, 0, 0, -2, 8, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 3, 10}
    };

    double tempB[] = { 6, 25, -11, 15, 9, 10, -6, 5, 2, 3 };

    for (int i = 0; i < N; ++i) {
        b[i] = tempB[i];
        for (int j = 0; j < N; ++j) {
            A[i][j] = tempA[i][j];
        }
    }
}

void print_matrix(double A[][N], double b[]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(8) << fixed << setprecision(3) << A[i][j] << " ";
        }
        cout << "| " << setw(8) << b[i] << endl;
    }
}

void simple_iteration(double A[][N], double b[], double x[], double epsilon, double epsilon1) {
    double x_new[N];
    double error = epsilon + 1.0;
    int iter = 0;

    for (int i = 0; i < N; ++i) x[i] = 0.0;

    while (error > epsilon && iter < 1000) {
        ++iter;
        error = 0.0;

        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = 0; j < N; ++j) {
                if (j != i) sum += A[i][j] * x[j];
            }

            if (fabs(A[i][i]) < 1e-10) {
                cout << "Error: Near-zero diagonal element at row " << i << endl;
                return;
            }

            x_new[i] = (b[i] - sum) / A[i][i];
            error = max(error, fabs(x_new[i] - x[i]));
        }

        for (int i = 0; i < N; ++i) x[i] = x_new[i];

        double residual = 0.0;
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = 0; j < N; ++j)
                sum += A[i][j] * x[j];
            
            residual = max(residual, fabs(sum - b[i]));
        }

        if (residual < epsilon1) break;

        cout << "Iteration " << setw(5) << iter << ", error: " << error << ", residual: " << residual << endl;
    }
}

void gauss_seidel(double A[][N], double b[], double x[], double epsilon, double epsilon1) {
    double error = epsilon + 1.0;
    int iter = 0;

    for (int i = 0; i < N; ++i) x[i] = 0.0;

    while (error > epsilon && iter < 1000) {
        ++iter;
        error = 0.0;

        for (int i = 0; i < N; ++i) {
            double sum = b[i];
            for (int j = 0; j < N; ++j) {
                if (j != i)
                    sum -= A[i][j] * x[j];
            }
            if (fabs(A[i][i]) < 1.0e-10) {
                cout << "Error: Zero or near-zero diagonal element at " << i << endl;
                return;
            }

            double new_xi = sum / A[i][i];
            error = max(error, fabs(new_xi - x[i]));
            x[i] = new_xi;
        }

        double residual = 0.0;
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = 0; j < N; ++j)
                sum += A[i][j] * x[j];
      
            residual = max(residual, fabs(sum - b[i])); //подсчет A*x
        }
        if (residual < epsilon1) break; //Ax - b 

        cout << "Iteration " << setw(3) << iter << ", error: " << error << setprecision(10) << 
            ", residual: " << residual << endl;
    }
}

void sor(double A[][N], double b[], double x[], double epsilon, double epsilon1, double omega) {
    double error = epsilon + 1.0;
    int iter = 0;

    for (int i = 0; i < N; ++i) x[i] = 0.0;

    while (error > epsilon && iter < 1000) {
        ++iter;
        error = 0.0;

        for (int i = 0; i < N; ++i) {
            double x_old = x[i];
            double sum = b[i];
            for (int j = 0; j < N; ++j) {
                if (j != i)
                    sum -= A[i][j] * x[j];
            }

            if (fabs(A[i][i]) < 1.0e-10) {
                cout << "Error: Zero or near-zero diagonal element at " << i << endl;
                return;
            }

            double gs_update = sum / A[i][i];
            x[i] = (1 - omega) * x_old + omega * gs_update;

            error = max(error, fabs(x[i] - x_old));
        }

        double residual = 0.0;
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = 0; j < N; ++j) {
                sum += A[i][j] * x[j];
            }
            residual = max(residual, fabs(sum - b[i]));
        }

        if (residual < epsilon1) break;

        cout << "Iteration " << setw(3) << iter << ", error: " << error << setprecision(10) << 
            ", residual: " << residual << endl;
    }
}

void output_solutions(double A[][N], double b[], double x[], const string& method_name) {
    double Ax[N];
    double residual = 0.0;

    for (int i = 0; i < N; ++i) {
        Ax[i] = 0.0;
        for (int j = 0; j < N; ++j)
            Ax[i] += A[i][j] * x[j];
        residual = max(residual, fabs(Ax[i] - b[i]));
    }

    cout << "Solution (" << method_name << "):" << endl;
    for (int i = 0; i < N; ++i)
        cout << "x[" << i + 1 << "] = " << fixed << setprecision(6) << x[i] << endl;

    cout << "Residual: " << residual << endl;
}
