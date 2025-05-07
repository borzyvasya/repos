
#include <iostream> // Подключаем библиотеку для ввода-вывода
#include <fstream> // Подключаем библиотеку для работы с файлами
#include <memory>

using namespace std; // Используем пространство имен std для упрощения синтаксиса

const int MAX_SIZE = 12; // Определяем константу MAX_SIZE, которая задает максимальный размер массивов

// Объявляем функции для формирования массива C и для вывода массивов
void forArrayC(int*, int*, int*, int); 
void outputArray(int*, int);
void delArrays(int[], int[], int[]);
bool loadArraysFromf(const string&, int*, int*);

int main() {
    // Инициализируем динамические массивы A и B с 12 элементами
    int* A = new int[MAX_SIZE];
    int* B = new int[MAX_SIZE];


    // В случае с такой инициализацией не нужно писать delete в конце
    //auto A = make_unique<int>(MAX_SIZE);
    //auto B = make_unique<int>(MAX_SIZE);
    //auto C = make_unique<int>(MAX_SIZE);

    // Загружаем данные из файла
    if (!loadArraysFromf("input.txt", A, B)) {
        cerr << "Ошибка загрузки данных из файла." << endl;
        return EXIT_FAILURE; // Завершаем программу с ошибкой, если загрузка не удалась
    }

    // Инициализируем динамический массив C
    int* C = new int[MAX_SIZE]; // Массив C изначально не инициализирован, но будет заполнен в функции

    // Вызываем функцию для формирования массива C на основе массивов A и B
    forArrayC(A, B, C, MAX_SIZE);

    // Выводим массив A
    cout << "Array A: " << endl;
    outputArray(A, MAX_SIZE); // Вызываем функцию для вывода массива A

    // Выводим массив B
    cout << "Array B: " << endl;
    outputArray(B, MAX_SIZE); // Вызываем функцию для вывода массива B

    // Выводим массив C
    cout << "Array C: " << endl;
    outputArray(C, MAX_SIZE); // Вызываем функцию для вывода массива C

    // Освобождаем память
    delArrays(A, B, C);
    return EXIT_SUCCESS; // Завершаем программу с успешным статусом
}

// Функция для формирования массива C на основе массивов A и B
void forArrayC(int* A, int* B, int* C, int m) {
    int S = 0; // Инициализируем переменную для хранения суммы элементов массива C

    // Цикл для вычисления каждого элемента массива C
    for (int i = 0; i < m; ++i) { // Проходим по всем элементам от 0 до m-1
        C[i] = B[m - i - 1] + A[i]; // Формируем элемент C[i] как сумму соответствующих элементов массива B и A
        S += C[i]; // Добавляем значение C[i] к сумме S
    }

    // Выводим сумму элементов массива C
    cout << "Sum is " << S << endl << endl; 
}

// Функция для вывода массива на экран
void outputArray(int* Array, int size) {
    for (int i = 0; i < size; i++) { // Проходим по всем элементам массива
        cout << Array[i] << endl; // Выводим текущий элемент массива
    }
    cout << endl; // Печатаем пустую строку для разделения выводов
}

void delArrays(int A[], int B[], int C[]) {
    delete[] A;
    delete[] B;
    delete[] C;
}

// Функция для загрузки массивов A и B из файла
bool loadArraysFromf(const string& filename, int* A, int* B) {
    ifstream f(filename); // Открываем файл для чтения
    if (!f.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return false; // Возвращаем false, если файл не удалось открыть
    }

    // Читаем элементы в массив A
    for (int i = 0; i < MAX_SIZE; i++) {
        if (!(f >> A[i])) { // Читаем элемент и проверяем на ошибку
            A[i] = 0; // Если не удалось прочитать, устанавливаем значение в 0
        }
    }

    // Читаем элементы в массив B
    for (int i = 0; i < MAX_SIZE; i++) {
        if (!(f >> B[i])) { // Читаем элемент и проверяем на ошибку
            B[i] = 0; // Если не удалось прочитать, устанавливаем значение в 0
        }
    }

    f.close(); // Закрываем файл
    return true; // Возвращаем true, если загрузка прошла успешно
}

