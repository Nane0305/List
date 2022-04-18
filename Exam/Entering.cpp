
#include "Entering.h"

#include <iostream>
#include <iomanip>

using namespace std;

int EnterNumber(const char* prompt) {
    int num;
    cout << "\n" << prompt << " : ";
    cin >> num;
    cin.ignore();
    return num;
}

int EnterNumber(const char* prompt, int min, int max) {
    while (true) {
        int value = EnterNumber(prompt);
        if (value >= min && value <= max) {
            return value;
        }
        cerr << "¬ведите значение в пределах между " << min << " и " << max << endl;
    }
}