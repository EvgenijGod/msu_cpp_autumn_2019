#include <iostream>
#include <assert.h>
#include "Thread.h"

class A {

};

void foo(const A &) {
    std::cout << "1\n";
}

int main() {
    ThreadPool pool(10);
    auto f1 = pool.exec(foo, A());
    f1.get();
    auto f2 = pool.exec([]() { return 1; });
    if (f2.get() == 1) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAULT\n";
    }
    return 0;
}