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
    // for (auto node : nodes)
    // {
    //     // create a record for each node;
    //     cout << node->id << "[shape=circle, style=solid, label=\"" << node->getValue() << "\"];" << endl;
    //     if (node->getOp() != '~')
    //     {
    //         // if the record is the result of an operation, create an op node
    //         // naivly add 1 to a nodes id to get the op id
    //         cout << node->id + 1 << "[label=\"" << node->getOp() << "\"];" << endl;
    //         // connect the node to that edge
    //         cout << node->id + 1 << " -> " << node->id << ";" << endl;
    //     }
    // }

    // for (auto edge : edges)
    // {
    //     cout << (edge.second).id + 1 << "->" << (edge.first)->id << ";" << endl;
    // }

    // Pipe the output to the dot utility to generate the graph visualization
    FILE *pipe = popen("dot -Tpng -o ./graphs/output.png", "w");
    if (pipe)
    {
        char top[256];
        snprintf(top, sizeof(top), "digraph {\n");
        fputs(top, stdout);
        fputs(top, pipe);
        // std::fprintf(stdout, "digraph {\n");
        // std::fprintf(pipe, "drigraph {\n");

        for (auto node : nodes)
        {
            // create a record for each node;
            char label[256];
            snprintf(label, sizeof(label), "%d[shape=circle, style=solid, label=\"%d\"];\n", node->id, static_cast<int>(node->getValue()));
            fputs(label, pipe);
            fputs(label, stdout);
            if (node->getOp() != '~')
            {
                // if the record is the result of an operation, create an op node
                // naivly add 1 to a nodes id to get the op id
                char op[256];
                snprintf(op, sizeof(op), "%d[label=\"%c\"];\n", node->id + 1, node->getOp());
                fputs(op, stdout);
                fputs(op, pipe);
                // connect the node to that edge
                char edge[256];
                snprintf(edge, sizeof(edge), "%d -> %d;\n", node->id + 1, node->id);
                fputs(edge, stdout);
                fputs(edge, pipe);
            }
        }

        for (auto edge : edges)
        {
            char conn[256];
            snprintf(conn, sizeof(conn), "%d->%d;\n", (edge.second).id + 1, (edge.first)->id);
            fputs(conn, stdout);
            fputs(conn, pipe);
        }
        std::fprintf(stdout, "}\n");
        std::fprintf(pipe, "}\n");
        pclose(pipe); // Close the pipe file pointer after using it
    }
}