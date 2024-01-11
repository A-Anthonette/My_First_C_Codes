#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

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

int createAcct()
{
  struct Customer customer1;
  printf("To create your account, enter the following details\n\n");

  printf("Enter your first name:\n");
  scanf("%s", customer1.firstName);

  printf("Enter your last name:\n");
  scanf("%s", customer1.lastName);

  printf("Enter your phone number:\n");
  scanf("%s", customer1.phone);

  printf("Enter your password (at least 8 characters):\n");
  scanf("%s", customer1.Password);

  // Code to generate account number
  srand(time(NULL));
  int recurringDigits = 21;

  int randEightDigitNum = 0;

  for (int i = 0; i < 8; i++)
  {
    randEightDigitNum = (randEightDigitNum * 10) + (rand() % 10);
  }

  long int generatedAcctNumber = (long int)(recurringDigits * (pow(10, 8))) + randEightDigitNum;

  customer1.acctNumber = labs(generatedAcctNumber);

  // Concatenate, open, and save users general info (struct cstmrInfo)
  char userFileName[30];
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", customer1.acctNumber);
  printf("Your account number is %ld\n", customer1.acctNumber);

  FILE *pCustomer = fopen(userFileName, "wb");

  if (pCustomer == NULL)
  {
    perror("Failed to open file");
    return 0;
  }
  else
  {
    customer1.acctBalance = 0;
    fwrite(&customer1, sizeof(customer1), 1, pCustomer);
    fclose(pCustomer);
    return 1;
  }
}

int homeScreen()
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

bool loginAcct(long acctNumber, char password[20])
{
  struct Customer customer1;

  char userFileName[20];
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);

  FILE *pCustomer;

  pCustomer = fopen(userFileName, "rb");
  if (pCustomer == NULL)
  {
    perror("\nAccount not registered. Proceed to create an account");
    return 0;
  }
  else
  {
    fread(&customer1, sizeof(struct Customer), 1, pCustomer);
    if (strcmp(password, customer1.Password) == 0)
    {
      fclose(pCustomer);
      printf("login successful\n");
      return 1;
    }
    else
    {
      printf("\nPassword mismatch! Try again.");
      return 0;
    }
  }
}
// fwrite(&customer1.acctBalance, sizeof(float), 1, pCustomer);
// fclose(pCustomer);
void acctStatement(long acctNumber)
{
  char userFileName[20];
  struct Customer customer1;
  FILE *pCustomer;
  snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);
  pCustomer = fopen(userFileName, "rb");
  if (pCustomer == NULL)
  {
    perror("Unable to open file");
  }
  else
  {
    fread(&customer1, sizeof(struct Customer), 1, pCustomer);
    printf("Your account balance is %f\n\n", customer1.acctBalance);
  }
}

int deposit(long acctNumber)
{
  struct Customer customer1;
  float amount;
  FILE *pCustomer;
  int structRead, structWritten;

  printf("Enter amount you want to deposit: ");
  scanf("%f", &amount);

  customer1.acctNumber = acctNumber;
  char userFileName[20];
  snprintf(userFileName, sizeof(userFileName), "%d.bin", customer1.acctNumber);

  pCustomer = fopen(userFileName, "rb");
  if (pCustomer == NULL)
  {
    perror("Unable to open file");
    return 0;
  }
  else
  {
    structRead = fread(&customer1, sizeof(struct Customer), 1, pCustomer);
    // long offset = ftell(pCstmrInfo) - sizeof(float);
    // fseek(pCustomer, offset, SEEK_SET);
    fclose(pCustomer);
  }
  if (structRead != 1)
  {
    perror("Error reading file");
  }
  customer1.acctBalance += amount;
  pCustomer = fopen(userFileName, "wb");
  if (pCustomer == NULL)
  {
    perror("Unable to open file");
  }
  else
  {
    structWritten = fwrite(&customer1, sizeof(struct Customer), 1, pCustomer);
    fclose(pCustomer);
    return 1;
  }
  if (structWritten != 1)
  {
    perror("Error writing to file");
    fclose(pCustomer);
    return 0;
  }
}

bool transfer(long acctNumber)
{
  int status;
  struct Customer customer[2];
  long int recipientAcctNumber;
  float amount;
  FILE *pCustomer1;
  FILE *pCustomer2;
  int structRead1, structWritten1, structRead2, structWritten2;

  printf("Enter amount to transfer: ");
  scanf("%f", &amount);

  char userFileName1[20], userFileName2[20];
  char password[20];

  // Concatenating the SENDER'S acctNumber to check if such file exists before updating the balance
  snprintf(userFileName1, sizeof(userFileName1), "%ld.bin", acctNumber);
  pCustomer1 = fopen(userFileName1, "rb");
  if (pCustomer1 == NULL)
  {
    perror("Error opening file");
  }
  else
  {
    structRead1 = fread(&customer[0], sizeof(struct Customer), 1, pCustomer1);
    fclose(pCustomer1);
  }
  if (structRead1 != 1)
  {
    perror("Error reading file");
  }

  printf("Enter your password to confirm transfer:");
  scanf(" %s", password);
  if (strcmp(password, customer[0].Password) == 0)
  {
    customer[0].acctBalance -= amount;
    printf("Your account balance is %f\n", customer[0].acctBalance);
  }
  pCustomer1 = fopen(userFileName1, "wb");
  if (pCustomer1 == NULL)
  {
    perror("Error opening file");
  }
  else
  {
    structWritten1 = fwrite(&customer[0], sizeof(struct Customer), 1, pCustomer1);
    fclose(pCustomer1);
  }
  if (structWritten1 != 1)
  {
    perror("Error writing back to file");
    status = 0;
  }
  else
  {
    printf("Account updated successfully\n");
    fclose(pCustomer1);
    status = 1;
  }

  printf("Enter account number to transfer: ");
  scanf("%ld", &recipientAcctNumber);
  snprintf(userFileName2, sizeof(userFileName2), "%ld.bin", recipientAcctNumber);

  pCustomer2 = fopen(userFileName2, "rb");
  if (pCustomer2 == NULL)
  {
    perror("Error opening file, or receiver's account not registered");
  }
  else
  {
    structRead2 = fread(&customer[1], sizeof(struct Customer), 1, pCustomer2);
    fclose(pCustomer2);
  }
  if (structRead2 != 1)
  {
    perror("Error reading recipient's file");
    status = 0;
  }
  customer[1].acctBalance += amount;
  printf("The sender's account balance is now %f", customer[1].acctBalance);
  pCustomer2 = fopen(userFileName2, "wb");
  // long offset = ftell(pCustomer1) - sizeof(float);
  structWritten2 = fwrite(&customer[1], sizeof(struct Customer), 1, pCustomer2);
  if (structWritten2 != 1)
  {
    perror("Error writing back to file");
    status = 0;
  }
  else
  {
    printf("Account updated successfully");
    fclose(pCustomer2);
    status = 1;
  }
  return status;
  // fseek(pCustomer1, offset, SEEK_SET);

  // // Concatenating the RECEIVER'S acctNumber to check if such file exists before updating the balance
  // snprintf(userFileName2, sizeof(userFileName2), "%ld.bin", acctNumber[1]);
  // pCustomer2 = fopen(userFileName2, "rb");
  // if (pCustomer2 == NULL)
  // {
  //   perror("Error opening file, or receiver's account not registered");
  // }
  // structRead2 = fread(&customer[1], sizeof(struct Customer), 1, pCustomer2);
  // fclose(pCustomer2);
  // if (structRead2 != 1)
  // {
  //   perror("Error reading recipient's file");
  //   return 0;
  // }
  // else
  // {
  //   printf("Account number %ld found.\nEnter your password to confirm transfer:", acctNumber[1]);
  //   scanf(" %s", password);
  // }

  // if (strcmp(password, customer[0].Password) == 0)
  // {
  //   customer[1].acctBalance += amount;
  // }
  // else
  // {
  //   perror("Password mismatch\n");
  //   return 0;
  // }
  // pCustomer2 = fopen(userFileName2, "wb");
  // structWritten2 = fwrite(&customer[1], sizeof(struct Customer), 1, pCustomer2);
  // if (structWritten2 != 1)
  // {
  //   perror("Error updating file");
  //   fclose(pCustomer2);
  //   return 0;
  // }
  // else
  // {
  //   printf("Account updated successfully");
  //   fclose(pCustomer2);
  //   return 1;
  // }
}

int reMove(long acctNumber)
{
  char choice;

  printf("Confirm that you want to delete your account.\n");
  printf("WARNING: All your records and residual balance will be erased.\n\n");
  printf("WARNING: No claims can be made to any funds if you wish to continue.\n");
  printf("Do you wish to continue [y/n]?: ");
  scanf(" %c", &choice);
  if (choice == 'y')
  {
    printf("Provide the account number: ");
    scanf("%ld", &acctNumber);

    char userFileName[20];
    snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);
    // call the remove Function within the main and input name of file
    remove(userFileName);
    if (remove(userFileName) == 0)
    {
      printf("Account successfully deleted.\n\n");
      // return 1;
    }
    else
    {
      printf("Failed to delete the account.\n\n");
      // return 0;
    }
  }
}

char contCycle()
{
  char choice;
  printf("\n\nDo you wish to continue [y/n]");
  scanf(" %c", &choice);
  return choice;
}

// !!!!!!!!!!!!!!!!!!!!!!THIS IS THE MAIN FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main()
{
  int userChoice;
  int numberOfTrial = 0;
  int createStatus;
  int loginStatus;
  float amount;
  int depositStatus;
  int transferStatus;
  int deleteStatus;
  int statementStatus;
  char acctToDelete[30];
  long int acctNumber;

  struct Customer customer1;
  FILE *pCustomer;

  int input;
  int menuOption;
  printf("Welcome to the New Bank. We keep your money in a way that's new.\n\n");

  while (1)
  {
    // Initialize createStatus to 0 to signify account not yet created
    createStatus = 0;

    input = homeScreen();

    // Create an account
    if (input == 1)
    {
      // acctNumber = genAcctNumber();
      createStatus = createAcct();
      if (createStatus == 1)
      {
        printf("Account created successfully!\n\n");
      }
    }
    // Login
    if (input == 2)
    {
      long int acctNumber;
      char password[20];
      printf("Enter your account number:\n");
      scanf(" %ld", &acctNumber);
      printf("Enter your password:\n");
      scanf(" %s", password);
      loginStatus = loginAcct(acctNumber, password);
      if (loginStatus == 1)
      {
        struct Customer customer1;
        // Load user's information for later use
        char userFileName[30];
        snprintf(userFileName, sizeof(userFileName), "%ld.bin", acctNumber);

        FILE *pCustomer;
        pCustomer = fopen(userFileName, "rb");
        if (pCustomer != NULL)
        {
          fread(&customer1, sizeof(struct Customer), 1, pCustomer);
          fclose(pCustomer);
        }

        // Entering into the user's main banking interface
        while (1)
        {
          printf("Select an option below\n\n");
          printf("1. Credit your account\n");
          printf("2. Make a transfer\n");
          printf("3. Check account balance\n");
          printf("4. Delete your account\n");
          printf("5. Log out\n\n");
          printf("Enter option: ");
          scanf("%d", &menuOption);
          // Credit account
          if (menuOption == 1)
          {
            depositStatus = deposit(acctNumber);
            if (depositStatus == 1)
            {
              printf("Your account has been credited successfully!\n\n");
              acctStatement(acctNumber);
            }
            else
            {
              printf("Failed to complete the transaction\n");
            }
          }
          // Make a transfer
          if (menuOption == 2)
          {
            transferStatus = transfer(acctNumber);
            if (transferStatus == 1)
            {
              printf("Transaction successful.\n");
              acctStatement(acctNumber);
            }
            else
            {
              printf("Transaction incomplete.\n");
            }
          }
          // Check balance
          if (menuOption == 3)
          {
            acctStatement(acctNumber);
          }
          // Delete account
          if (menuOption == 4)
          {
            reMove(acctNumber);
            createStatus = 0;
            break;
          }
          // Log out
          if (menuOption == 5)
          {
            printf("You have logged out successfully\n");
            break;
          }
          if (menuOption != 1 && menuOption != 2 && menuOption != 3 && menuOption != 4 && menuOption != 5)
          {
            printf("Invalid option. Choose a valid option");
          }
        }
      }
    }
    if (input != 1 && input != 2)
    {
      printf("Invalid option\n");
    }
  }
  return 0;
}