#include "Value.h"
#include <iostream>
#include <string.h>
Value::Value() {}
Value::Value(int x)
{
    data = x;
    op[0] = '~';
    op[1] = '\0';
    std::cout << "Constructed Value with op = " << op << '\n';
}
Value::Value(int x, char _op[2], std::vector<Value const *> children) : data{x}, op{*_op}
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

bool Value::operator==(const Value &other) const
{
    return data == other.data && strcmp(op, other.op) == 0 && prev == other.prev;
}

Value Value::operator+(Value &obj) const
{
    std::vector<Value const *> children;
    char op[2] = {'+', '\0'};
    for (const auto child : obj.prev)
    {
        children.push_back(child);
    }
    children.push_back(this);
    children.push_back(&obj);
    int stored = (data + obj.data);
    Value newValue(stored, op, children);
    return newValue;
}

Value Value::operator*(Value &obj) const
{
    std::vector<Value const *> children;
    char op[2] = {'*', '\0'};
    for (const auto child : obj.prev)
    {
        children.push_back(child);
    }
    children.push_back(this);
    children.push_back(&obj);
    int stored = (data * obj.data);
    Value newValue(stored, op, children);
    return newValue;
}
Value Value::operator/(Value &obj) const
{
    std::vector<Value const *> children;
    char op[2] = {'/', '\0'};
    for (const auto child : obj.prev)
    {
        children.push_back(child);
    }
    children.push_back(this);
    children.push_back(&obj);
    int value = (data + obj.data);
    Value newValue(value, op, children);
    return newValue;
}

std::ostream &operator<<(std::ostream &os, const Value &val)
{
    os << val.data;
    return os;
}
void Value::print() const { std::cout << data << " and " << op << '\n'; }
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

std::vector<Value const *> Value::getChildren() const
{
    return prev;
}

void Value::getOp() const
{
    std::cout << op << std::endl;
}