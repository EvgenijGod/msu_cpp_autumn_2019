#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Vector.h"
using namespace std;

int main() {
    Vector<int> A(10);
    cout << A.size() << endl;
    for (size_t i = 0; i < 10; i++) {
        A[i] = 10 - i;
    }
    for (size_t i = 0; i < 10; i++) {
        cout << A[i] << " ";
    }
    A.push_back(-133);
    cout << endl;
    for (size_t i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    A.resize(19);
    for (size_t i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << "\n" << A.size();
    cout << endl;
    A.resize(3);
    cout << A.size() << "\n";
    A.clear();
    cout << A.size() << "\n";
    for (size_t i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }
    Vector<pair<int, int>> B;
    B.resize(2);
    B[0] = {0, 0};
    B[1] = {1, 1};
    for (int i = 0; i < B.size(); i++) {
        cout << B[i].first << " " << B[i].second << "\n";
    }
    B.pop_back();
    cout << endl;
    for (int i = 0; i < B.size(); i++) {
        cout << B[i].first << " " << B[i].second << "\n";
    }
    cout << "OK";
    return 0;
}