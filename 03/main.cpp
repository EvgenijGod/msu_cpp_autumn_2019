#include <iostream>
#include <stdlib.h>
#include "Matrix.h"
using namespace std;


int main(int argc, char *argv[]) {
    Matrix m1(2, 3);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }
    m1 *= 10;
    cout << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    m1[1][1] = 17;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    Matrix m2(2, 3);
    try {
        m2[10][1] = 1111;
    } catch (const exception &e) {
        cerr << e.what();
    }
    cout << (m1 != m2) << endl;
    cout << (m1 == m2) << endl;
    return 0;
}