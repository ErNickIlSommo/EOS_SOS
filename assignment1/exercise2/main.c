#include <stdint.h>
/*
The program must have the following specifications:

* It contains only the main function that defines an array of integers v of 10 integers 
* Two integer variables min and max
* An inline assembly block that computes the min and max of the array and store the values into min and max
* The result must be printed using the provided  my_printf function

 // min = v[0];
    // max = v[0];
    // for(uint8_t i = 0; i < 10; i++) {
    //     if (min > v[i])
    //         min = v[i];
    //     if(max < v[i])
    //         max = v[i];
    // }

*/

/* This is a function to print strings using UART */
extern void my_printf(const char *s); 
extern void intToStr(int num, char *str);

int main(void) {

    int32_t v[] = {3, 5, 6, 3, 1, 100, 4, -4, 9, 10};
    int32_t min, max;

   

    asm(
        "ldr r2, [%[v]] \n"             // r2 = v[0]
        "mov %[min], r2 \n"             // min = v[0]
        "mov %[max], r2 \n"             // max = v[0]
        
        "mov r3, #0 \n"                 // i = 0
        "_loop: \n"
            // loop control
        "   cmp r3, #10 \n"             // if i > 10 {exit}
        "   bge _end \n"
            // load i-item of the array in r4
        "   ldr r4, [%[v], r3] \n"      // r4 = v[i]
            // control for min
        "   cmp %[min], r4 \n"          // if min > v[i] { min = v[i] }
        "   movgt %[min], r4 \n"
            // control for max
        "   cmp %[max], r4 \n"          // if max < v[i] {max = v[i] }
        "   movlt %[max], r4 \n"               
            // increment i and restart loop
        "   add r3, r3, #1 \n"          // i++
        "   b _loop \n"
        "_end: \n"
        "   b _end \n"
        : [min] "=r" (min), [max] "=r" (max)
        : [v] "r" (v)
        : "r2", "r3", "r4"
    );

    char message[100];
    intToStr(min, message);
    my_printf(message);

    intToStr(max, message);
    my_printf(message);
    return 0;
}

// Bro's solution
/*

int main(void) {

    int integers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int min = 11;
    int max = -1;

    int i = 0;
    int current;
    asm volatile (
        "1:\n"
        "ldr %3, [%4, %2, LSL #2]\n"
        "cmp %3, %0\n"
        "ble no_update_max\n"
        "mov %0, %3\n"
        "no_update_max:\n"
        "cmp %3, %1\n"
        "bge no_update_min\n"
        "mov %1, %3\n"
        "no_update_min:\n"
        "add %2, %2, #1\n"
        "cmp %2, #10\n"
        "blt 1b\n"
        : "=&r" (max), "=&r" (min), "=&r" (i), "=&r" (current)
        : "r" (integers), "0" (max), "1" (min), "2" (i)
    );

    char buffer[10];

    intToStr(min, buffer);
    my_printf("Minimum is: ");
    my_printf(buffer);

    my_printf("\n");

    intToStr(max, buffer);
    my_printf("Maximum is: ");
    my_printf(buffer);
    return 0;
}

*/

