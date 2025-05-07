#include <fstream> 
#include <iostream>

using namespace std; 

const int MAX_SIZE = 12;

void forArrayC(int[], int[], int[]);
void outputArray(int[]);
bool loadArraysFromf(const string&, int[], int[]);
void bubSort(int[]);

int main() {
    int A[MAX_SIZE];
    int B[MAX_SIZE];


    if (!loadArraysFromf("input.txt", A, B)) {
        cerr << "Ошибка загрузки данных из файла." << endl;
        return EXIT_FAILURE;
    }

    int C[MAX_SIZE]; 

    forArrayC(A, B, C);

    bubSort(A);
    bubSort(B);
    bubSort(C); 

    cout << "Array A: " << endl;
    outputArray(A);

    cout << "Array B: " << endl;
    outputArray(B); 

    cout << "Array C: " << endl;
    outputArray(C); 

    return EXIT_SUCCESS;
}

void forArrayC(int A[], int B[], int C[]) {
    int S = 0; 
    for (int i = 0; i < MAX_SIZE; ++i) { 
        C[i] = B[MAX_SIZE - i - 1] + A[i]; 
        S += C[i];                  
    }
    cout << "Sum is " << S << endl << endl;
}

void outputArray(int Array[]) {
    for (int i = 0; i < MAX_SIZE; i++) { 
        cout << Array[i] << endl;      
    }
    cout << endl;
}


bool loadArraysFromf(const string &filename, int A[], int B[]) {
    ifstream f(filename); 
    if (!f.is_open()) {
        return false; 
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        if (!(f >> A[i])) A[i] = 0;  
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        if (!(f >> B[i])) B[i] = 0;  
    }

  f.close();   
  return true; 
}

void bubSort(int Array[]) {
    for (int i = 0; i < MAX_SIZE - 1; ++i) {
        for (int j = 0; j < MAX_SIZE - i - 1; ++j) {
            if (Array[j] > Array[j + 1]) {
                int temp = Array[j];
                Array[j] = Array[j + 1];
                Array[j + 1] = temp;
            }
        }
    }
}
