#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "./Value.h"
#include <iostream>
#include <stdlib.h>
class Graph
{
public:
    Graph(Value const *v);
    void build(Value const *v);
    void visualize();

private:
    std::vector<Value *> nodes;
    std::vector<std::pair<Value *, Value *>> edges;
    bool isIn(std::vector<Value *> values, Value *value);
    void buildHelper(Value const *v, std::vector<Value *> &nodes, std::vector<std::pair<Value *, Value *>> &edges);
};

#endif