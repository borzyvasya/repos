#include <iostream>


using namespace std;

const int MAX_SIZE = 12;

void formArrayC(int[], int[], int[], int);


int main() {
    int A[MAX_SIZE] {1, 2, 3, 4, 1, 4, 6, 4};
    int B[MAX_SIZE] {4, 6, 7, 8, 6, 1, 8, 4};
    int C[MAX_SIZE];

    int m = 8;

    formArrayC(A, B, C, m);

    for (int i = 0; i < m; i++) {
        cout<<C[i]<<endl;
    }


}

void formArrayC(int A[], int B[], int C[], int m) {
    for (int i = 0; i < m; i++) {
        C[i] = B[m - 1 - i] + A[i];
    }

}
