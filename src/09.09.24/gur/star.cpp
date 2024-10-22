#include <cmath>
#include <iostream>


using namespace std;

int main() {

    // Первая программа с полупирамидой.

    int n;
    cin>>n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cout<<"*";
        }

        cout<<""<<endl;
    }

    
    
    // Вторая программа с таблицей плотности.

    const double p0 = 1.25; 
    const double z = 1.21*pow(10, -4);  
    double h, p; 

    cout << "Высота (м)\tПлотность (кг/м^3)" << endl; 
    for (h = 0; h <= 1000; h += 100) { 
        p = p0 * exp(-h * z); 
        cout << h << "\t\t" << p << endl; 
    } 

    return 0;
}