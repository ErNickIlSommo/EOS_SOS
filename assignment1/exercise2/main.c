#include <stdint.h>

/* This is a function to print strings using UART */
extern void my_printf(const char *s); 

int main(void) {

    my_printf ("Hello World");
    return 0;
}

