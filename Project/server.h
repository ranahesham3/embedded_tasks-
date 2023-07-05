#include "stdio.h"
#ifndef SERVER_H_
#define SERVER_H_

#include"terminal.h"



//flag2=false
 Resieve_transaction_data(struct card* c1)
{
    printf("enter your transaction data (the PAN of the other account)\n");
    fflush(stdin);fflush(stdout);
    gets(c1->PAN);

}


int Is_amount_available(struct card* c1,struct card * c2)
{
    int flag3=1;
    if((c1->Last_trans_amount) > (c1->amount))
        {
            printf("Declined insuffecient funds\n");
            flag3=0;
        }
    else
        {
            printf("                DONE                ");
        }
        return flag3;
}


#endif // SERVER_H_
