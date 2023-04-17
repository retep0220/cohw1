//
//  main.c
//  co3
//
//  Created by 王吉朗 on 2023/4/9.
//

#include<stdio.h>
int main() {
  int f,i=0;
  int h[9]={0}, x[3]={0}, y[3]={0};
  FILE *input = fopen("../input/3.txt","r");
  for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
  for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
  for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
  fclose(input);
  int *p_x = &x[0] ;
  int *p_h = &h[0] ;
  int *p_y = &y[0] ;
  for (i = 0 ; i < 3; i++)
    {
      p_x = &x[0]  ;
      for (f = 0 ; f < 3; f++)
        asm volatile(
        "li x30, 3\n\t"
        "mul x5, %[i], x30\n\t"
        "add x5, x5, %[f]\n\t" //x5 h location
        "li x7, 4\n\t"
        "mul x5, x5, x7\n\t" //x5 h offset
        "add x5, x5, %[h]\n\t" //x5 h address
        "lw x6, 0(x5)\n\t" //x6 h value
        "li x5, 0\n\t" //cler x5
        "mul x5, %[f], x7\n\t" //x5 x offset
        "add x5, x5, %[x]\n\t" //x5 x address
        "lw x28, 0(x5)\n\t" //x28 x value
        "li x5, 0\n\t" //cler x5
        "mul x5, %[i], x7\n\t" //x5 y offset
        "add x5, x5, %[y]\n\t" //x5 y address
        "lw x29, 0(x5)\n\t" //x29 y value
        "mul x31, x6, x28\n\t"
        "add x29, x29, x31\n\t"
        "sw x29, 0(x5)\n\t"
        
                     :
                     :[h] "r"(p_h), [x] "r"(p_x), [y] "r"(p_y), [i] "r" (i), [f] "r"(f)
                     :"x5","x6","x7","x28","x29","x30","x31"
                     );
                     
    }
  p_y = &y[0];
  for(i = 0; i<3; i++)
    printf("%d \n", *p_y++);
  return(0)  ;
}
