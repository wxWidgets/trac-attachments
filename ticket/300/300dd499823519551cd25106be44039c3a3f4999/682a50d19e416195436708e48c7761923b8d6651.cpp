#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

// Build minimal.cpp:
// g++ minimal_mex.cpp -shared -Wl,-rpath,$(pwd) -o ./libminimal.so `wx-config --cxxflags --libs`

// Build main.cpp
// g++ -L$(pwd) main.cpp -o main -ldl


void check_error( void *handle )
{
    char* error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "%s\n", error);
        if( handle )
        {
            dlclose( handle );
        }
        exit(EXIT_FAILURE);
    }
    
}

int main( int argc, const char* argv[] )
{
    int (*fcn)( int argc, const char* argv[] );

    for( int i = 0; i < 3; i++ )
    {
        void *handle = dlopen( "./libminimal.so", RTLD_NOW );

        check_error( handle );

        if( handle )
        {
            *(void**)(&fcn) = dlsym( handle, "main" );
            check_error( handle );
            (*fcn)( argc, argv );
            dlclose( handle );
        }
    }
    exit(EXIT_SUCCESS);
}