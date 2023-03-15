#ifndef VALUE_H
#define VALUE_H
#include <vector>
#include <memory>
#include <stdlib.h>
class Value
{
private:
    int data;
    char op[2];
    double grad;
    std::vector<Value const *> prev;

public:
    int id = rand();
    Value();
    Value(int x);
    Value(int x, char _op[2], std::vector<Value const *> children);
    Value(const Value &other);
    bool operator==(const Value &other) const;
    Value(Value *child);
    Value operator+(Value &obj) const;
    Value operator*(Value &obj) const;
    Value operator/(Value &obj) const;

    friend std::ostream &operator<<(std::ostream &os, const Value &val);

    void print() const;
    void children();
    std::vector<Value const *> getChildren() const;
    char getOp() const;
    int getValue() const;
    double getGrad() const;
    void setGrad(double _grad);
};

#endif