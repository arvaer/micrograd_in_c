#include "Value.h"
#include <iostream>
int main()
{
    Value a(10);
    Value b(17);
    a.print();
    b.print();
    Value c = a + b;
    c.print();
    Value d(15);
    d.print();
    Value e = c * d + a;
    e.print();
    e.children();
    return 0;
}