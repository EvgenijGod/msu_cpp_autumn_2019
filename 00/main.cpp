#include <iostream>
#include <string>
#include <random>
#include "Timer.cpp"

using namespace std;
enum{ N = 3000 };
int *arr;

void columns_sum() {
    Timer time;
    volatile long long sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += arr[i * N + j];
        }
    }
    cout << sum << endl;
}

void rows_sum() {
    Timer time;
    volatile long long sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += arr[j * N + i];
        }
    }
    cout << sum << endl;
}

int main()
{
    arr = new int[N * N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i * N + j] = rand() % 10;
        }
    }
    columns_sum();
    rows_sum();
    delete[] arr;
    return 0;
}