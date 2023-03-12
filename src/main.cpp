#include <vector>
#include <Value.h>
#include <iostream>
#include <stdlib.h>
using namespace ::std;

bool isIn(vector<Value> values, Value value)
{
    for (auto i : values)
    {
        // std::cout << "Checking " << &i << " against " << &value << '\n';
        if (&i == &value)
        {
            return true;
        }
    }
    return false;
}
void build(Value const *v, vector<Value> *node, vector<pair<const Value, Value>> *edges)
{
    if (!isIn(*node, *v))
    {
        node->push_back(*v);
        vector<Value const *> children = (*v).getChildren();
        if (!children.empty())
        {
            for (const auto child : children)
            {
                pair<const Value &, Value> edge(*v, *child);
                (*edges).push_back(edge);
                build(child, node, edges);
            }
        }
    }

    (*v).print();
    for (auto n : *node)
    {
        n.print();
    }
}

int main()
{
    int id;
    vector<Value> nodes;
    vector<pair<const Value, Value>> edges;
    Value a(17);
    Value b(10);
    Value c = a + b;
    build(&c, &nodes, &edges);
    for (auto node : nodes)
    {
        id = rand();
        // need to add edge for op
    }
    // Pipe the output to the dot utility to generate the graph visualization
    // FILE *pipe = popen("dot -Tpng -o ./graphs/output.png", "w");
    // if (pipe)
    // {
    //     fputs("digraph {\n", pipe);
    //     fputs("  x [shape=circle, style=solid];\n", pipe);
    //     fputs("  y [shape=circle, style=solid];\n", pipe);
    //     fputs("  add [label=\"+\", shape=rectangle, style=solid];\n", pipe);
    //     fputs("  mul [label=\"*\", shape=rectangle, style=solid];\n", pipe);
    //     fputs("  two [label=\"2\", shape=rectangle, style=solid];\n", pipe);
    //     fputs("  x -> add;\n", pipe);
    //     fputs("  y -> add;\n", pipe);
    //     fputs("  add -> mul;\n", pipe);
    //     fputs("  two -> mul;\n", pipe);
    //     fputs("}\n", pipe);
    //     fflush(pipe);
    //     pclose(pipe);
    // }
}