#include "Value.h"
int main()
{
    Value a(10);
    Value b(17);
    Value c = a + b;

    c.print();
    return 0;
}