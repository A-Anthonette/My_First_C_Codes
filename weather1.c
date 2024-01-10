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
  int index;
};

int createAcct(struct cstmrInfo *cstmrInfo, int index, long int *generatedAcctNumber);
long int genAcctNumber();
int homeScreen(void);
int loginMenu();
int loginAcct();
void acctStatement(struct cstmrInfo *cstmrInfo, int index);
int deposit(struct cstmrInfo *cstmrInfo);
bool transfer(struct cstmrInfo *cstmrInfo, struct cstmrInfo *cstmrInfo1);
int reMove();

long int genAcctNumber()
{
  srand(time(NULL));
  int recurringDigits = 21;
  long int randEightDigitNum = 0;

  for (int i = 0; i < 8; i++)
  {
    randEightDigitNum = (randEightDigitNum * 10) + (rand() % 10);
  }

  long int generatedAcctNumber = (long int)(recurringDigits * (pow(10, 8))) + randEightDigitNum;

  return labs(generatedAcctNumber);
}

int createAcct(struct cstmrInfo *cstmrInfo, int index, long int *generatedAcctNumber)
{
  // struct cstmrInfo cstmrInfo1;

  char userFileName[30];

  printf("To create your account, enter the following details\n\n");

  printf("Enter your first name:\n");
  scanf("%s", cstmrInfo[index].firstName);

  printf("Enter your last name:\n");
  scanf("%s", cstmrInfo[index].lastName);

  printf("Enter your phone number:\n");
  scanf("%s", cstmrInfo[index].phone);

  printf("Enter your password (at least 8 characters):\n");
  scanf("%s", cstmrInfo[index].Password);

  cstmrInfo[index].acctNumber = *generatedAcctNumber;
  cstmrInfo[index].acctBalance = 0;
  // Concatenate, open, and save user's general info (struct cstmrInfo)
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", cstmrInfo[0].acctNumber);

  FILE *pCstmrInfo;
  pCstmrInfo = fopen(userFileName, "wb");
  if (pCstmrInfo != NULL)
  {
    fwrite(&cstmrInfo[index], sizeof(cstmrInfo), 1, pCstmrInfo);
    // *acctNumber = cstmrInfo1.acctNumber;
    // *createStatus = 1;
    fclose(pCstmrInfo);
    return 1;
  }
  else
  {
    printf("Failed to open %s. Account registration failed. Try again.\n", userFileName);
    return 0;
  }
}

int homeScreen(void)
{
  int opt;
  printf("This is the New Bank.\n\nWhat would you want to do?\n\n");
  printf("1. Create an account\n\n2. Login to an existing account\n\n");
  printf("Choose an option: ");
  scanf("%d", &opt);
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

int loginAcct(struct cstmrInfo *cstmrInfo, int index)
{
  long int acctNumber;
  char password[20];

  // printf("Enter your account number: ");
  // scanf("%ld", &acctNumber);
  // printf("Enter your password: ");
  // scanf("%s", password);

  char userFileName[30];
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);

  FILE *pCstmrInfo;
  pCstmrInfo = fopen(userFileName, "rb");
  if (pCstmrInfo != NULL && strcmp(password, cstmrInfo[index].Password) == 0)
  {
    fread(&cstmrInfo[index], sizeof(cstmrInfo), 1, pCstmrInfo);
    fclose(pCstmrInfo);
    return 1;
  }
  else
  {
    printf("\nAccount not registered. Proceed to create an account or Password mismatch! Try again.\n");
    fclose(pCstmrInfo);
    return 0;
  }
}

void acctStatement(struct cstmrInfo *cstmrInfo, int index)
{
  printf("Your account balance is %.2f\n\n", cstmrInfo[index].acctBalance);
}

int deposit(struct cstmrInfo *cstmrInfo1)
{
  float amount;
  FILE *pCstmrInfo;

  printf("Enter the amount you want to deposit: ");
  scanf("%f", &amount);

  char userFileName[30];
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", cstmrInfo1->acctNumber);

  pCstmrInfo = fopen(userFileName, "rb+");
  if (pCstmrInfo != NULL)
  {
    fread(cstmrInfo1, sizeof(struct cstmrInfo), 1, pCstmrInfo);
    long offset = ftell(pCstmrInfo) - sizeof(float);
    cstmrInfo1->acctBalance += amount;
    fseek(pCstmrInfo, offset, SEEK_SET);
    fwrite(&cstmrInfo1->acctBalance, sizeof(float), 1, pCstmrInfo);
    fclose(pCstmrInfo);
    return 1;
  }
  else
  {
    printf("Processing error: Unable to retrieve account information. Try again.\n");
    return 0;
  }
}

bool transfer(struct Customer *cstmrInfo, struct Customer *cstmrInfo1)
{
  long int senderAcctNumber, receiverAcctNumber;
  float amount;

  printf("Enter your account number: ");
  scanf("%ld", &senderAcctNumber);
  printf("Enter the account number to transfer to: ");
  scanf("%ld", &receiverAcctNumber);
  printf("Enter the amount to transfer: ");
  scanf("%f", &amount);

  // Load sender's data
  char senderFileName[30];
  snprintf(senderFileName, sizeof(senderFileName), "%ld.bin", senderAcctNumber);
  FILE *pSenderFile = fopen(senderFileName, "rb+");
  if (pSenderFile != NULL)
  {
    fread(cstmrInfo, sizeof(struct Customer), 1, pSenderFile);
    if (cstmrInfo->acctBalance >= amount)
    {
      cstmrInfo->acctBalance -= amount;
      long offset = ftell(pSenderFile) - sizeof(float);
      fseek(pSenderFile, offset, SEEK_SET);
      fwrite(&cstmrInfo->acctBalance, sizeof(float), 1, pSenderFile);
      fclose(pSenderFile);
    }
    else
    {
      fclose(pSenderFile);
      printf("\nTransfer error: Insufficient balance.\n");
      return false;
    }
  }
  else
  {
    printf("\nTransfer error: Sender's account not found.\n");
    return false;
  }

  // Load receiver's data
  char receiverFileName[30];
  snprintf(receiverFileName, sizeof(receiverFileName), "%ld.bin", receiverAcctNumber);
  FILE *pReceiverFile = fopen(receiverFileName, "rb+");
  if (pReceiverFile != NULL)
  {
    fread(cstmrInfo1, sizeof(struct Customer), 1, pReceiverFile);
    cstmrInfo1->acctBalance += amount;
    long offset = ftell(pReceiverFile) - sizeof(float);
    fseek(pReceiverFile, offset, SEEK_SET);
    fwrite(&cstmrInfo1->acctBalance, sizeof(float), 1, pReceiverFile);
    fclose(pReceiverFile);
    printf("\nTransfer successful.\n");
    return true;
  }
  else
  {
    printf("\nTransfer error: Receiver's account not found.\n");
    return false;
  }
}

int reMove()
{
  long int acctNumber;

  printf("Enter your account number: ");
  scanf("%ld", &acctNumber);

  char userFileName[30];
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);

  int status = remove(userFileName);

  if (status == 0)
  {
    printf("Account deleted successfully.\n");
  }
  else
  {
    printf("Account not found. Delete operation failed.\n");
  }

  return 0;
}

int main(void)
{
  int input;
  long int acctNumber;
  int menuOption;
  struct cstmrInfo cstmrInfo; // Create a single struct to hold customer information

  while (1)
  {
    input = homeScreen();

    if (input == 1)
    {
      acctNumber = genAcctNumber();
      int createStatus = createAcct(&cstmrInfo, acctNumber);
      if (createStatus == 1)
      {
        printf("Account created successfully!\n");
      }
    }
    else if (input == 2)
    {
      printf("Enter your account number: ");
      scanf("%ld", &acctNumber);
      int loginStatus = loginAcct(&cstmrInfo, acctNumber);

      if (loginStatus == 1)
      {
        while (1)
        {
          menuOption = loginMenu();

          if (menuOption == 1)
          {
            if (deposit(&cstmrInfo))
            {
              printf("Your account has been credited successfully!\n");
              acctStatement(&cstmrInfo);
            }
            else
            {
              printf("Failed to complete the transaction\n");
            }
          }
          else if (menuOption == 2)
          {
            if (transfer(&cstmrInfo, &cstmrInfo1))
            {
              printf("Transaction complete.\n");
              acctStatement(&cstmrInfo);
            }
            else
            {
              printf("Transaction incomplete.\n");
            }
          }
          else if (menuOption == 3)
          {
            acctStatement(&cstmrInfo);
          }
          else if (menuOption == 4)
          {
            reMove(&cstmrInfo);
            break;
          }
          else if (menuOption == 5)
          {
            break;
          }
          else
          {
            printf("Invalid option.\n");
          }
        }
      }
    }
    else
    {
      printf("Invalid option\n");
    }
  }

  return 0;
}

// int main(void)
// {
//   int input;
//   long int acctNumber;
//   int loginStatus, createStatus;
//   int menuOption;
//   printf("Welcome to the New Bank. We keep your money in a way that's new.\n\n");

//   while (1)
//   {
//     // Initialize createStatus to 0 to signify account not yet created
//     createStatus = 0;

//     input = homeScreen();

//     // Create an account
//     if (input == 1)
//     {
//       acctNumber = genAcctNumber();
//       createStatus = createAcct(&createStatus, 1, &generatedAcctNumber);
//       if (createStatus == 1)
//       {
//         printf("Account created successfully!\n\n");
//       }
//     }
//     // Login
//     else if (input == 2)
//     {
//       loginStatus = loginAcct(&cstmrInfo, 1);
//       if (loginStatus == 1)
//       {
//         struct cstmrInfo cstmrInfo;
//         // Load user's information for later use
//         char userFileName[30];
//         snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);

//         FILE *pCstmrInfo;
//         pCstmrInfo = fopen(userFileName, "rb");
//         if (pCstmrInfo != NULL)
//         {
//           fread(&cstmrInfo, sizeof(struct cstmrInfo), 1, pCstmrInfo);
//           fclose(pCstmrInfo);
//         }

//         // Entering into the user's main banking interface
//         while (1)
//         {
//           menuOption = loginMenu();
//           // Credit account
//           if (menuOption == 1)
//           {
//             if (deposit(&cstmrInfo, 1))
//             {
//               printf("Your account has been credited successfully!\n\n");
//               acctStatement(&cstmrInfo, 1);
//             }
//             else
//             {
//               printf("Failed to complete the transaction\n");
//             }
//           }
//           // Make a transfer
//           else if (menuOption == 2)
//           {
//             if (transfer(&cstmrInfo, &cstmrInfo1))
//             {
//               printf("Transaction complete.\n");
//               acctStatement(&cstmrInfo, 1);
//             }
//             else
//             {
//               printf("Transaction incomplete.\n");
//             }
//           }
//           // Check balance
//           else if (menuOption == 3)
//           {
//             acctStatement(&cstmrInfo, 1);
//           }
//           // Delete account
//           else if (menuOption == 4)
//           {
//             reMove(&cstmrInfo);
//             createStatus = 0;
//             break;
//           }
//           // Log out
//           else if (menuOption == 5)
//           {
//             break;
//           }
//           else
//           {
//             printf("Invalid option.\n");
//           }
//         }
//       }
//     }
//     // Invalid option
//     else
//     {
//       printf("Invalid option\n");
//     }
//   }

//   return 0;
// }

