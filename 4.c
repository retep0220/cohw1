//
//  main.c
//  co4
//
//  Created by 王吉朗 on 2023/4/16.
//

// description: matrix muliply without for loop
#include<stdio.h>


int main() {
  int i=0;
  int h[9]={0}, x[3]={0}, y[3]={0};
  FILE *input = fopen("../input/4.txt","r");
  for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
  for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
  for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
  fclose(input);
  int *p_x = &x[0] ;
  int *p_h = &h[0] ;
  int *p_y = &y[0] ;
  asm volatile(
  	"li x9, 0\n\t" //x9 f
  	"li x18, 8\n\t"
  	"li x30, 3\n\t"
  	"li x19, 0\n\t" //x19 i
  	"li x7, 4\n\t"
  	"li x20, 2\n\t"
  	"Loop:\n\t"
  	"li x5, 0\n\t"
        "mul x5, x19, x30\n\t"
        "add x5, x5, x9\n\t" //x5 h location
        "mul x5, x5, x7\n\t" //x5 h offset
        "add x5, x5, %[h]\n\t" //x5 h address
        "lw x6, 0(x5)\n\t" //x6 h value
        "li x5, 0\n\t" //cler x5
        "mul x5, x9, x7\n\t" //x5 x offset
        "add x5, x5, %[x]\n\t" //x5 x address
        "lw x28, 0(x5)\n\t" //x28 x value
        "li x5, 0\n\t" //cler x5
        "mul x5, x19, x7\n\t" //x5 y offset
        "add x5, x5, %[y]\n\t" //x5 y address
        "lw x29, 0(x5)\n\t" //x29 y value
        "mul x31, x6, x28\n\t"
        "add x29, x29, x31\n\t"
        "sw x29, 0(x5)\n\t"
        "beq x9, x20, iLoop\n\t"
        "addi x9, x9, 1\n\t"
        "beq x0, x0, Loop\n\t"
	"iLoop:\n\t"
	"li x9, 0\n\t"
  	"beq x19, x20, Exit\n\t"
  	"addi x19, x19, 1\n\t"
        "beq x0, x0, Loop\n\t"
        "Exit:\n\t"
  	
        
                     :
                     :[h] "r"(p_h), [x] "r"(p_x), [y] "r"(p_y)
                     :"x5","x6","x7","x9","x18","x19","x20","x28","x29","x30","x31"
                     );
  p_y = &y[0];
  for(i = 0; i<3; i++)
    printf("%d \n", *p_y++);
  return(0)  ;
}
