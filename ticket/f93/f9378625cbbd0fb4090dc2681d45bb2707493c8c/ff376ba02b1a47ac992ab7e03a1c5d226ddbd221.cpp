#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <wchar.h>

void myPrintf(const wchar_t *fmt, ...) {
    size_t maxlen = 64;
    wchar_t *wcs = new wchar_t[maxlen];
    va_list ap;
    va_start(ap, fmt);
    int a = vswprintf(wcs, maxlen, fmt, ap);
    if (a >= 0) {
        wprintf(L"Success: %ls\n", wcs);
    } else {
        fprintf(stderr, "vswprintf() returned %d. errno: %d\n", a, errno);
    }
    va_end(ap);
    delete[] wcs;
}


int main(void) {
    int i;
    for (i = 0x177e; i < 0x178f; ++i) {
        myPrintf(L"test: %d: \"%c\"", i, i);
    }
    return 0;
}

