#include "stdio.h"
#include <string.h>
#ifndef CARD_H_
#define CARD_H_


/*void Get_card_holder_name(struct card* c1);
void Get_card_expiration_date(struct card* c1);
void Get_card_PAN(struct card* c1);
*/

struct card
{
    char name[500];
    char date[20];
    char PAN[20];
    char Last_trans_date[20];
    long amount;
    long Last_trans_amount;

};


void Get_card_holder_name(struct card* c1)
{
  printf("print your card holder name\n");
  fflush(stdin);fflush(stdout);
  gets(c1->name);

}


void Get_card_expiration_date(struct card* c1)
{
  char date[20];
  printf("print your card holder date\n");
  fflush(stdin);fflush(stdout);
  gets(c1->date);
}


void Get_card_PAN(struct card* c1)
{
  char PAN[20];
  printf("print your card holder PAN\n");
  fflush(stdin);fflush(stdout);
  gets(c1->PAN);

}




#endif // CARD_H_
