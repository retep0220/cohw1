//
//  main.c
//  co2
//
//  Created by 王吉朗 on 2023/4/9.
//

// description: cn = an - bn
#include <stdio.h>
int main () {
    int a[10] = {0}, b[10]= {0}, c[10] = {0};
    int i, arr_size = 10;
    FILE *input = fopen("../input/2.txt","r");
    for(i = 0; i<arr_size; i++) fscanf(input, "%d", &a[i]);
    for(i = 0; i<arr_size; i++) fscanf(input, "%d", &b[i]);
    for(i = 0; i<arr_size; i++) fscanf(input, "%d", &c[i]);
    fclose(input);
    int *p_a = &a[0];
    int *p_b = &b[0];
    int *p_c = &c[0];
    /* Original C code segment
    for (int i = 0; i < arr_size; i++){
        *p_c++ = *p_a++ - *p_b++;
    }
*/
    for (int i = 0; i < arr_size; i++)
        asm volatile("lw x5, (%0)\n\t"
                        "lw x6, (%1)\n\t"
                        "sub x7, x5, x6\n\t"
                        "sw x7, (%2)\n\t"
                        "addi %0, %0, 4\n\t"
                        "addi %1, %1, 4\n\t"
                        "addi %2, %2, 4\n\t"
                        :"+r"(p_a), "+r"(p_b), "+r"(p_c)
                        :
                        : "x5", "x6", "x7"
                     
                     );
    p_c = &c[0];
    for (int i = 0; i < arr_size; i++)
        printf("%d ", *p_c++);
    return 0;
}
