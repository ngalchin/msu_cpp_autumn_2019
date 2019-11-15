#pragma once
#include <sstream>
#include <cassert>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
private:
    static constexpr char Separator = ' ';
    std::ostream& out_;

    template <class T, class... ArgsT>
    Error process(T&& value, ArgsT&&... args)
    {
        make(value);
        return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& value)
    {
        make(value);
        return Error::NoError;
    }
/////////////////////////////////
    void make(bool value)
    {
        if (value)
            out_ << "true";
        else
            out_ << "false";
        out_ << Separator;
    }

    void make(uint64_t value)
    {
        out_ << value << Separator;
    }
/////////////////////////////////
public:
    explicit Serializer(std::ostream& out) : out_(out) {}

    template <class T>
    Error save(T& object)
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
    static constexpr char Separator = ' ';
    std::istream& in_;

    template <class T, class... ArgsT>
    Error process(T&& value, ArgsT&&... args)
    {
        if (make(value) == Error::CorruptedArchive)
            return Error::CorruptedArchive;

        return process(std::forward<ArgsT>(args)...);
    }

    template <class T>
    Error process(T&& value)
    {
        return make(value);
    }
/////////////////////////////////
    Error make(bool& value)
    {
        std::string text;
        in_ >> text;
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error make(uint64_t& value)
    {
        std::string text;
        in_ >> text; // Check if text is uint..
        for (size_t i = 0; i < text.length(); i++)
        {
            if (!std::isdigit(text[i]))
                return Error::CorruptedArchive;
        }
        value = std::stoull(text);
        return Error::NoError;
    }
/////////////////////////////////
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
