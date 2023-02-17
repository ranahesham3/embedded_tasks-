#include<stdio.h>
int main(void)
{int arr [5]={1,2,3,4,5};
int sum=0;
for(int i=0;i<5;i++)
{
    printf("arr[%d]= %d \n",i,arr[i]);
    sum+=arr[i];
}
printf("the sum =%d\n",sum);
printf("the average =%f\n",(float)sum/5);
}
