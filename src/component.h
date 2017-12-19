#pragma once

#include <cstdint>
#include <string>


class Component
{
public:
    enum Type
    {
        Physical
    };

private:
    Type type_;
    std::string name_;

protected:
    Component(Type type, std::string name);
    virtual ~Component() = default;

public:
    Type get_type() const;
    std::string get_name() const;
};