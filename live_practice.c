#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct cstmrInfo
{
  char firstName[30], lastName[30];
  char phone[12];
  float acctBalance;
  long int acctNumber;
  char Password[20];
};

// int createAcct();
// int genAcctNumber();
// int homeScreen(void);
// void loginMenu();
// int loginAcct();
// char contCycle();

// int main()
// {
//   struct cstmrInfo cstmrInfo1;
//   char choice;
//   int opt;
//   homeScreen();
//   scanf(" %d", &opt);

//   if (opt == 1)
//   {
//     createAcct();
//     contCycle();
//   }
//   else if (opt == 2)
//   {
//     loginAcct();
//   }
//   else
//   {
//     printf("\nChoose a valid option.");
//   }

//   printf("\n\nDo you wish to continue [y/n]");
//   scanf(" %c", &choice);
// }

//   printf("\n\nDo you wish to continue [y/n]");
//   scanf(" %c", &choice);

//   while (choice == 'y')
//   {
//     system("cls");
//     homeScreen();
//     scanf(" %d", &opt);

// }

// // Function to randomly generate account number
int genAcctNumber()
{
  srand(time(NULL));
  int recurringDigits = 21;

  int randEightDigitNum = 0;

  for (int i = 0; i < 8; i++)
  {
    randEightDigitNum = (randEightDigitNum * 10) + (rand() % 10);
  }

  long int generatedAcctNumber = (long int)(recurringDigits * (pow(10, 8))) + randEightDigitNum;

  return abs(generatedAcctNumber);
}

int createAcct()
{
  struct cstmrInfo cstmrInfo1;

  FILE *pCstmrInfo;

  char userFileName[30];

  printf("To create your account, enter the following details\n\n");

  printf("Enter your first name:\n");
  scanf("%s", cstmrInfo1.firstName);

  printf("Enter your last name:\n");
  scanf("%s", cstmrInfo1.lastName);

  printf("Enter your phone number:\n");
  scanf("%s", cstmrInfo1.phone);

  printf("Enter your password (at least 8 characters):\n");
  scanf("%s", cstmrInfo1.Password);

  // Code to generate account number
  srand(time(NULL));
  int recurringDigits = 21;

  int randEightDigitNum = 0;

  for (int i = 0; i < 8; i++)
  {
    randEightDigitNum = (randEightDigitNum * 10) + (rand() % 10);
  }

  long int generatedAcctNumber = (long int)(recurringDigits * (pow(10, 8))) + randEightDigitNum;

  cstmrInfo1.acctNumber = labs(generatedAcctNumber);
  // printf("Your account number is %ld\n", cstmrInfo1.acctNumber);

  // Concatenate, open, and save users general info (struct cstmrInfo)
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", cstmrInfo1.acctNumber);

  pCstmrInfo = fopen(userFileName, "wb");

  if (pCstmrInfo != NULL)
  {
    fwrite(&cstmrInfo1, sizeof(cstmrInfo1), 1, pCstmrInfo);
    system("cls");
    printf("CONGRATULATIONS!!!\nYou have successfully created an account with us.\n");
    printf("Your account number is %ld\n", cstmrInfo1.acctNumber);
    printf("\n\n\tRemember your account number and password for future transactions.\n\n");
    printf("\tThanks for banking with us. See you next time!");
    fclose(pCstmrInfo);
    return 1;
  }
  else
  {
    printf("Failed to open %s.\n Account registration failed.\nTry again.", userFileName);
    return 0;
  }
}

int homeScreen(void)
{
  int opt;
  printf("This is the New Bank.\n\nWhat would you want to do?\n\n");
  printf("1. Create account\n\n2. Login to existing account\n\n");
  printf("Choose an option:");
  scanf(" %d", &opt);
  return opt;
}

int loginMenu()
{
  int opt;
  printf("Select an option below\n\n");
  printf("1. Credit your account\n");
  printf("2. Make a transfer\n");
  printf("3. Check account balance\n");
  printf("4. Delete your account\n");
  printf("5. Log out\n\n");
  printf("Enter option: ");
  scanf("%d", &opt);
  return opt;
}

int loginAcct()
{
  struct cstmrInfo cstmrInfo1;
  long int acctNumber;
  char password[20];

  printf("Enter your account number:\n");
  scanf(" %ld", &acctNumber);
  printf("Enter your password:\n");
  scanf(" %s", password);

  char userFileName[20];
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);

  FILE *pCstmrInfo;

  pCstmrInfo = fopen(userFileName, "rb");
  if (pCstmrInfo != NULL)
  {
    fread(&cstmrInfo1, sizeof(cstmrInfo1), 1, pCstmrInfo);
    if (strcmp(password, cstmrInfo1.Password) == 0)
    {
      printf("Login successful. Welcome, %s\n", cstmrInfo1.firstName);
      // Do I need to close the file since the user will be interacting with it once logged in?
      return 1;
    }
    else
    {
      printf("\nPassword mismatch! Try again.");
      return 0;
    }
  }
  else
  {
    printf("\nAccount not registered. Proceed to create an account");
    return 0;
  }
}

char contCycle()
{
  char choice;
  printf("\n\nDo you wish to continue [y/n]");
  scanf(" %c", &choice);
  return choice;
}
// !!!!!!!!!!!!!!!!!!!!!!!THIS IS THE MAIN FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!
int main()
{
  /*int userChoice;
  int numberOfTrial = 0;
  int createStatus;
  int loginStatus;

  while (numberOfTrial < 3)
  {
    userChoice = homeScreen();
    if (userChoice == 1)
    {
      createAcct();      // Add code to save the return status of createAcct.
      numberOfTrial = 0; // If it's successful, add a break statement and recall the homescreen function
      // createStatus = createAcct();
      // if (createStatus == 1){
      // break;
      // homeScreen();
      // }
      // else {
      // numberOfTrial++;
      //}
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
        // numberOfTrial++;
        numberOfTrial = 0;
      }
    }
    if (userChoice != 1 && userChoice != 2)
    {
      numberOfTrial++;
      printf("Invalid option. Select a valid option.\nYou have %d trials remaining", 3 - numberOfTrial);
    }
  }

  if (loginStatus != 1) // Why not take this statement into the else statement in the loop?
  {
    printf("Thank you for banking with us");
    return 1000;
  }

  userChoice = loginMenu();
  while (userChoice != 5)
  {
    switch (userChoice)
    {
    case 1:;

    case 2:;

    case 3:;

    case 4:;

    case 5:
      printf("LOG OUT SUCCESSFUL. See you next time!");
      break;

    default:;
    }
  }*/
}