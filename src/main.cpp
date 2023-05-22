#include <vector>
#include <Value.h>
#include <Graph.h>
#include <iostream>
#include <stdlib.h>
using namespace ::std;

int main()
{
    Value<double> x1(18.00);
    Value<double> x2(4.0);
    Value<double> w1(-9.0);
    Value<double> w2(3.0);
    Value<double> b(15);
    Value<double> x1w1 = x1 * w1;
    Value<double> x2w2 = x2 * w2;
    Value<double> x1w1x2w2 = x1w1 + x2w2;
    // Graph<double> x(&x1w1x2w2);
    // x.visualize();
    Value<double> n = x1w1x2w2 + b;
    Value<double> o = n.tanh(true);
    o._backward();
    // n._backward();
    // x1w1x2w2._backward();
    // x1w1._backward();
    Graph<double> g(&o);
    g.visualize();
    return 0;
}
