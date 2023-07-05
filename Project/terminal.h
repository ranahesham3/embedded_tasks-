#include "stdio.h"
#include <string.h>

#ifndef TERMINAL_H_
#define TERMINAL_H_
#include "card.h"


 int Get_all_card_data(char P1[20],int counter,struct card *dataa)
{
    int point =-1;
    for(int i=0;i<=counter;i++)
        {
            if(strcmp(P1,dataa[i].PAN)==0)
                point=i;
        }
    return point;
}


void Get_transaction_date(struct card *c1)
{
    printf("enter the transaction date\n");
    fflush(stdin);fflush(stdout);
    gets(c1->Last_trans_date);
}

int Is_card_expired(char trans_date1[],char trans_date2[])
{
    int flag1=0;
    for(int i=0;i<20;i++)
    {
        if(trans_date2[i]<trans_date1[i])
        {
            flag1 =1;
            printf("your card is expired\n");
            break;
        }
    }
    return flag1;
}

//if flag1==false


    long Get_transaction_amount()
    {
        long trans_amount;
        printf("enter the transaction amount\n");
        fflush(stdin);fflush(stdout);
        scanf("%ld",&trans_amount);
        return trans_amount;
    }


    long Set_max_amount()
    {
        long max_amount;
        printf("enter the max amount \n");
        fflush(stdin);fflush(stdout);
        scanf("%ld",&max_amount);
        return max_amount;
    }

    int Is_below_max(long long max_amount,long long trans_amount)
    {
        int flag2=1;
        if(max_amount<trans_amount)
        {
            printf("Declined amount exceeding limit\n");
        }
        else
        {
            flag2=0;
        }
        return flag2;

    }



#endif // TERMINAL_H_
