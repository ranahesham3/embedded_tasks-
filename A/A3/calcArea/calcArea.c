#include "stdio.h"
double calcArea (double n)
{
  return (n*n*3.14);
}

void main()
{
double n ,area;
printf("enter the radius of the circle =");
fflush(stdin);fflush(stdout);
scanf("%lf",&n);
area =calcArea(n);
printf("the area of the circle = %lf",area);
}
