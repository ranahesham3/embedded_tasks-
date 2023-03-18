#include<stdio.h>
#include <string.h>
int main(void)
{
char arr1[50];
char arr2[50];
char arr3[100]={0};
printf("enter the first string :");
gets(arr1);
printf("enter the second string :");
gets(arr2);
strcat(arr3,arr1);
strcat(arr3,arr2);
printf("the final or the third string : %s",arr3);
}
