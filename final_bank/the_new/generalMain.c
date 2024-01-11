#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "general.h"

int main()
{
  struct cstmrInfo cstmrInfo1;

  int userChoice;
  int numberOfTrial = 0;
  int createStatus;
  int loginStatus;

  while (numberOfTrial < 3)
  {
    userChoice = homeScreen();
    if (userChoice == 1)
    {
      createAcct();
      numberOfTrial = 0;
    }
    if (userChoice == 2)
    {
      loginStatus = loginAcct();
      if (loginStatus == 1)
      {
        break;
      }
      else
      {
        numberOfTrial = 0;
      }
    }
    if (userChoice != 1 && userChoice != 2)
    {
      numberOfTrial++;
      printf("Invalid option. Select a valid option.\nYou have %d trials remaining", 3 - numberOfTrial);
    }
  }

  if (loginStatus != 1)
  {
    printf("Thank you for banking with us");
    return 1000;
  }

  userChoice = loginMenu();
  while (userChoice != 5)
  {
    switch (userChoice)
    {
    case 1:
      transfer_money();

    case 2:;

    case 3:
      acctStatement();

    case 4:;

    case 5:
      break;

    default:
      printf("Invalid option. Choose a valid option");
    }
  }
  if (userChoice == 5)
  {
    printf("LOG OUT SUCCESSFUL. See you next time!");
  }
}