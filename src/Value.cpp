#include "Value.h"
#include <iostream>
#include <string.h>
#include <math.h>
Value::Value() : data{0}, op{}, grad{0}
{
    std::cout << "Empty Value Object Constructed" << std::endl;
}
Value::Value(int x) : data{x}, op{}, grad{0}
{
    op[0] = '~';
    op[1] = '\0';
}
Value::Value(int x, char _op[2], std::vector<Value const *> children) : data{x}, grad{0}
{
    op[0] = _op[0];
    op[1] = '\0'; // add null terminator
    for (const auto child : children)
    {
        prev.push_back(child);
    }
}
Value::Value(const Value &Other) : data{Other.data}, op{}
{
    op[0] = Other.op[0];
    op[1] = '\0'; // add null terminator
    grad = Other.grad;
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
    // for (const auto child : obj.prev)
    // {
    //     children.push_back(child);
    // }
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
    // for (const auto child : obj.prev)
    // {
    //     children.push_back(child);
    // }
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
    // for (const auto child : obj.prev)
    // {
    //     children.push_back(child);
    // }
    children.push_back(this);
    children.push_back(&obj);
    int value = (data + obj.data);
    Value newValue(value, op, children);
    return newValue;
}

Value Value::tanh() const
{
    std::vector<Value const *> children;
    char op[5] = {'t', 'a', 'n', 'h', '\0'};
    double x = data;
    double t = (exp(2 * x) + 1) / (exp(2 * x) - 1);
    children.push_back(this);

    return Value(t, op, children);
}

std::ostream &operator<<(std::ostream &os, const Value &val)
{
    os << val.data;
    return os;
}

void Value::print() const
{
    std::cout << "v : " << data << " and ";
    std::cout.write(op, 1); // write a single character from op
    std::cout << "\n";
}

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

char Value::getOp() const
{
    return op[0];
}

int Value::getValue() const
{
    return data;
}

double Value::getGrad() const
{
    return grad;
}

void Value::setGrad(double _grad)
{
    grad = _grad;
}