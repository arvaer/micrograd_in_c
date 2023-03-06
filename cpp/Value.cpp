#include <iostream>
#include <math.h>
#include <vector>
#include <memory>
using namespace std;
class Value
{
private:
    int data;
    vector<unique_ptr<Value>> prev;

public:
    Value() { data = 0; }
    Value(int x) { data = x; }
    Value(int x, auto &children) : data{x}, prev{move(children)} {};

    Value operator+(Value const &obj)
    {
        // need to add the values of obj and data together
        vector<unique_ptr<Value>> children;
        children.insert(children.end(), make_unique<Value>(*this));
        children.insert(children.end(), make_unique<Value>(obj));
        Value newValue(data + obj.data, children);
        return newValue;
    }

    Value operator*(Value const &obj)
    {
        vector<unique_ptr<Value>> children;
        children.insert(children.end(), make_unique<Value>(*this));
        children.insert(children.end(), make_unique<Value>(obj));
        Value newValue(data + obj.data, children);
        return newValue;
    }

    friend bool operator<(const Value &left, const Value &right)
    {
        return left.data < right.data;
    }
    friend bool operator!=(const Value &left, const Value &right)
    {
        return left.data != right.data;
    }
    friend ostream &operator<<(ostream &os, const Value &val)
    {
        os << val.data;
        return os;
    }
    void print() { cout << data << '\n'; }
    void children()
    {
        vector<Value *> children = getPrev();
        for (auto itr : children)
        {
            cout << (*itr).data << endl;
        }
    }

    vector<Value *> getPrev() const
    {
        vector<Value *> result;
        for (const auto &child : prev)
        {
            result.push_back(child.get());
        }
        return result;
    }
};

int main()
{
    Value a(10);
    Value b(17);
    Value c = a + b;

    c.print();
    return 0;
}