#ifndef SPHERE_MATRIX_H
#define SPHERE_MATRIX_H

#include <iostream>

#pragma once

#include <ostream>
enum class Error
{
    NoError,
    CorruptedArchive
};



class Serializer
{   private:
    std::ostream &out_;
    static constexpr char Separator = ' ';
    void Save(bool val) {
        if (val == true)
            out_ << "true" << Separator;
        else
            out_ << "false" << Separator;
    }
    void Save(uint64_t val) {
        out_ << val << Separator;
    }
    template <class T>
    Error process(T&& val)
    {
        Save(val);
        return Error::NoError;
    }
    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        Save(val);
        return process(std::forward<Args>(args)...);
    }
public:
    explicit Serializer(std::ostream& out) : out_(out) {}
    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
};

class Deserializer
{   private:
    std::istream &in_;
    static constexpr char Separator = ' ';
    void Save(bool val) {
        if (val == true)
            out_ << "true" << Separator;
        else
            out_ << "false" << Separator;
    }
    void Save(uint64_t val) {
        out_ << val << Separator;
    }
    template <class T>
    Error process(T&& val)
    {
        load(val);
        return Error::NoError;
    }
    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        load(val);
        return process(std::forward<Args>(args)...);
    }
public:
    explicit Deserializer(std::istream& in) : in_(in) {}
    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
};
#endif //SPHERE_MATRIX_H
