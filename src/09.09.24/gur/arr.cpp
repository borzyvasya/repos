#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;
int main() {
    int size;
    cin >> size;
    
   // auto arr = new int[size];

    unique_ptr<int[]> arr(new int[size]);
    
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % size; 
    }
    
    cout<<"Вывод массива: "<<endl;
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    
    cout<<""<<endl;
    
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    cout<<"Отсортированный массив: "<<endl;
    
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout<<""<<endl;  
}
