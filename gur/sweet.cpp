#include <iostream> // Для cout и endl

using namespace std; // Чтобы не прописывать std:: 

// Абстрактный класс WonkaFactory
// Этот класс служит основой для создания фабрик, которые будут производить конфеты.
class WonkaFactory {
public:
    // Чисто виртуальный метод CreateCandy
    // Метод будет переопределен в дочерних классах, и каждый класс должен реализовать свой способ создания конфеты.
    virtual void CreateCandy() const = 0;
};

// Класс для фабрики Красный Октябрь
// Переопределяет метод CreateCandy, чтобы создать конфету "Alenka".
class KrasnyiOktabrFactory : public WonkaFactory {
public:
    // Переопределение метода CreateCandy для фабрики Красный Октябрь
    void CreateCandy() const override {
        cout << "Alenka" << endl;  // Выводим название конфеты, которую производит фабрика
    }
};

// Класс для фабрики Рот Фронт
// Переопределяет метод CreateCandy, чтобы создать конфету "Bars".
class RotFrontFactory : public WonkaFactory {
public:
    // Переопределение метода CreateCandy для фабрики Рот Фронт
    void CreateCandy() const override {
        cout << "Bars" << endl;  // Выводим название конфеты, которую производит фабрика
    }
};

// Класс для фабрики им. Крупской
// Переопределяет метод CreateCandy, чтобы создать конфету "Mishka on North".
class KrupskayaFactory : public WonkaFactory {
public:
    // Переопределение метода CreateCandy для фабрики им. Крупской
    void CreateCandy() const override {
        cout << "Mishka on North" << endl;  // Выводим название конфеты, которую производит фабрика
    }
};

int main() {
    // Создание объектов фабрик
    KrasnyiOktabrFactory redOctober;  // Объект класса фабрики Красный Октябрь
    RotFrontFactory rotFront;         // Объект класса фабрики Рот Фронт
    KrupskayaFactory krupskaya;      // Объект класса фабрики им. Крупской

    // Вызов метода CreateCandy для каждой фабрики
    redOctober.CreateCandy();  // Выводит название конфеты, которую производит Красный Октябрь
    rotFront.CreateCandy();    // Выводит название конфеты, которую производит Рот Фронт
    krupskaya.CreateCandy();   // Выводит название конфеты, которую производит фабрика им. Крупской

    return EXIT_SUCCESS;  // Завершаем программу с кодом успешного завершения
}
