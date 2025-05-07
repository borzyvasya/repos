#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Максимальный размер системы линейных уравнений
constexpr int MAX_SIZE = 10;
// Расширенный размер для матрицы (коэффициенты + свободный член)
constexpr int MAX_SIZE_EXTENDED = MAX_SIZE + 1;

// Количество уравнений в системе
const int Q = 9; // Либо 9

// Прототипы функций
bool readFile(const string&, float[][MAX_SIZE_EXTENDED]);  // Функция для чтения матрицы из файла
void printMatrix(float[][MAX_SIZE_EXTENDED]);              // Функция для вывода матрицы на экран
void forwardSubstitution(float[][MAX_SIZE_EXTENDED]);      // Прямой ход метода Гаусса
void backSubstitution(float[][MAX_SIZE_EXTENDED], float[]); // Обратный ход метода Гаусса
void outputSolutions(float[]);                             // Функция для вывода найденных решений
void checkSolution(float[][MAX_SIZE_EXTENDED], float[]);   // Функция для проверки правильности решения

int main() {
    float matrix[MAX_SIZE][MAX_SIZE_EXTENDED];  // Матрица коэффициентов и свободных членов (size + 1)
    float solution[MAX_SIZE];                   // Массив для хранения решений

    if (!readFile("input.txt", matrix)) {
        cout << "Couldn't open file..." << endl;
        return EXIT_FAILURE;
    }

    cout << "Source matrix is:" << endl;
    printMatrix(matrix);

    cout << endl;

    // Преобразование матрицы в верхнюю треугольную форму
    forwardSubstitution(matrix);

    cout << "Matrix after making upper triangular form:" << endl;
    printMatrix(matrix);

    // Нахождение решений системы
    backSubstitution(matrix, solution);

    // Вывод найденных решений
    outputSolutions(solution);

    // Проверка корректности решений
    checkSolution(matrix, solution);

    return EXIT_SUCCESS;
}

// Функция для чтения матрицы из файла
bool readFile(const string& filename, float matrix[][MAX_SIZE_EXTENDED]) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        return false;
    }

    cout << "Reading matrix from file..." << endl;

    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < MAX_SIZE_EXTENDED; j++) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close();
    return true;
}

// Функция для вывода матрицы на экран
void printMatrix(float matrix[][MAX_SIZE_EXTENDED]) {
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            // Используем fabs для устранения -0.0
            cout << fixed << setw(7) << setprecision(2) << fabs(matrix[i][j]) << " ";
        }
        // Выводим свободный член с использованием fabs
        cout << " | " << fixed << setw(7) << setprecision(2) << fabs(matrix[i][MAX_SIZE]) << endl;
    }
}

// Функция для выполнения прямого хода метода Гаусса
void forwardSubstitution(float matrix[][MAX_SIZE_EXTENDED]) {
    for (int i = 0; i < Q; i++) {
        // Поиск строки с максимальным элементом в столбце для улучшения численной стабильности
        float maxEl = fabs(matrix[i][i]);
        int maxRow = i;

        for (int k = i + 1; k < Q; k++) {
            if (fabs(matrix[k][i]) > maxEl) {
                maxEl = fabs(matrix[k][i]);
                maxRow = k;
            }
        }

        if (maxRow != i) {
            // Поменять местами строки
            for (int j = 0; j < MAX_SIZE_EXTENDED; j++) {
                float temp = matrix[maxRow][j];
                matrix[maxRow][j] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }

        for (int k = i + 1; k < Q; k++) {
            float factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < MAX_SIZE_EXTENDED; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }
}

// Функция для выполнения обратного хода метода Гаусса
void backSubstitution(float matrix[][MAX_SIZE_EXTENDED], float solution[]) {
    for (int i = Q - 1; i >= 0; i--) {
        solution[i] = matrix[i][MAX_SIZE];

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

// Функция для вывода решения на экран
void outputSolutions(float solution[]) {
    cout << "\nSolution is:" << endl;
    for (int i = 0; i < Q; i++) {
        // Выводим с помощью fixed и setprecision для точности
        cout << "x" << i + 1 << " = " << setprecision(2) << solution[i] << endl;
    }
}

// Функция для проверки правильности найденных решений
void checkSolution(float matrix[][MAX_SIZE_EXTENDED], float solution[]) {
    for (int i = 0; i < Q; i++) {
        float sum = 0;

        for (int j = 0; j < MAX_SIZE; j++) {
            sum += matrix[i][j] * solution[j];
        }

        // Выводим с помощью fixed и setprecision для точности
        if (fabs(sum - matrix[i][MAX_SIZE]) > 1e-04) {
            cout << "Equation " << i + 1 << " is not satisfied: " << fixed << setprecision(2) << sum
                << " != " << matrix[i][MAX_SIZE] << endl;
            cout << "Solution is incorrect" << endl;
            return;
        }
    }

    cout << "Solution is correct" << endl;
}
