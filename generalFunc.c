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