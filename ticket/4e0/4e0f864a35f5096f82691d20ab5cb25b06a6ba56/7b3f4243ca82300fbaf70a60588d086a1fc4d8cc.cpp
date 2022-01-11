#include "mytrackable.h"
#include "foo.h" // MyTrackableClass is complete type at this point
#include <iostream>

void Foo::sayHello()
{
    if (ref) {
        std::cout << "Hello, " << ref->message << " " << a << std::endl;
    } else {
        std::cout << "Hello world! " << a << std::endl;
    }
}

