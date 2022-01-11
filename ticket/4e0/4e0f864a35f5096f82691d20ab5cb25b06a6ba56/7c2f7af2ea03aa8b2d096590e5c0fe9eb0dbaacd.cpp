#include "foo.h" // MyTrackableClass is incomplete type at this point
#include "mytrackable.h"

int main()
{
    Foo foo;
    foo.a = 42;
    {
        MyTrackableClass t("kitty!");
        foo.ref = &t;
        foo.sayHello(); // expected output: "Hello, kitty! 42", actual output: "Hello, kitty! <a random number>"
    }
    foo.sayHello(); // expected output: "Hello world! 42", actual output: "Hello world! 0"
}

