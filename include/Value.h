#ifndef VALUE_H
#define VALUE_H
#include <vector>
#include <memory>
#include <stdlib.h>
#include <functional>

template <typename T = double>
class Value
{
private:
    T data;
    char op[2];
    T grad;
    std::vector<Value<T> const *> prev;

public:
    int id = rand();
    std::function<void()> backward;
    Value<T>();
    Value<T>(T x);
    Value<T>(T x, T initGrad);
    Value<T>(T x, char _op[5], std::vector<Value<T> const *> children);
    Value<T>(const Value<T> &other);
    bool operator==(const Value<T> &other);
    // Value<T>(Value<T> *child);
    Value<T> operator+(Value<T> &obj);
    Value<T> operator*(Value<T> &obj);
    Value<T> operator/(Value<T> &obj);
    Value<T> tanh(bool initialize);
    Value<T> tanh(Value<T> n);
    template <typename Y>
    friend std::ostream &operator<<(std::ostream &os, const Value<Y> &val);
    // friend std::ostream <>&operator<<(std::ostream &os, const Value<T> &val);

    void print() const;
    void children();
    std::vector<Value<T> const *> getChildren() const;
    char getOp() const;
    T getValue() const;
    T getGrad() const;
    void setGrad(T _grad);
    void _backward();

};
template class Value<double>;

#endif