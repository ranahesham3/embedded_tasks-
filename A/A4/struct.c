#include "stdio.h"

enum Category
{
FOOD,DRINK,TOILETRIES,CLOTHING
};

union ProductInfo
{
float floatValue;
int intValue;
};


struct Product
{
char arr[50];
float price;
int stock;
enum Category category;
union ProductInfo info;
};

void print (struct Product x);


void main()
{
  struct Product x[3]=
  {{"cake",200.5,50,FOOD,105.5},
  {"pepsi",8.0,150,DRINK,330},
  {"tshirt",250.0,23,CLOTHING,55}};
  for(int i=0;i<3;i++)
  {
      print(x[i]);
  }

}
void print (struct Product x)
{
printf("Product Name: <%s>, Category: <%d>, Price: <%f>, Stock: <%d>,  Additional Info:<%f>\n "
       ,x.arr,x.category,x.price,x.stock,x.info.floatValue);

}
