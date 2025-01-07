//
// Created by milen on 27/03/2024.
//
#include <iostream>
#include <cstring>
#define NEDELI 4
#define DENOVI 5

using namespace std;

struct RabotnaNedela{
    int casovi[7];
    int brned;

};
struct Rabotnik{
    char ime[50];
    RabotnaNedela nedeli[4];
};

int maxNedela(Rabotnik *r) {
    int maxHours = 0;
    int maxWeek = 0;

    for (int i = 0; i < NEDELI; ++i) {
        int sum = 0;
        for (int j = 0; j < DENOVI; ++j) {
            sum += r->nedeli[i].casovi[j];
        }
        if (sum > maxHours) {
            maxHours = sum;
            maxWeek = i + 1; // Week numbers start from 1
        }
    }

    return maxWeek;
}

// Function to print the table of employees
void table(Rabotnik *r, int n) {
    cout << "Rab\t1\t2\t3\t4\tVkupno" << endl;
    for (int i = 0; i < n; ++i) {
        cout << r[i].ime << "\t";
        int totalHours = 0;
        for (int j = 0; j < NEDELI; ++j) {
            int sum = 0;
            for (int k = 0; k < DENOVI; ++k) {
                sum += r[i].nedeli[j].casovi[k];
            }
            cout << sum << "\t";
            totalHours += sum;
        }
        cout << totalHours << endl;
    }
}

int main() {
    int n;
    cin >> n;
    Rabotnik rabotnici[n];
    for (int i = 0; i < n; ++i) {
        cin >> rabotnici[i].ime;
        for (int j = 0; j < NEDELI; ++j) {
            for (int k = 0; k < DENOVI; ++k) {
                cin >> rabotnici[i].nedeli[j].casovi[k];
            }
        }
    }
    cout << "TABLE" << endl;
    table(rabotnici, n);
    cout << "MAX NEDELA NA RABOTNIK: " << rabotnici[n / 2].ime << endl;
    cout << maxNedela(&rabotnici[n / 2]) << endl;
    return 0;
}