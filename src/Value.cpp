#include "Value.h"
#include <iostream>

Value::Value() { data = 0; }
Value::Value(int x) { data = x; }
Value::Value(int x, std::vector<std::unique_ptr<Value>> &children) : data{x}, prev{std::move(children)} {}

Value Value::operator+(Value &obj) const
{
    std::vector<std::unique_ptr<Value>> children;
    children.push_back(std::make_unique<Value>(data));
    children.push_back(std::make_unique<Value>(obj.data));
    Value newValue(data + obj.data, children);
    return newValue;
}

Value Value::operator*(Value &obj) const
{
    std::vector<std::unique_ptr<Value>> children;
    children.push_back(std::make_unique<Value>(data));
    children.push_back(std::make_unique<Value>(obj.data));
    Value newValue(data * obj.data, children);
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
