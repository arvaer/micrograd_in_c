#include <vector>
#include <Value.h>
#include <Graph.h>
#include <iostream>
#include <stdlib.h>

Graph::Graph(Value const *v)
{
    build(v);
}
void Graph::build(Value const *v)
{
    buildHelper(v, nodes, edges);
}

void Graph::visualize()
{
    FILE *pipe = popen("dot -Tpng -o ./graphs/output.png", "w");
    if (pipe)
    {
        char top[256];
        snprintf(top, sizeof(top), "digraph {\n");
        fputs(top, pipe);
        fputs("rankdir=LR;\n", pipe);
        fputs(top, stdout);
        for (auto node : nodes)
        {
            char label[256];
            std::snprintf(label, sizeof(label),
                          "%d[shape=circle, fixedsize=false, width=0.6, style=solid, label=\"value :%d | grad:%d\"];\n",
                          node->id, static_cast<int>(node->getValue()), static_cast<int>(node->getGrad()));
            // std::snprintf(label, sizeof(label),
            //               "%d[shape=circle, style=solid, label=\"value :%d | grad:%d\"];\n",
            //               node->id, static_cast<int>(node->getValue()), static_cast<int>(node->getGrad()));
            fputs(label, pipe);
            fputs(label, stdout);

            if (node->getOp() != '~')
            {
                char op[256];
                std::snprintf(op, sizeof(op), "%d[label=\"%c\"];\n", node->id + 1, node->getOp());
                fputs(op, pipe);
                fputs(op, stdout);
                char edge[256];
                std::snprintf(edge, sizeof(edge), "%d -> %d;\n", node->id + 1, node->id);
                fputs(edge, pipe);
                fputs(edge, stdout);
            }
        }

        for (auto edge : edges)
        {
            char conn[256];
            std::snprintf(conn, sizeof(conn), "%d->%d;\n", (edge.second)->id, (edge.first)->id + 1);
            fputs(conn, pipe);
            fputs(conn, stdout);
        }
        std::fprintf(pipe, "}\n");
        pclose(pipe);
        std::cout << "Graph visualized to ./graphs/output.png" << std::endl;
    }
}

bool Graph::isIn(std::vector<Value *> values, Value *value)
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

void Graph::buildHelper(Value const *v, std::vector<Value *> &nodes, std::vector<std::pair<Value *, Value *>> &edges)
{

    if (!isIn(nodes, const_cast<Value *>(v)))
    {
        nodes.push_back(const_cast<Value *>(v));
        std::vector<Value const *> children = (*v).getChildren();
        if (!children.empty())
        {
            for (const auto child : children)
            {
                std::pair<Value *, Value *> edge(const_cast<Value *>(v), const_cast<Value *>(child));
                edges.push_back(edge);
                buildHelper(child, nodes, edges);
            }
        }
    }
}
