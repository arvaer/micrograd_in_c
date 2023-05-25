#include <vector>
#include <Value.h>
#include <Graph.h>
#include <iostream>
#include <stdlib.h>

template <typename T>
Graph<T>::Graph(Value<T> const *v)
{
    build(v);
}
template <typename T>
void Graph<T>::build(Value<T> const *v)
{
    buildHelper(v, nodes, edges);
}

template <typename T>
void Graph<T>::visualize()
{
    FILE *pipe = popen("dot -Tpng -o ./graphs/output.png", "w");
    if (pipe)
    {
        char top[256];
        snprintf(top, sizeof(top), "digraph {\n");
        fputs(top, pipe);
        fputs("rankdir=LR;\n", pipe);
        // fputs(top, stdout);
        for (auto node : nodes)
        {
            char label[256];
            std::snprintf(label, sizeof(label),
                          "%d[shape=circle, style=solid, label=\"value :%.3f | grad:%.3f\"];\n",
                          node->id, (node->getValue()), (node->getGrad()));
            fputs(label, pipe);
            // fputs(label, stdout);

            if (node->getOp() != '~')
            {
                char op[256];
                std::snprintf(op, sizeof(op), "%d[label=\"%c\"];\n", node->id + 1, node->getOp());
                fputs(op, pipe);
                // fputs(op, stdout);
                char edge[256];
                std::snprintf(edge, sizeof(edge), "%d -> %d;\n", node->id + 1, node->id);
                fputs(edge, pipe);
                // fputs(edge, stdout);
            }
        }

        for (auto edge : edges)
        {
            char conn[256];
            std::snprintf(conn, sizeof(conn), "%d->%d;\n", (edge.second)->id, (edge.first)->id + 1);
            fputs(conn, pipe);
            // fputs(conn, stdout);
        }
        std::fprintf(pipe, "}\n");
        pclose(pipe);
        std::cout << "Graph visualized to ./graphs/output.png" << std::endl;
    }
}

template <typename T>
bool Graph<T>::isIn(std::vector<Value<T> *> values, Value<T> *value)
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

template <typename T>
void Graph<T>::buildHelper(Value<T> const *v, std::vector<Value<T> *> &nodes, std::vector<std::pair<Value<T> *, Value<T> *>> &edges)
{

    if (!isIn(nodes, const_cast<Value<T> *>(v)))
    {
        nodes.push_back(const_cast<Value<T> *>(v));
        std::vector<Value<T> const *> children = (*v).getChildren();
        if (!children.empty())
        {
            for (const auto child : children)
            {
                std::pair<Value<T> *, Value<T> *> edge(const_cast<Value<T> *>(v), const_cast<Value<T> *>(child));
                edges.push_back(edge);
                buildHelper(child, nodes, edges);
            }
        }
    }
}
