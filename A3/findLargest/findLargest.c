#include "stdio.h"

int findLargest(int arr[], int n);

void main()
{
int n;
printf("enter the array size ");
 fflush(stdin);fflush(stdout);
scanf("%d",&n);
int arr[n];
for(int i=0;i<n;i++)
{
printf("arr[%d] =",i);
fflush(stdin);fflush(stdout);
scanf("%d",&arr[i]);
}
printf("the largest number in the array = %d",findLargest(arr,n));
}

int findLargest(int arr[], int n)
{
  int max=arr[0];
  for(int i=0;i<n;i++)
  {
      if(arr[i]>max)
      max=arr[i];
  }
  return max;
}
