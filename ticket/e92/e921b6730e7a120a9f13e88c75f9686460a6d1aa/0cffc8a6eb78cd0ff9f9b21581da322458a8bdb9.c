#include <stdlib.h>
#include <stdio.h>

void main()
{
    fprintf(stdout, "Message to stdout from program doing exit(-1): Permission Denied\n");
    fprintf(stderr, "Message to stderr from program doing exit(-1): Permission Denied\n");
    exit(-1);
}
