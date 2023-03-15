#include <vector>
#include <Value.h>
#include <Graph.h>
#include <iostream>
#include <stdlib.h>
using namespace ::std;

int main()
{
    Value x1(2);
    Value x2(0);
    Value w1(-3);
    Value w2(1);
    Value b(6.7);
    Value x1w1 = x1 * w1;
    Value x2w2 = x2 * w2;
    Value x1w1x2w2 = x1w1 + x2w2;
    // Graph x(&x1w1x2w2);
    // x.visualize();
    Value n = x1w1x2w2 + b;
    Value o = n.tanh();
    Graph g(&o);
    g.visualize();
    return 0;
}
