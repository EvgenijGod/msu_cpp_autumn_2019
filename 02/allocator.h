#include <stdlib.h>

class LinearAllocator
{
    size_t max_size = 0, cur_iter = 0;
    char *st = nullptr;
    char *current = nullptr;
public:
    LinearAllocator(size_t maxSize) {
        max_size = maxSize;
        st = (char *)malloc(maxSize);
        current = st;
    }
    char* alloc(size_t size) {
        if (cur_iter + size > max_size) {
            return nullptr;
        }
        cur_iter += size;
        char *res = current;
        current += size;
        return res;
    }
    void reset() {
        cur_iter = 0;
        current = st;
    }
    ~LinearAllocator() {
        free(st);
    }
};