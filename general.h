#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct Customer
{
  char firstName[30], lastName[30];
  char phone[12];
  float acctBalance;
  long int acctNumber;
  char Password[20];
};

int createAcct();
int genAcctNumber();
int homeScreen(void);
int loginMenu();
bool loginAcct(long acctNumber, char *password);
char contCycle();
void acctStatement(long acctNumber);
int deposit(long acctNumber);
bool transfer(long acctNumber);
int reMove(long acctNumber);

#endif
