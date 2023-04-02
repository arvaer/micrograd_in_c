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
    std::function<void()> backward;

public:
    int id = rand();
    Value<T>();
    Value<T>(T x);
    Value<T>(T x, char _op[2], std::vector<Value<T> const *> children);
    Value<T>(const Value<T> &other);
    bool operator==(const Value<T> &other);
    // Value<T>(Value<T> *child);
    Value<T> operator+(Value<T> &obj);
    Value<T> operator*(Value<T> &obj);
    Value<T> operator/(Value<T> &obj);
    Value<T> tanh();
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

};
template class Value<double>;

#endif