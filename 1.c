//
//  main.c
//  co
//
//  Created by 王吉朗 on 2023/4/9.
//

// description: a = a - b
#include <stdio.h>
int main () {
    int a, b;
    FILE *input = fopen("../input/1.txt","r");
    fscanf(input, "%d %d", &a, &b);
    fclose(input);
    //a = a - b;
    asm volatile("sub %[A], %[A], %[B]\n\t"
                 :[A] "+r" (a)
                 :[B] "r" (b)
                 );
    printf("%d\n", a);
    return 0;
}
