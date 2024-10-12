#include <iostream>
#include <vector>


using namespace std;
int main() {
    int row = 5;
    int column = 5;

    vector<vector<int>> matrix (row, vector<int>(column));


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            matrix[i][j] = rand() % 9 + 1;
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    int multiplication = 1;
    for (int i = 0; i < row; i++) {
        multiplication *= matrix[i][i];
    }

    cout<<multiplication<<endl;


    multiplication = 1;
    for (int i = 0; i < row; i++) {
        multiplication *= matrix[i][row - 1 - i];
    }
    
    
    cout<<multiplication<<endl;


    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (i > j) {  
              matrix[i][j] = 0;
            }
        }
    }


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }



}
