#include "fcgi_stdio.h"
#include <stdio.h>

int main( ) {
    while(FCGI_Accept() >= 0)
        printf("Content-type: text/html\r\n\r\nHello World!");
    return 0;
}