#include <iostream>
#include <stdlib.h>
#include "allocator.h"
#include "Timer.h"

using namespace std;

int main(int argc, char *argv[]) {
    char *x;
    {
        Timer t;
        char *mallc = (char *)malloc(10000);
        x = mallc;
    }
    cout << "-----" << endl;
    LinearAllocator A(10000);
    char *ans, *st;
    {
        Timer t;
        ans = A.alloc(6000);
    }
    if (ans != nullptr) {
        cout << "Correct" << endl;
    } else {
        cout << "Error" << endl;
    }
    {
        Timer t;
        ans = A.alloc(7000);
    }
    if (ans == nullptr) {
        cout << "Correct" << endl;
    } else {
        cout << "Error" << endl;
    }
    {
        Timer t;
        A.reset();
        ans = A.alloc(7000);
    }
    if (ans != nullptr) {
        cout << "Correct" << endl;
    } else {
        cout << "Error" << endl;
    }
    {
        Timer t;
        ans = A.alloc(0);
    }
    if (ans != nullptr) {
        cout << "Correct" << endl;
    } else {
        cout << "Error" << endl;
    }
    {
        Timer t;
        ans = A.alloc(3000);
    }
    if (ans != nullptr) {
        cout << "Correct" << endl;
    } else {
        cout << "Error" << endl;
    }
    {
        Timer t;
        ans = A.alloc(0);
    }
    if (ans != nullptr) {
        cout << "Correct" << endl;
    } else {
        cout << "Error" << endl;
    }
    cout << "-----" << endl;
    {
        Timer t;
        x = (char *)realloc(x, 10000);
    }
    cout << "-----" << endl;
    free(x);
    A.reset();
    ans = A.alloc(0);
    if (st + 10000 != ans) {
        cout << "Correct" << endl;
    } else {
        cout << "Error" << endl;
    }
    return 0;
}