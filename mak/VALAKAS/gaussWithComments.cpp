#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Максимальный размер системы линейных уравнений
constexpr int MAX_SIZE = 10, FSZ = MAX_SIZE + 1;
// Количество уравнений в системе (сейчас оно равно 10)
const int Q = 10;

// Прототипы функций
bool readFile(const string&, float[][FSZ]);  // Функция для чтения матрицы из файла
void printMatrix(float[][FSZ]);              // Функция для вывода матрицы на экран
void forwardSubstitution(float[][FSZ]);      // Прямой ход метода Гаусса
void backSubstitution(float[][FSZ], float[]); // Обратный ход метода Гаусса
void outputSolutions(float[]);                         // Функция для вывода найденных решений
void checkSolution(float[][FSZ], float[]);    // Функция для проверки правильности решения

int main() {
    // Объявление матрицы для коэффициентов и свободных членов
    float matrix[MAX_SIZE][FSZ];  // Матрица размером Qx(Q+1), так как у нас есть столбцы для коэффициентов и столбец для свободных членов
    // Массив для хранения найденных решений
    float solution[MAX_SIZE];

    if (!readFile("input", matrix)) {
        return EXIT_FAILURE;
    };

    // Печать исходной матрицы, считанной из файла
    cout << "Source matrix is:" << endl;
    printMatrix(matrix);

    // Преобразование матрицы в верхнюю треугольную форму с использованием прямого хода
    forwardSubstitution(matrix);

    // Вывод матрицы после выполнения прямого хода
    cout << "Matrix after making upper triangular form:" << endl;
    printMatrix(matrix);

    // Нахождение решений системы с использованием обратного хода
    backSubstitution(matrix, solution);

    // Вывод найденных решений
    outputSolutions(solution);

    // Проверка корректности найденных решений
    checkSolution(matrix, solution);

    return EXIT_SUCCESS; // Успешное завершение программы
}

// Функция для чтения матрицы из файла
bool readFile(string& filename, float matrix[][FSZ]) {
    //int i, j;
    //float CF = 1.0e+04;
    //srand(time(NULL));

    //for (i = 0; i < Q; i++) {
    //    for (j = 0; j < Q + 1; j++) {
    //        matrix[i][j] = rand() / CF;
    //    }
    //}

    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        return false;
    }
    cout << "Reading matrix from file..." << endl;

    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < FSZ; j++) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close();

    return true;  // Успешно прочитали файл
}

// Функция для вывода матрицы на экран
void printMatrix(float matrix[][FSZ]) {
    // Проходим по всем строкам и столбцам матрицы
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < Q; j++) {
            // Выводим элементы матрицы с точностью до 4 знаков после запятой
            cout << setw(8) << setprecision(2) << matrix[i][j] << " ";
        }
        // После вывода коэффициентов столбца выводим свободный член (последний столбец)
        cout << " | " << setw(8) << setprecision(2) << matrix[i][Q] << endl;
    }
}

// Функция для выполнения прямого хода метода Гаусса
void forwardSubstitution(float matrix[][FSZ]) {
    // Проходим по всем строкам матрицы (строки системы уравнений)
    for (int i = 0; i < Q; i++) {
        // Ищем максимальный элемент в столбце i
        float maxEl = abs(matrix[i][i]);
        int maxRow = i;

        // Ищем строку с максимальным элементом в текущем столбце
        for (int k = i + 1; k < Q; k++) {
            if (abs(matrix[k][i]) > maxEl) {
                maxEl = abs(matrix[k][i]);
                maxRow = k;
            }
        }

        // Если максимальный элемент не в текущей строке, меняем строки местами
        if (maxRow != i) {
            for (int j = 0; j < FSZ; j++) {
                // Меняем местами элементы в строках
                float temp = matrix[maxRow][j];
                matrix[maxRow][j] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }

        // Приводим элементы ниже главной диагонали к нулю
        for (int k = i + 1; k < Q; k++) {
            // Вычисляем коэффициент для обнуления элемента в текущем столбце
            float factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < Q + 1; j++) {
                // Вычитаем пропорциональную строку, чтобы обнулить текущий элемент
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }
}

// Функция для выполнения обратного хода метода Гаусса
void backSubstitution(float matrix[][FSZ], float solution[]) {
    // Начинаем с последней строки и двигаемся вверх
    for (int i = Q - 1; i >= 0; i--) {
        solution[i] = matrix[i][Q];  // Начинаем с правой части уравнения

        // Для каждого уравнения вычитаем известные решения
        for (int j = i + 1; j < Q; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }

        // Проверяем, что ведущий элемент (диагональный) ненулевой
        if (fabs(matrix[i][i]) < 1e-9) {
            cout << "The matrix does not have a non-zero pivot!" << endl;
            return;  // Если ведущий элемент равен нулю, выводим ошибку и завершаем решение
        }

        // Решаем для текущей переменной, деля на ведущий элемент
        solution[i] /= matrix[i][i];
    }
}

// Функция для вывода решения на экран
void outputSolutions(float solution[]) {
    cout << "Solution is:" << endl;
    // Выводим найденное решение для каждой переменной
    for (int i = 0; i < Q; i++) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }
}

// Функция для проверки правильности найденных решений
void checkSolution(float matrix[][FSZ], float solution[]) {
    // Проходим по каждому уравнению
    for (int i = 0; i < Q; i++) {
        float sum = 0;

        // Для текущего уравнения вычисляем левую часть, подставляя найденные решения
        for (int j = 0; j < Q; j++) {
            sum += matrix[i][j] * solution[j];
        }

        // Проверяем, что левая часть уравнения равна правой (с учетом погрешности)
        if (fabs(sum - matrix[i][Q]) > 1e+02) {
            cout << "Equation " << i + 1 << " is not satisfied: " << sum
                << " != " << matrix[i][Q] << endl;

            cout << "solution is incorrect" << endl;  // Если уравнение не выполняется, решение неверно
            return;  // Завершаем проверку
        }
    }

    // Если все уравнения выполнены, выводим сообщение о корректности решения
    cout << "solution is correct" << endl;
}


