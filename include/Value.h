#ifndef VALUE_H
#define VALUE_H
#include <vector>
#include <memory>

class Value
{
private:
    int data;
    char label;
    std::vector<Value const *> prev;

public:
    Value();
    Value(int x);
    Value(int x, std::vector<Value const *> children);
    Value(const Value &other);
    Value(Value *child);
    Value operator+(Value &obj) const;
    Value operator*(Value &obj) const;

    friend std::ostream &operator<<(std::ostream &os, const Value &val);

    void print() const;
    void children();
};

#endif