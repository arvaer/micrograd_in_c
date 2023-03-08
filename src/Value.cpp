#include "Value.h"
#include <iostream>

Value::Value() { data = 0; }
Value::Value(int x) { data = x; }
Value::Value(int x, std::vector<Value const *> children) : data{x}
{
    for (const auto child : children)
    {
        prev.push_back(child);
    }
}

Value::Value(const Value &Other) : data{Other.data}
{
    for (const auto child : Other.prev)
    {
        prev.push_back(child);
    }
}
Value Value::operator+(Value &obj) const
{
    std::vector<Value const *> children;
    for (const auto child : obj.prev)
    {
        children.push_back(child);
    }
    children.push_back(this);
    children.push_back(&obj);
    int stored = (data + obj.data);
    Value newValue(stored, children);
    return newValue;
}

Value Value::operator*(Value &obj) const
{
    std::vector<Value const *> children;
    for (const auto child : obj.prev)
    {
        children.push_back(child);
    }
    children.push_back(this);
    children.push_back(&obj);
    int stored = (data * obj.data);
    Value newValue(stored, children);
    return newValue;
}
std::ostream &operator<<(std::ostream &os, const Value &val)
{
    os << val.data;
    return os;
}
void Value::print() const { std::cout << data << '\n'; }
void Value::children()
{
    std::cout << "@Number of children: " << prev.size() << '\n';
    for (size_t i = 0; i < prev.size(); ++i)
    {
        std::cout << "Child " << i + 1 << " (from ";
        if (i < prev.size() - 1)
        {
            std::cout << "operator)";
        }
        else
        {
            std::cout << "input value)";
        }
        std::cout << ": " << prev[i]->data << '\n';
    }
}