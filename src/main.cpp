#include <vector>
#include <Value.h>
#include <iostream>
int main()
{
    Value a(10);
    Value b(17);
    // // a.print();
    // // b.print();
    Value c = a + b;
    // c.print();
    // c.children();
    Value d(15);
    // // // d.print();
    Value e = c * d;
    e.print();
    e.children();
    // Value f = e + d;
    // f.print();
    // f.children();

    return 0;
}