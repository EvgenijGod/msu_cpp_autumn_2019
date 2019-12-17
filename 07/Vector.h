#include <iostream>
#include <cstdlib>
#include <iterator>
#include <limits.h>


//using namespace std;
template <class T>
class Allocator
{
public:
    template <class... T1>
    void make(T *tmp, T1&&... zizn) {
        new(tmp) T(std::forward<T1>(zizn)...);
    }
    /*void make(T *tmp) {
        new (tmp) T();
    }
    void make(T *tmp, T&& zizn) {
        new(tmp) T(std::move(zizn));
    }
    void make(T * tmp, const T& zizn) {
        new(tmp) T(zizn);
    }*/
    T* alloc(size_t cnt) {
        return (T*)calloc(cnt, sizeof(T));
    }
    void clear(T* tmp) {
        free(tmp);
    }
    void erase(T* tmp) {
        tmp->~T();
    }
};

template <class T>
class Iterator : std::iterator<std::random_access_iterator_tag, T>
{
public:
    explicit Iterator(T * tmp) {
        my = tmp;
    }
    T& operator*() {
        return *my;
    }
    Iterator& operator++ () {
        ++my;
        return *this;
    }
    Iterator operator+= (size_t c) {
        my += c;
        return *this;
    }
    Iterator operator-= (size_t c) {
        my -= c;
        return *this;
    }
    Iterator operator[](size_t c) {
        return *(my + c);
    }
    Iterator& operator-- () {
        --my;
        return *this;
    }
    bool operator==(const Iterator<T> &tmp) {
        if (tmp.my == my) {
            return true;
        }
        return false;
    }
    bool operator!=(const Iterator<T> &tmp) {
        return !(tmp == *this);
    }

private:
    T* my;
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;
    Vector(){

    };
    Vector(size_t num) {
        if (num != 0) {
            content_num = size_num = num;
            info = alloc_.alloc(num);
            size_t i = 0;
            while (i < num) {
                alloc_.make(info + i);
                i++;
            }
        }
    }
    size_t size() {
        return size_num;
    }
    bool empty() {
        if (size_num > 0) {
            return false;
        }
        return true;
    }
    T& operator[] (size_t i) {
        if (i < size_num) {
            return info[i];
        } else {
            throw std::out_of_range("index is out of range\n");
        }
    }
    const T& operator[] (size_t i) const {
        if (i < size_num) {
            return info[i];
        } else {
            throw std::out_of_range("index is out of range\n");
        }
    }
    iterator begin(){
        return iterator(info);
    }
    iterator end(){
        return iterator(info + size_num);
    }

    const iterator begin() const {
        return iterator(info);
    }
    const iterator end() const {
        return iterator(info + size_num);
    }
    std::reverse_iterator<T> rbegin() {
        return std::reverse_iterator<T>(end());
    }
    std::reverse_iterator<T> rend() {
        return std::reverse_iterator<T>(begin());
    }
    const std::reverse_iterator<T> rbegin() const{
        return std::reverse_iterator<T>(end());
    }
    const std::reverse_iterator<T> rend() const {
        return std::reverse_iterator<T>(begin());
    }
    void reserve(size_t num) {
        if (num > content_num) {
            T* tmp_info = alloc_.alloc(num);
            for (size_t i = 0; i < num; i++) {
                alloc_.make(tmp_info + i, info[i]);
                alloc_.erase(info + i);
            }
            std::swap(info, tmp_info);
            alloc_.clear(tmp_info);
            content_num = num;
        }
    }
    void resize(size_t num) {
        if (size_num == 0) {
            content_num = size_num = num;
            info = alloc_.alloc(num);
            size_t i = 0;
            while (i < num) {
                alloc_.make(info + i);
                i++;
            }
            return;
        }
        if (num < size_num) {
            for (size_t i = num; i < size_num; i++) {
                alloc_.erase(info + i);
            }
        }
        if (num > content_num) {
            reserve(num);
        }
        if (num > size_num) {
            for (size_t i = size_num; i < num; i++) {
                alloc_.make(info + i);
            }
        }
        size_num = num;
    }
    void clear() {
        resize(0);
    }
    void push_back(T&& tmp) {
        if (content_num == size_num) {
            if (content_num != 0) {
                reserve(size_num * 2);
            } else {
                reserve(1);
            }
        }
        alloc_.make(info + size_num++, std::move(tmp));
    }
    void pop_back() {
        if (size_num > 0) {
            resize(size_num - 1);
        }
    }

    ~Vector() {
        clear();
        alloc_.clear(info);

    }
    void push_back(const T& tmp) {
        if (content_num == size_num) {
            if (content_num != 0) {
                reserve(size_num * 2);
            } else {
                reserve(4);
            }
        }
        alloc_.make(info + size_num++, tmp);
    }

private:
    Alloc alloc_;
    T* info = nullptr;
    size_t size_num = 0;
    size_t content_num = 0;
};