#include "stdio.h"
#include <string.h>

struct record
{
 char name[30];
 int roll_num ;
 int math_mark;
 int phys_mark;
 int chem_mark;
}record;

/*
void add(struct record student);
void modify(struct record student);
void delete_it(struct record student);
void display (struct record student);
*/


void main (){
struct record student[100]={};

/*the roll number-->
for student[0] -->roll_num=1 and soo*/

int choice=0;
while(choice!=6){
printf("enter 1 if you want to add \n enter 2 if you want to modify\n");
printf("enter 3 if you want to delete \n enter 4 if you want to display\n");
printf("enter 5 if you want to search \n enter 6 if you want to exit\n");

scanf("%d",&choice);

if(choice==1)
{
    int i=0;
    while(student[i].roll_num!=0)
    {
       i++;
    }
    printf("enter the student's name \n ");
    fflush(stdin);fflush(stdout);
    gets(student[i].name);
    printf("enter the student's roll number\n");
    fflush(stdin);fflush(stdout);
    scanf("%d",&student[i].roll_num);
    printf("enter the student's marks\n");
    fflush(stdin);fflush(stdout);
    scanf("%d%d%d",&student[i].math_mark,&student[i].phys_mark,&student[i].chem_mark);
}
else if(choice==2)
{
    int x;
    printf("enter the roll number \n");
    scanf("%d",&x);

    int i,j;
    printf("if you want to modify name enter 1,roll number enter 2,marks enter 3 \n");
    scanf("%d",&i);

    if(i==1)
        gets(student[x-1].name);
    else if(i==2)
        scanf("%d",&student[x-1].roll_num);
    else if(i==3)
        {printf("if you want math enter 1,physics enter 2,chemistry enter 3\n");
        scanf("%d",&j);
        if(j==1)
            scanf("%d",&student[x-1].math_mark);
        else if(j==2)
            scanf("%d",&student[x-1].phys_mark);
        else if(j==3)
            scanf("%d",&student[x-1].chem_mark);
        else
            printf("try again");
        }
    else
        printf("try again");
}
else if(choice==3)
{
    int x;
    printf("enter the roll number \n");
    scanf("%d",&x);
    for(int i=0;i<30;i++)
        student[x-1].name[i]=0;
    student[x-1].roll_num=0;
    student[x-1].math_mark=0;
    student[x-1].phys_mark=0;
    student[x-1].chem_mark=0;
}
else if(choice==4)
{
    int n=0;
    while(student[n].roll_num!=0)
    {
       n++;
    }
    for(int i=0;i<n;i++)
    {
        printf("Student name: %s ,Student roll_number  %d \n Math marks: %d ,Physics marks: %d ,Chemistry marks: %d \n"
           ,student[i].name,student[i].roll_num,student[i].math_mark
           ,student[i].phys_mark,student[i].chem_mark);
    }
}
else if(choice==5)
{
    int x;
    printf("enter the roll number \n");
    scanf("%d",&x);
    printf("Student name: %s ,Student roll_number  %d \n Math marks: %d ,Physics marks: %d ,Chemistry marks: %d \n"
           ,student[x-1].name,student[x-1].roll_num,student[x-1].math_mark
           ,student[x-1].phys_mark,student[x-1].chem_mark);
}
else if(choice==6)
    break;
else
    printf("WRONG NUMBER \n  try again");
}
}




/*
void display (struct record student)
{
    printf("Student name: %s ,Student roll_number  %d \n Math marks: %d ,Physics marks: %d ,Chemistry marks: %d \n"
           ,student.name,student.roll_num,student.math_mark
           ,student.phys_mark,student.chem_mark);
}


void add (struct record student)
{
printf("enter the student's name \n ");
fflush(stdin);fflush(stdout);
scanf("%s",student.name);
printf("enter the student's roll number\n");
fflush(stdin);fflush(stdout);
scanf("%d",&student.roll_num);
printf("enter the student's marks\n");
fflush(stdin);fflush(stdout);
scanf("%d%d%d",&student.math_mark,&student.phys_mark,&student.chem_mark);
}


void modify(struct record student)
{
int i,j;
printf("if you want to modify name enter 1,roll number enter 2,marks enter 3 \n");
scanf("%d",&i);
if(i==1)
    gets(student.name);
else if(i==2)
    scanf("%d",&student.roll_num);
else if(i==3)
    {printf("if you want math enter 1,physics enter 2,chemistry enter 3\n");
    scanf("%d",&j);
    if(j==1)
        scanf("%d",&student.math_mark);
    else if(j==2)
        scanf("%d",&student.phys_mark);
    else if(j==3)
        scanf("%d",&student.chem_mark);
    else
       printf("try again");
    }
else
   printf("try again");
}


void delete_it(struct record student)
{
for(int i=0;i<30;i++)
    student.name[i]=0;
student.roll_num=0;
student.math_mark=0;
student.phys_mark=0;
student.chem_mark=0;
}


*/
