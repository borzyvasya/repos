#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int N = 6; // Количество точек

// Структура для представления точки на плоскости с координатами x и y
struct Point {
    float x, y;
};

// Функция для заполнения массива точек
void fillingArray(Point[]);
// Функция для нахождения минимального расстояния между точками
void findMinDistance(Point[], float&, int&, int&);
// Функция для вывода результатов на экран
void outputResults(Point[], float, int, int);

int main() {
    Point points[N]; // Массив точек

    // Заполнение массива точек
    fillingArray(points);

    float minDistance; // Переменная для хранения минимального расстояния
    int minIndex1, minIndex2; // Индексы точек, между которыми минимальное расстояние

    // Нахождение минимального расстояния и индексов точек
    findMinDistance(points, minDistance, minIndex1, minIndex2);

    // Вывод результатов
    cout << "Min distance: ";
    outputResults(points, minDistance, minIndex1, minIndex2);

    return EXIT_SUCCESS; // Завершение программы
}

// Функция для заполнения массива точек с заранее заданными координатами
void fillingArray(Point points[]) {
    points[0] = { 2., 3. }; // Точка 1
    points[1] = { 7., 7. }; // Точка 2
    points[2] = { 8., 2. }; // Точка 3
    points[3] = { 6., 4. }; // Точка 4
    points[4] = { 3.5, 2. }; // Точка 5
    points[5] = { 5., 2. }; // Точка 6
}

// Функция для нахождения минимального расстояния между точками
void findMinDistance(Point points[], float& distance, int& index1, int& index2) {
    // Инициализация минимального расстояния первым возможным расстоянием (между первой и второй точкой)
    distance = sqrt(pow(points[1].x - points[0].x, 2) + pow(points[1].y - points[0].y, 2));

    // Инициализация индексов для первых двух точек
    index1 = 0;
    index2 = 1;

    // Перебор всех возможных пар точек для нахождения минимального расстояния
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Вычисление расстояния между текущими точками
            float dist = sqrt(pow(points[j].x - points[i].x, 2) + pow(points[j].y - points[i].y, 2));

            // Если найдено меньшее расстояние, обновляем минимальное
            if (dist < distance) {
                distance = dist;
                index1 = i;
                index2 = j;
            }
        }
    }
}

// Функция для вывода результатов на экран: координаты точек и их минимальное расстояние
void outputResults(Point points[], float distance, int idx1, int idx2) {
    cout << "Points (" << points[idx1].x << ", " << points[idx1].y << ") and "
        << "(" << points[idx2].x << ", " << points[idx2].y << ") are "
        << "separated by a distance of: " << fixed << setprecision(2) << distance << endl;
}
