#include "stdio.h"
#include <string.h>
#include "server.h"

struct card dataa[5000];
int counter=0;


void main()
{
    int flag1,flag2,flag3,flag4,num,num2;
    long max_amount;
    while (1)
    {
    int choice;
    printf("\n                                            *********Welcome*********\n");
    printf("for new account enter 1\nfor viewing an account enter 2\nfor transaction enter 3\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        Get_card_holder_name(&dataa[counter]);
        Get_card_expiration_date(&dataa[counter]);
        Get_card_PAN(&dataa[counter]);
        printf("enter the amount of money this account has\n");
        scanf("%ld",&dataa[counter].amount);
        counter++;

    }
    if(choice==2)
    {
        char P1[20];

        printf("enter the user PAN\n");
        scanf("%s",&P1);
        int view=Get_all_card_data(P1,counter,&dataa);
        if(view>=0)
        {
            printf("the name of the user is     %s\n",dataa[view].name);
            printf("the expiring date of the user's card is     %s\n",dataa[view].date);
            printf("the user's card PAN is      %s\n",dataa[view].PAN);
            printf("the amount of money in this account is      %ld\n",dataa[view].amount);
            printf("the last transaction date is     %s\n",dataa[view].Last_trans_date);
            printf("the last transaction amount is      %ld\n",dataa[view].Last_trans_amount);
        }
        else
        {
            printf("wrong PAN please try again");
        }
    }
    if(choice==3)
    {
        struct card trans;
        Get_card_holder_name(&trans);
        Get_card_expiration_date(&trans);
        Get_card_PAN(&trans);
        num=Get_all_card_data(trans.PAN,counter,&dataa);
        if(num<0)
        {
            printf("wrong in filling the information");
            continue;
        }
        //trans=dataa[num];
        Get_transaction_date(&dataa[num]);
        flag1=Is_card_expired(dataa[num].Last_trans_date,dataa[num].date);
        if(flag1==0)
        {
            dataa[num].Last_trans_amount=Get_transaction_amount();
            max_amount=Set_max_amount();
            flag2=Is_below_max(max_amount,dataa[num].Last_trans_amount);
            if(flag2==0)
            {
                struct card trans2;
                Resieve_transaction_data(&trans2);
                num2=Get_all_card_data(trans2.PAN,counter,&dataa);
                if(num2<0)
                {
                    printf("wrong in filling the information");
                    continue;
                }
                //trans2=dataa[num2];

                    flag3=Is_amount_available(&dataa[num],&dataa[num2]);
                    if(flag3==1)
                    {
                        long amount=dataa[num].Last_trans_amount;
                        dataa[num].amount-=amount;
                        dataa[num2].amount+=amount;
                        dataa[num2].Last_trans_amount=dataa[num].Last_trans_amount;
                        /*char data_[20]=dataa[num].Last_trans_date;
                        for(int i=0;i<20;i++)
                        {
                            dataa[num2].Last_trans_date[i]=date_[i];
                        }*/
                    }
                    else
                    {
                        for(int i=0;i<20;i++)
                        {
                            dataa[num].Last_trans_date[i]=' ';
                        }
                        dataa[num].Last_trans_amount=0;
                    }

        }


    }

    }

}
}
