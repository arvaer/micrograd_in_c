#include <vector>
#include <Value.h>
#include <Graph.h>
#include <iostream>
#include <stdlib.h>
using namespace ::std;

int main()
{
    Value a(17);
    Value b(10);
    Value c = a + b;
    Value d(16);
    Value e(17);
    Value f = c + d;
    Value h = f + e;
    Graph g(&h);
    g.visualize();
    return 0;
}
