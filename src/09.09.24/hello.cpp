#include <iostream>
#include <string>
#include <cmath>
#include <exception>
#include <vector>
#include <set>

using namespace std;
bool isNumber(const string& str) {
    try {
        size_t pos;
        stod(str, &pos);
        return pos == str.length();
    } catch (const exception) {
        return false;
    }
}

// Само решение
void equationSolve(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        cout << "Нет действительных решений для t." << endl;
        return;
    }

    set<double> x_roots;
    if (discriminant >= 0) {
        double sqrt_disc = sqrt(discriminant);
        double t1 = (-b + sqrt_disc) / (2 * a);
        double t2 = (-b - sqrt_disc) / (2 * a);

        for (double t : {t1, t2}) {
            if (t >= 0) {
                x_roots.insert(sqrt(t));
                x_roots.insert(-sqrt(t));
            }
        }
    }

    if (x_roots.empty()) {
        cout<<"Нет действительных решений для x."<<endl;
    } else {
        int n = 1;
        cout<<"Решения биквадратного уравнения:"<<endl;
        for (double x : x_roots) {
            cout<<"x"<<n++<<" = "<<x<< endl;
        }
    }
}

void processingNumber(string str) {
    if (!isNumber(str)) {
        cout << "Ошибка: введенный коэффициент должен быть числом"<<endl;
        exit(0);
    }
}

int main() {
    string a_str, b_str, c_str;
    cout << "Введите коэффициент a: ";
    cin >> a_str;

    processingNumber(a_str);

    cout << "Введите коэффициент b: ";
    cin >> b_str;

    processingNumber(b_str);

    cout << "Введите коэффициент c: ";
    cin >> c_str;

    processingNumber(c_str);

    double a = stod(a_str);
    double b = stod(b_str);
    double c = stod(c_str);

    equationSolve(a, b, c);

    return 0;
}
