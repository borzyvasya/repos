#include <cstdlib>
#include <iostream>

using namespace std;


const int MAX_SIZE = 12;

void forArrayC(int[], int[], int[], int); 
void inputArray(int[], int);


int main() {
    int A[MAX_SIZE] {6, 2, 3, 4, 1, 4, 6, 9, 3, 6, 1, 7};
    int B[MAX_SIZE] {4, 6, 7, 8, 6, 1, 8, 4};
    int C[MAX_SIZE];
    
    forArrayC(A, B, C, MAX_SIZE);

    cout << "Array A: " << endl;
    inputArray(A, MAX_SIZE);

    cout << "Array B: " << endl;
    inputArray(B, MAX_SIZE);

    cout << "Array C: " << endl;
    inputArray(C, MAX_SIZE);


    return EXIT_SUCCESS;
}

void forArrayC(int A[], int B[], int C[], int m) {
    int S = 0;
    for (int i = 0; i < MAX_SIZE; ++i) {
        C[i] = B[MAX_SIZE - 1 - i] + A[i];
        S += C[i];
    }

    cout << "Sum is " << S << endl << endl;
}

void inputArray(int Array[], int MAX_SIZE) {
    for (int i = 0; i < MAX_SIZE; i++) {
        cout << Array[i] << endl;
    }
    cout << endl;
}
