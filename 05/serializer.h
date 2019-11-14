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
    Error save(T&& object)
    {
        return object.serialize(*this);
    }
    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
};

class Deserializer
{
private:
    std::istream &in_;
    static constexpr char Separator = ' ';
    std::string tmp;

    template <class T>
    Error process(T&& val)
    {
        return ser_load(val);
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        if(Error::CorruptedArchive != ser_load(val)) {
            return process(std::forward<Args>(args)...);
        } else {
            return Error::CorruptedArchive;
        }
    }

    Error ser_load(uint64_t &val) {
        in_ >> tmp;
        try {
            if (tmp[0] <= '9' && tmp[0] >= '0') {
                val = strtoull(tmp.c_str(), NULL ,10);
                return Error::NoError;
            } else {
                return Error::CorruptedArchive;
            }
        } catch (const std::exception &e) {
            return Error::CorruptedArchive;
        }
    }
    Error ser_load(bool &val) {
        in_ >> tmp;
        if (!(tmp == "true" || tmp == "false")) {
            return Error::CorruptedArchive;
        } else {
            if (tmp == "true") {
                val = true;
            } else {
                val = false;
            }
            return Error::NoError;
        }
    }
public:
    explicit Deserializer(std::istream& in) : in_(in) {}

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
};
#endif //SPHERE_MATRIX_H
