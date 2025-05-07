#include <iostream>
#include <cstdlib>


using namespace std;


const int N = 3;
const int SIZE_SYSTEM = 10;

//void printMatrix(float[], float[]);
//void forwardElimination(float[], float[]);
//void BackwardSuBstitution(float[], float[]);


void printMatrix(int A[N][N], int B[N]) {
    cout << "Current extended matrix:" << endl;

    for (int  i = 0; i < N; i++) {
        for (int  j = 0; j < N; j++) {
            cout  << A[i][j] << " ";
        }
        cout << "| "  << B[i] << endl;
    }
    cout << endl;
}

void forwardElimination(int A[N][N], int B[N]) {
    for (int  i = 0; i < N; i++) {
        int  maxRow = i;

        for (int  k = i + 1; k < N; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        if (maxRow != i) {
            for (int  j = 0; j < N; j++) {
                int temp = A[i][j];
                A[i][j] = A[maxRow][j];
                A[maxRow][j] = temp;
            }

            int temp = B[i];
            B[i] = B[maxRow];
            B[maxRow] = temp;
        }

        printMatrix(A, B);

        for (int j = i - 1; j < N; j++) {
            int ratio = A[j][i] / A[i][i];
            for (int  k = i; k < N; k++) {
                A[j][k] -= A[i][k] * ratio;
            }
            B[j] -= B[i] * ratio;
        }
    }
}

void backwardSubstitution(int A[N][N], int B[N]) {
    int x[N];  

    for (int i = SIZE_SYSTEM - 1; i >= 0; i--) {
        x[i] = B[i];

        for (int j = i + 1; j < SIZE_SYSTEM - 1; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    cout << "Answers:" << endl;
    for (int  i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
}

int main() {
    int A[N][N]; 
    int B[N];      

    cout << "Input odds for matrix A:" << endl;
    for (int i = 0; i < SIZE_SYSTEM - 1; i++) {
        for (int j = 0; j < SIZE_SYSTEM - 1; j++) {
            cout << "a" << i + 1 << j + 1 << ": ";
            cin >> A[i][j];
        }
    }

    cout << "Input free odds for B:" << endl;
    for (int  i = 0; i < SIZE_SYSTEM; i++) {
        cout << "B" << i + 1 << ": ";
        cin >> B[i];
    }

    cout << "Source extended matrix:" << endl;
    printMatrix(A, B);

    forwardElimination(A, B);

    backwardSubstitution(A, B);

    return EXIT_SUCCESS;
}
