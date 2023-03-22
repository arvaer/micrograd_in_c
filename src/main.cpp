#include <vector>
#include <Value.h>
#include <Graph.h>
#include <iostream>
#include <stdlib.h>
using namespace ::std;

int main()
{
    Value<double> x1(2.00);
    Value<double> x2(0.0);
    Value<double> w1(-3.0);
    Value<double> w2(1.0);
    Value<double> b(6.7);
    Value<double> x1w1 = x1 * w1;
    Value<double> x2w2 = x2 * w2;
    Value<double> x1w1x2w2 = x1w1 + x2w2;
    // Graph<double> x(&x1w1x2w2);
    // x.visualize();
    Value<double> n = x1w1x2w2 + b;
    Value<double> o = n.tanh();
    Graph<double> g(&o);
    g.visualize();
    return 0;
}
