#ifndef VALUE_H
#define VALUE_H
#include <vector>
#include <memory>

class Value
{
private:
    int data;
    std::vector<Value *> prev;

public:
    Value();
    Value(int x);
    Value(int x, std::vector<Value *> &children);

    Value operator+(Value &obj) const;
    Value operator*(Value &obj) const;

    friend bool operator<(const Value &left, const Value &right);
    friend bool operator!=(const Value &left, const Value &right);
    friend std::ostream &operator<<(std::ostream &os, const Value &val);

    void print();
    void children();
};

#endif