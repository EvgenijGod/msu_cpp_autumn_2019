#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <limits.h>
#include <assert.h>
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
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }

};

int main() {
    Data x { 1, false, 2 };
    stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    cout << stream.str() << endl;

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    Data x1 { 42, false, 207 };
    stringstream stream1;
    Serializer serializer1(stream1);
    serializer1.save(x1);
    cout << stream1.str() << endl;

    Data y1 { 42, true, 77};

    Deserializer deserializer1(stream1);
    const Error err1 = deserializer1.load(y1);
    assert(err == Error::NoError);
    assert(x1.a == y1.a);
    assert(x1.b == y1.b);
    assert(x1.c == y1.c);
    cout << "OK";
    return 0;
}