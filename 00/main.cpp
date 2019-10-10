#include <iostream>
#include <string>
#include <random>
#include "Timer.cpp"

using namespace std;
enum{ N = 8000, M = 1000 };
int *arr;

void columns_sum() {
    Timer time;
    volatile long long sum = 0;
    for (int i = 0; i < M; i++) {
        volatile long long tmp = 0;
        for (int j = 0; j < N; j++) {
            sum += arr[tmp + i];
            tmp += M;
        }
    }
    cout << sum << endl;
}

void rows_sum() {
    Timer time;
    volatile long long sum = 0;
    volatile long long tmp = N * M;
    for (int i = 0; i < tmp; i++) {
        sum += arr[i];
    }
    cout << sum << endl;
}

int main()
{
    arr = new int[N * M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            arr[i * M + j] = rand() % 10;
        }
    }
    columns_sum();
    rows_sum();
    delete[] arr;
    return 0;
}