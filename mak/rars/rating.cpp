#include <string>
#include <iostream>
using namespace std;

string calculateRARS(int answers[]); // ???????? ???????

int main() {
    string questions[] = {
        // 0
        "Does the content deny family values and create disrespect for parents and (or) other family members? (Answer 0 - no, 1 - yes)",
        // 1
        "Does the content have information about narcotic drugs or psychotropic and (or) intoxicating substances? (Answer 0 - no, 1 - yes)",
        // 2
        "Does the content have image or description that does not encourage antisocial behavior? (Answer 0 - no, 1 - yes)",
        // 3
        "Does the content have description of an accident, catastrophe or non-violent death? (Answer 0 - no, 1 - yes)",
        // 4
        "Does the content have sexual content? (Answer 0 - no, 1 - yes)",
        // 5
        "Does the content have erotic content? (Answer 0 - no, 1 - yes)",
        // 6
        "Does the content mention sexual things? (Answer 0 - no, 1 - yes)",
        // 7
        "Does the content have slaughtering, blood, etc? (Answer 0 - no, 1 - yes)"
    };

    int answers[7];

    for (int i = 0; i < 7; i++) {
        cout << questions[i] << endl;

        while (true) {
            cin >> answers[i];

            if (cin.fail() || (answers[i] != 0 && answers[i] != 1)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter 0 (no) or 1 (yes). Try again:" << endl;
            }
            else {
                break;
            }
        }
    }

    string rating = calculateRARS(answers);

    cout << "RARS Rating is: " << rating << endl;

    return EXIT_SUCCESS;
}

string calculateRARS(int answers[]) {
    if (answers[0] == 1 || answers[4] == 1 || answers[7] == 1) {
        return "18+";
    }

    if (answers[1] == 1) {
        return "16+";
    }

    if (answers[5] == 1 || answers[6] == 1 || answers[2] == 1) {
        return "12+";
    }

    if (answers[3] == 1) {
        return "6+";
    }

    return "0+";
}