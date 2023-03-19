#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "./Value.h"
#include <iostream>
#include <stdlib.h>

template <typename T = double>
class Graph
{
public:
    Graph(Value<T> const *v);
    void build(Value<T> const *v);
    void visualize();

private:
    std::vector<Value<T> *> nodes;
    std::vector<std::pair<Value<T> *, Value<T> *>> edges;
    bool isIn(std::vector<Value<T> *> values, Value<T> *value);
    void buildHelper(Value<T> const *v, std::vector<Value<T> *> &nodes, std::vector<std::pair<Value<T> *, Value<T> *>> &edges);
};

template class Graph<double>;
#endif