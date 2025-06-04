#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

const int Q = 10;
const float EPS = 1e-3;

void randMatrix(float[][Q], float[]);
void printSystem(float[][Q], float[]);
bool forwardSubstitution(float[][Q], float[], float[]);
float calculateMatrixNorm(float[][Q]);
bool invertMatrix(float[][Q], float[][Q]);
void checkSolution(float[][Q], float[], float[]);

int main() {
    float matrix[Q][Q];
    float b[Q];
    float solution[Q];
    float invMatrix[Q][Q];

    randMatrix(matrix, b);

    cout << "Original system (A | b):" << endl;
    printSystem(matrix, b);

    if (!forwardSubstitution(matrix, b, solution)) {
        cout << "Matrix is singular or nearly singular. Cannot solve." << endl;
        return EXIT_FAILURE;
    }

    checkSolution(matrix, b, solution);

    if (!invertMatrix(matrix, invMatrix)) {
        cout << "Matrix is singular or nearly singular. Cannot invert." << endl;
        return EXIT_FAILURE;
    }

    float normA = calculateMatrixNorm(matrix);
    float normAinv = calculateMatrixNorm(invMatrix);

    cout << "Matrix norm ||A|| = " << normA << endl;
    cout << "Inverse matrix norm ||A^-1|| = " << normAinv << endl;
    cout << "Condition number = ||A|| * ||A^-1|| = " << normA * normAinv << endl;

    return EXIT_SUCCESS;
}

void randMatrix(float matrix[][Q], float b[]) {
    float CF = 750.0f;
    srand(time(NULL));
    for (int i = 0; i < Q; ++i) {
        for (int j = 0; j < Q; ++j) {
            matrix[i][j] = rand() / CF;
        }
        b[i] = rand() / CF;
    }
}

void printSystem(float matrix[][Q], float b[]) {
    for (int i = 0; i < Q; ++i) {
        for (int j = 0; j < Q; ++j) {
            cout << setw(8) << fixed << setprecision(2) << matrix[i][j] << " ";
        }
        cout << " | " << setw(8) << fixed << setprecision(2) << b[i];
        cout << endl;
    }
    cout << endl;
}

bool forwardSubstitution(float matrix[][Q], float b[], float solution[]) {
    float mat[Q][Q];
    float vec[Q];

    for (int i = 0; i < Q; ++i) {
        vec[i] = b[i];
        for (int j = 0; j < Q; ++j) {
            mat[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < Q; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < Q; ++k) {
            if (fabs(mat[k][i]) > fabs(mat[maxRow][i]))
                maxRow = k;
        }
        if (fabs(mat[maxRow][i]) < EPS) return false; // сингулярность

        if (maxRow != i) {
            for (int j = 0; j < Q; ++j) swap(mat[maxRow][j], mat[i][j]);
            swap(vec[maxRow], vec[i]);
        }

        for (int k = i + 1; k < Q; ++k) {
            float factor = mat[k][i] / mat[i][i];
            for (int j = i; j < Q; ++j) {
                mat[k][j] -= factor * mat[i][j];
                if (fabs(mat[k][j]) < EPS) mat[k][j] = 0.0f;
            }
            vec[k] -= factor * vec[i];
            if (fabs(vec[k]) < EPS) vec[k] = 0.0f;
        }
    }

    // Обратный ход
    for (int i = Q - 1; i >= 0; --i) {
        if (fabs(mat[i][i]) < EPS) return false; // сингулярность
        solution[i] = vec[i];
        for (int j = i + 1; j < Q; ++j) {
            solution[i] -= mat[i][j] * solution[j];
        }
        solution[i] /= mat[i][i];
    }

    return true;
}

float calculateMatrixNorm(float matrix[][Q]) {
    float norm = 0.0f;
    for (int j = 0; j < Q; ++j) {
        float colSum = 0.0f;
        for (int i = 0; i < Q; ++i) {
            colSum += fabs(matrix[i][j]);
        }
        norm = max(norm, colSum);
    }
    return norm;
}

bool invertMatrix(float matrix[][Q], float inv[][Q]) {
    float e[Q];
    float x[Q];

    for (int j = 0; j < Q; ++j) {
        for (int i = 0; i < Q; ++i) e[i] = 0.0f;
        e[j] = 1.0f;

        if (!forwardSubstitution(matrix, e, x))
            return false; // сингулярна

        for (int i = 0; i < Q; ++i)
            inv[i][j] = x[i];
    }
    return true;
}

void checkSolution(float matrix[][Q], float b[], float solution[]) {
    for (int i = 0; i < Q; ++i) {
        float sum = 0.0f;
        for (int j = 0; j < Q; ++j) sum += matrix[i][j] * solution[j];

        if (fabs(sum - b[i]) > EPS) {
            cout << "Solution is incorrect" << endl;
            return;
        }
    }
    cout << "Solution is correct" << endl;
}
