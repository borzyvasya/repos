#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const int MAX_SIZE = 10;  
const int Q = 10;         

bool readFile(const string&, float[][MAX_SIZE + 1]);
void printMatrix(float[][MAX_SIZE + 1]);
void forwardSubstitution(float[][MAX_SIZE + 1]);
void backSubstitution(float[][MAX_SIZE + 1], float[]);
void outputSolutions(float[]);
void checkSolution(float[][MAX_SIZE + 1], float[]);

int main() {
    float matrix[MAX_SIZE][MAX_SIZE + 1];  
    float solution[MAX_SIZE];  


    if (!readFile("input.txt", matrix)) {
        cout << "COULD NOT OPEN FILE" << endl;
        return EXIT_FAILURE;
    }

    cout << "Source matrix is:" << endl;
    printMatrix(matrix);

    forwardSubstitution(matrix); 

    cout << "Matrix after making upper triangular form:" << endl;

    printMatrix(matrix);

    backSubstitution(matrix, solution); 

    outputSolutions(solution);

    checkSolution(matrix, solution);

    return EXIT_SUCCESS;
}

bool readFile(const string& filename, float matrix[MAX_SIZE][MAX_SIZE + 1]) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return false;
    }
    cout << "Reading matrix from file..." << endl;

    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < Q + 1; j++) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close();
    return true;
}

void printMatrix(float matrix[MAX_SIZE][MAX_SIZE + 1]) {
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < Q; j++) {
            cout << setw(10) << setprecision(4) << matrix[i][j] << " ";
        }
        cout << " | " << setw(10) << setprecision(4) << matrix[i][Q] << endl;
    }
}

void forwardSubstitution(float matrix[MAX_SIZE][MAX_SIZE + 1]) {
    for (int i = 0; i < Q; i++) {
        float maxEl = abs(matrix[i][i]);
        int maxRow = i;

        for (int k = i + 1; k < Q; k++) {
            if (abs(matrix[k][i]) > maxEl) {
                maxEl = abs(matrix[k][i]);
                maxRow = k;
            }
        }

        if (maxRow != i) {
            for (int j = 0; j < Q + 1; j++) {
                float temp = matrix[maxRow][j];
                matrix[maxRow][j] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }

        for (int k = i + 1; k < Q; k++) {
            float factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < Q + 1; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }
}


void backSubstitution(float matrix[MAX_SIZE][MAX_SIZE + 1], float solution[MAX_SIZE]) {
    for (int i = Q - 1; i >= 0; i--) {
        solution[i] = matrix[i][Q]; 

        for (int j = i + 1; j < Q; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }

        if (fabs(matrix[i][i]) < 1e-9) {
            cout << "The matrix does not have a non-zero pivot!" << endl;
            return;
        }

        solution[i] /= matrix[i][i];  
    }
}


void outputSolutions(float solution[MAX_SIZE]) {
    cout << "Solution is:" << endl;
    for (int i = 0; i < Q; i++) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }
}


void checkSolution(float matrix[MAX_SIZE][MAX_SIZE + 1], float solution[MAX_SIZE]) {
    for (int i = 0; i < Q; i++) {
        float sum = 0;
        
        for (int j = 0; j < Q; j++) {
            sum += matrix[i][j] * solution[j];
        }

        if (fabs(sum - matrix[i][Q]) > 1e-6) {
            cout << "Equation " << i + 1 << " is not satisfied: " << sum
                << " != " << matrix[i][Q] << endl;

            cout << "solution is incorrect" << endl;
        }
    }

    cout << "solution is correct" << endl;
}


