#include <vector>
#include <Value.h>
#include <iostream>
#include <stdlib.h>
using namespace ::std;

bool isIn(vector<Value *> values, Value *value)
{
    for (auto i : values)
    {
        if (i == value)
        {
            return true;
        }
    }
    return false;
}

void build(Value const *v, vector<Value *> &nodes, vector<pair<const Value *, Value>> &edges)
{
    if (!isIn(nodes, const_cast<Value *>(v)))
    {
        nodes.push_back(const_cast<Value *>(v));
        vector<Value const *> children = (*v).getChildren();
        if (!children.empty())
        {
            for (const auto child : children)
            {
                pair<const Value *, Value> edge(v, *child);
                edges.push_back(edge);
                build(child, nodes, edges);
            }
        }
    }
}

int main()
{
    vector<Value *> nodes;
    vector<pair<const Value *, Value>> edges;
    Value a(17);
    Value b(10);
    Value c = a + b;
    build(&c, nodes, edges);
    for (auto node : nodes)
    {
        int id = rand();
        // create a record for each node;
        cout << id << "[shape=circle, style=solid, label=\"" << node->getValue() << "\"]" << endl;
        if (node->getOp() != '~')
        {
            // if the record is the result of an operation, create an op node
            int id2 = rand();
            cout << id2 << "[label=\"" << node->getOp() << "\"]" << endl;
            // connect the node to that edge
            cout << id2 << " -> " << id << endl;
        }
    }

    for (auto n1, auto n2 : edges)
    {
    }
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
