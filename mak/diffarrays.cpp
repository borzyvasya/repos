#include <iostream>


using namespace std;

const int sizetwelve = 12;

void formArrayC(int[], int[], int[], int);


int main() {
    int A[sizetwelve] {1, 2, 3, 4};
    int B[sizetwelve] {5, 6, 7, 8};
    int C[sizetwelve];

    int m = 4;

    formArrayC(A, B, C, m);

    for (int i = 0; i < m; i++) {
        cout<<C[i]<<"";
    }

    cout<<endl;

}

void formArrayC(int A[], int B[], int C[], int m) {
    for (int i = 0; i < m; i++) {
        C[i] = B[m - 1 - i] + A[i];
    }
}




