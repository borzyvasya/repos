#include <iostream>
#include <string>


using namespace std;

bool containsB(const string& input) {
    for (char c : input) {
        if (c == 'b') {
            return true;
        }
    }
    return false; 
}

int main() {
    string input;

    cout << "введите строку (состоящую из символов 'a' и 'b'): ";
    cin >> input;

    if (containsB(input)) {
        cout << "Строка содержит хотя бы одну 'b'." << endl;
    } else {
        cout << "Строка не содержит 'b'." << endl;
    }

    return 0;
}
