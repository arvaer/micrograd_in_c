#include "Value.h"
#include <iostream>

Value::Value() { data = 0; }
Value::Value(int x) { data = x; }
Value::Value(int x, std::vector<Value *> &children) : data{x}, prev{std::move(children)} {}

Value Value::operator+(Value &obj) const
{
    std::vector<Value *> children;

    for (const auto &child : prev)
    {
        children.push_back(std::move(child));
    }
    for (const auto &child : obj.prev)
    {
        children.push_back(std::move(child));
    }
    int stored = (data + obj.data);
    Value newValue(stored, children);
    return newValue;
}

Value Value::operator*(Value &obj) const
{
    std::vector<Value *> children;

    for (const auto &child : prev)
    {
        std::cout << "read?" << std::endl;
        children.push_back(std::move(child));
    }
    for (const auto &child : obj.prev)
    {
        std::cout << "read?" << std::endl;
        children.push_back(std::move(child));
    }
    int stored = (data * obj.data);
    Value newValue(stored, children);
    return newValue;
}

bool operator<(const Value &left, const Value &right)
{
    return left.data < right.data;
}
bool operator!=(const Value &left, const Value &right)
{
    return left.data != right.data;
}
std::ostream &operator<<(std::ostream &os, const Value &val)
{
    os << val.data;
    return os;
}
void Value::print() { std::cout << data << '\n'; }
void Value::children()
{
    for (const auto &child : prev)
    {
        std::cout << (*child).data << std::endl;
    }
}
