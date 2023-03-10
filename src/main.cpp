#include <vector>
#include <Value.h>
#include <iostream>
using namespace ::std;
int main()
{
    cout << "digraph {\n";
    cout << "  x [shape=circle, style=solid];\n";
    cout << "  y [shape=circle, style=solid];\n";
    cout << "  add [label=\"+\", shape=rectangle, style=solid];\n";
    cout << "  mul [label=\"*\", shape=rectangle, style=solid];\n";
    cout << "  two [label=\"2\", shape=rectangle, style=solid];\n";
    cout << "  x -> add;\n";
    cout << "  y -> add;\n";
    cout << "  add -> mul;\n";
    cout << "  two -> mul;\n";
    cout << "}\n";

    // Pipe the output to the dot utility to generate the graph visualization
    FILE *pipe = popen("dot -Tpng -o ./graphs/output.png", "w");
    if (pipe)
    {
        fputs("digraph {\n", pipe);
        fputs("  x [shape=circle, style=solid];\n", pipe);
        fputs("  y [shape=circle, style=solid];\n", pipe);
        fputs("  add [label=\"+\", shape=rectangle, style=solid];\n", pipe);
        fputs("  mul [label=\"*\", shape=rectangle, style=solid];\n", pipe);
        fputs("  two [label=\"2\", shape=rectangle, style=solid];\n", pipe);
        fputs("  x -> add;\n", pipe);
        fputs("  y -> add;\n", pipe);
        fputs("  add -> mul;\n", pipe);
        fputs("  two -> mul;\n", pipe);
        fputs("}\n", pipe);
        fflush(pipe);
        pclose(pipe);
    }
}