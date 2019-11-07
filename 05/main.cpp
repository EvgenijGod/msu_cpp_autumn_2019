#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <limits.h>
#include "serializer.h"
using namespace std;

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

int main() {
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    cout << stream.str();
    return 0;
    Data y { 0, false, 0 };

    /*Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);*/
    return 0;
}