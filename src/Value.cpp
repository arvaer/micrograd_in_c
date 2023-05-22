#include <Value.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <functional>

template <typename T>
Value<T>::Value() : data{0}, op{}, grad{0}
{
    std::cout << "Empty Value Object Constructed" << std::endl;
}
template <typename T>
Value<T>::Value(T x) : data{x}, op{}, grad{0}
{
    op[0] = '~';
    op[1] = '\0';
}

template <typename T>
Value<T>::Value(T x, T initGrad) : data{x}, op{}, grad{initGrad} 
{
    op[0] = '~';
    op[1] = '\0';
}

template <typename T>
Value<T>::Value(T x, char _op[5], std::vector<Value<T> const *> children) : data{x}, grad{0}
{
    op[0] = _op[0];
    op[1] = '\0'; // add null terminator
    for (const auto child : children)
    {
        prev.push_back(child);
    }
}

template <typename T>
Value<T>::Value(const Value<T> &Other) : data{Other.data}, op{}
{
    op[0] = Other.op[0];
    op[1] = '\0'; // add null terminator
    grad = Other.grad;
    for (const auto child : Other.prev)
    {
        prev.push_back(child);
    }
}
template <typename T>
bool Value<T>::operator==(const Value<T> &other)
{
    return data == other.data && strcmp(op, other.op) == 0 && prev == other.prev;
}

template <typename T>
Value<T> Value<T>::operator+(Value<T> &obj) 
{
    std::vector<Value<T> const *> children;
    char op[2] = {'+', '\0'};
    children.push_back(this);
    children.push_back(&obj);
    T stored = (data + obj.data);
    Value<T> newValue(stored, op, children);

    newValue.backward = [this, &obj, &newValue](){
        std::cout << "add" << std::endl;
        grad += (1 * newValue.grad);
        obj.grad += (1 * newValue.grad);
    };

    return newValue;
}

template <typename T>
Value<T> Value<T>::operator*(Value<T> &obj) 
{
    std::vector<Value<T> const *> children;
    char op[2] = {'*', '\0'};
    children.push_back(this);
    children.push_back(&obj);
    T stored = (data * obj.data);
    Value<T> newValue(stored, op, children);
    newValue.backward = [this, &obj, &newValue](){
        std::cout << "mult" << std::endl;
        grad += (obj.data * newValue.grad);
        obj.grad += (data * newValue.grad);
    };

    return newValue;
}

template <typename T>
Value<T> Value<T>::operator/(Value<T> &obj) 
{
    std::vector<Value<T> const *> children;
    char op[2] = {'/', '\0'};
    children.push_back(this);
    children.push_back(&obj);
    T value = (data / obj.data);
    Value<T> newValue(value, op, children);
    newValue.backward = [this, &obj, &newValue](){
        std::cout << "div" << std::endl;
        grad += (obj.data * newValue.grad);
        obj.grad += (data * newValue.grad);
    };

    return newValue;
}
template <typename T>
Value<T> Value<T>::tanh(bool initialize){
    std::vector<Value<T> const *> children;
    char op[5] = {'t', 'a', 'n', 'h', '\0'};
    T value = data;
    T t = (exp(2 * value) + 1) / (exp(2 * value) - 1);
    children.push_back(this);
    Value<T> result(t, op, children);
    if (initialize){
        result.grad = 1.0;
    }

    result.backward = [this, &result]()
    {
        std::cout << "tanh" << std::endl;
        T dtanh = 1 - std::pow(std::tanh(data), 2);
        std::cout << "dtanh:" << dtanh << "result.grad: "<< result.grad << std::endl;
        grad += dtanh * result.grad ; 
    };
    return result;
}

template <typename T>
Value<T> Value<T>::tanh(Value<T> n)
{
    std::vector<Value<T> const *> children;
    char op[5] = {'t', 'a', 'n', 'h', '\0'};
    T value = n.data;
    T t = (exp(2 * value) + 1) / (exp(2 * value) - 1);
    children.push_back(&n);
    children.push_back(this);
    Value<T> result(t, op, children);

    result.backward = [this, &result]()
    {
        std::cout << "tanh" << std::endl;
        T dtanh = 1 - std::pow(std::tanh(data), 2);
        grad += dtanh * result.grad ; 
    };

    return result;
}


template <typename T>
std::ostream &operator<<(std::ostream &os, const Value<T> &val)
{
    os << val.data;
    return os;
}

template <typename T>
void Value<T>::print() const
{
    std::cout << "v : " << data << " and ";
    std::cout.write(op, 1); // write a single character from op
    std::cout << "\n";
}

template <typename T>
void Value<T>::children()
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

template <typename T>
std::vector<Value<T> const *> Value<T>::getChildren() const
{
    return prev;
}

template <typename T>
char Value<T>::getOp() const
{
    return op[0];
}

template <typename T>
T Value<T>::getValue() const
{
    return data;
}

template <typename T>
T Value<T>::getGrad() const
{
    return grad;
}

template <typename T>
void Value<T>::setGrad(T _grad)
{
    grad = _grad;
}
template <typename T>
void Value<T>::_backward(){
   backward();
}