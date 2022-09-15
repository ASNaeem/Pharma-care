#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>   //for CB

#define MAX 100

void menu();
void updateFile();
void addNew();
void loadAll();
void display();
int search(int Bool);
void delData();
void editData();
void addSupplier();
void displaySupplier();
int searchSupplier(int Bool);
void delSupplier();
void editSupplier();
void updatefileSup();
void AdminPanel();
void supplierPanel();
void login();
void loginInfoWrite();
void loginInfoRead();
void orderInfoWrite();
void orderInfoRead();
void addOrder();
void displayOrder();
void currentDate();
void currentTime();
void displayReceipt();
void loadReceipts();
void updateReceipts();
void addReceipt(int Bool);
void contactInfo();
void goBack();
void sales();
void Orders();
void Receipts();
void techTeam();
void systemClear() { system("cls"); } // cls for CB
void alignment(int k, int length);

const char *RB =
    "____________________________________________________________\n";
const char *UB =
    "____________________________________________________________\n";
const char *SB = "__________________________________________\n";
const char *L = {"|"};
const char *R = {"|\n"};

const char *MED_DATA_FORMAT_IN =
    "{\"MedID\": %d, \"Brand name\": \"%[^\"]\", \"Generic name\": \"%[^\"]\", "
    "\"Manufacturer\": \"%[^\"]\", \"Dosage form\": \"%[^\"]\", \"Strength\": "
    "\"%[^\"]\", \"Price/Pack\": %lf, \"Price/Unit\": %lf, \"In stock\": "
    "%d, "
    "\"Indications\": \"%[^\"]\"}\n";
const char *MED_DATA_FORMAT_OUT =
    "{\"MedID\": %d, \"Brand name\": \"%s\", \"Generic name\": \"%s\", "
    "\"Manufacturer\": "
    "\"%s\", \"Dosage form\": \"%s\", \"Strength\": \"%s\", \"Price/Pack\": "
    "%lf, \"Price/Unit\": %lf, \"In stock\": %d, \"Indications\": \"%s\"}\n";
const char *MED_DATA_FORMAT_CONSOLE = {
    "MedID: %d\nBrand name: %s\nGeneric name: %s\nManufacturer: %s\nDosage "
    "form: "
    "%s\nStrength: %s\nPrice/Pack: %.2lf\nPrice/Unit: %.2lf\nIn stock: "
    "%d\nIndications: %s\n\n"};
const char *SUP_DATA_FORMAT_OUT = "{\"Suppiler ID\": %d, \"Company Name\": "
                                  "\"%s\", \"Dealer's Name\": \"%s\", \"Phone "
                                  "Number\":\"%s\", \"Email\": \"%s\"}\n";
const char *SUP_DATA_FORMAT_IN =
    "{\"Suppiler ID\": %d, \"Company Name\": \"%[^\"]\", \"Dealer's Name\": "
    "\"%[^\"]\", \"Phone Number\": \"%[^\"]\", \"Email\": \"%[^\"]\"}\n";

typedef struct supplier {
  int supID;
  char comName[100];
  char salesMan[30];
  char phnNum[20];
  char email[50];
} supplier;

supplier sup[MAX];
int sTop = -1;
int foundIndex = -1;

typedef struct med {
  int MedID;
  char brandName[100];
  char genericName[100];
  char manufacturingCompany[100];
  char dosageForm[30];
  char strength[30];
  int packSize;
  double pricePerPack;
  double pricePerUnit;
  int inStock;
  char indications[1000];
} med;

med drug[MAX];
int top = -1;

typedef struct receipt {
  int RID;
  char cName[30];
  char cPhone[20];
  char rDate[40];
  int hour;
  int min;
  char AMPM[30];
  int items;
  char meds[30][50];
  int units[30];
  double unitPrice[30];
  double totalPrice;
} receipt;

receipt rec[MAX];
int rTop = -1;

double Total_Sales = 0;
double Profit;

void loadAll() {

  FILE *fpr, *ftop, *fprSup, *fprsTop;
  ftop = fopen("top.dat", "r");
  fpr = fopen("medinfo.dat", "r");
  fprSup = fopen("SupplierInfo.dat", "r");
  fprsTop = fopen("sTop.dat", "r");
  if (fpr == NULL || ftop == NULL) {
    fprintf(stderr, "Error while opening file!");
    exit(1);
  }
  if (fprSup == NULL || fprsTop == NULL)
    printf("Failed to open file in read mode!\n");
  fscanf(fprsTop, "%d", &sTop);
  for (int i = 0; i <= sTop; i++) {
    fscanf(fprSup, SUP_DATA_FORMAT_IN, &sup[i].supID, sup[i].comName,
           sup[i].salesMan, sup[i].phnNum, sup[i].email);
  }
  fclose(fprsTop);
  fclose(fprSup);

  fscanf(ftop, "%d", &top);
  int i = 0;
  //int data = 0;
  //printf("\nloading data....\n");
  //printf("\ntop index is %d\n", top);
  while (i <= top) {

    //data +=
        fscanf(fpr, MED_DATA_FORMAT_IN, &drug[i].MedID, drug[i].brandName,
               drug[i].genericName, drug[i].manufacturingCompany,
               drug[i].dosageForm, drug[i].strength, &drug[i].pricePerPack,
               &drug[i].pricePerUnit, &drug[i].inStock, drug[i].indications);
    i++;
  }
  //printf("\n%d data loaded\n\n", data / 9);
  fclose(ftop);
  fclose(fpr);
  orderInfoRead();
  loadReceipts();
  loginInfoRead();
}

void updateFile() {
  FILE *fpwrite, *fptop;
  fpwrite = fopen("medinfo.dat", "w");
  fptop = fopen("top.dat", "w");
  if (fpwrite == NULL || fptop == NULL) {
    printf("Failed to write!\n");
    exit(1);
  }
  int err = 0, i = 0;
  while (i <= top) {
    err +=
        fprintf(fpwrite, MED_DATA_FORMAT_OUT, drug[i].MedID, drug[i].brandName,
                drug[i].genericName, drug[i].manufacturingCompany,
                drug[i].dosageForm, drug[i].strength, drug[i].pricePerPack,
                drug[i].pricePerUnit, drug[i].inStock, drug[i].indications);
    i++;
  }
  fprintf(fptop, "%d", top);
  if (err != 0)
    printf("\nData updated!\n");
  fclose(fptop);
  fclose(fpwrite);
  systemClear();
}

void alignment(int k, int length) {

  k = k - length;
  while (k != 0) {
    printf(" ");
    k--;
  }
}

void addNew() {
  if (top <= MAX) {
    top++;
    systemClear();
    printf("MedID: %d\n", top + 101);
    drug[top].MedID = top + 101;
    printf("Brand name: ");
    scanf(" %[^\n]%*c", drug[top].brandName);
    printf("Generic name: ");
    scanf("%[^\n]%*c", drug[top].genericName);
    printf("Manufacturing company: ");
    scanf("%[^\n]%*c", drug[top].manufacturingCompany);
    printf("Dosage form: ");
    scanf("%[^\n]%*c", drug[top].dosageForm);

    printf("Dose strength: ");
    scanf("%[^\n]%*c", drug[top].strength);

    if (strcmp(drug[top].dosageForm, "Syrup") != 0 &&
        strcmp(drug[top].dosageForm, "syrup") != 0 &&
        strcmp(drug[top].dosageForm, "Cream") != 0 &&
        strcmp(drug[top].dosageForm, "cream") != 0) {
      printf("Pack Size: ");
      scanf("%d", &drug[top].packSize);
    } else {
      drug[top].packSize = 1;
      printf("Pack Size: %d\n", drug[top].packSize);
    }
    printf("Price/pack: ");
    scanf("%lf", &drug[top].pricePerPack);

    drug[top].pricePerUnit = (drug[top].pricePerPack) / (drug[top].packSize);

    printf("Price/unit: %.2lf\n", drug[top].pricePerUnit);

    printf("In stock(unit): ");
    scanf("%d", &drug[top].inStock);

    printf("Indications: ");
    scanf(" %[^\n]%*c", drug[top].indications);

    printf("\n");
    updateFile();
  } else
    printf("Maximum stack size reached\n");
}

void display() {
  int i = 0;
  while (i <= top) {
    printf(MED_DATA_FORMAT_CONSOLE, drug[i].MedID, drug[i].brandName,
           drug[i].genericName, drug[i].manufacturingCompany,
           drug[i].dosageForm, drug[i].strength, drug[i].pricePerPack,
           drug[i].pricePerUnit, drug[i].inStock, drug[i].indications);
    i++;
  }
  printf("\n");
}

int returnToMain() {
  systemClear();
  return 0;
}

int search(int Bool) {
  systemClear();
  char key[10];
  char const *back = "0";
  int count;
mac:
  count = 0;
  printf("\n");
  alignment(30, 3);
  printf("SEARCH\n");
  printf("%s\n", UB);
  printf("Input the search key: ");
  scanf(" %[^\n]%*c", key);
  printf("\n");
  if (strlen(key) < 3) {
    printf("\nPlease input at least 3 characters!\n");
    goto mac;
  } else {
    char temp_bN[100], temp_gN[100], temp_mC[100], temp_dF[100], temp_iN[1000];
    for (int i = 0; i <= top; i++) {
      strcpy(temp_bN, drug[i].brandName);
      strcpy(temp_gN, drug[i].genericName);
      strcpy(temp_mC, drug[i].manufacturingCompany);
      strcpy(temp_dF, drug[i].dosageForm);
      strcpy(temp_iN, drug[i].indications);
      if (strstr(strlwr(temp_bN), strlwr(key)) || strstr(strlwr(temp_gN), strlwr(key)) ||
          strstr(strlwr(temp_mC), strlwr(key)) || strstr(strlwr(temp_dF), strlwr(key)) ||
          strstr(strlwr(temp_iN), strlwr(key))) {
        printf(MED_DATA_FORMAT_CONSOLE, drug[i].MedID, drug[i].brandName,
               drug[i].genericName, drug[i].manufacturingCompany,
               drug[i].dosageForm, drug[i].strength, drug[i].pricePerPack,
               drug[i].pricePerUnit, drug[i].inStock, drug[i].indications);
        count++;
      }
    }
    printf("\na total of %d result(s) found\n___________________________\n",
           count);
  }
  if (Bool){
    goBack();
    return count;
  }
  else
    return count;
}

void delData() {
  int id = 1, i, j, res;

  res = search(0);
  if (res == 0) {
    printf("\n***Showing all available data***\n\n");
    display();
  }
REID:
  printf("Input the MedID to delete(0 to return): ");
  scanf("%d", &id);
  if (id == 0)
    returnToMain();
  else if (id < 101 || id > drug[top].MedID) {
    systemClear();
    printf("\n**Wrong ID, Try Again!!**\n\n");
    goto REID;
  }

  else {
    for (i = 0; i <= top; i++)
      if (drug[i].MedID == id) {
        id = i;
        break;
      }

    for (j = i; j < top; j++) {
      strcpy(drug[j].brandName, drug[j + 1].brandName);
      strcpy(drug[j].genericName, drug[j + 1].genericName);
      strcpy(drug[j].manufacturingCompany, drug[j + 1].manufacturingCompany);
      strcpy(drug[j].dosageForm, drug[j + 1].dosageForm);
      strcpy(drug[j].strength, drug[j + 1].strength);
      drug[j].pricePerPack = drug[j + 1].pricePerPack;
      drug[j].pricePerUnit = drug[j + 1].pricePerUnit;
      drug[j].inStock = drug[j + 1].inStock;
      strcpy(drug[j].indications, drug[j + 1].indications);
    }
    top--;
    updateFile();
  }
}

void editData() {
  int id = -1, res, option;
  res = search(0);

  if (res == 0) {
    printf("\n***Showing all available data***\n\n");
    display();
  }
DE:
  printf("\nInput the MedID to edit(0 to return): ");
  scanf("%d", &id);
  if (id == 0)
    returnToMain();
  else if (id < 101 || id > drug[top].MedID) {
    printf("\n**Wrong ID, Try Again!**\n\n");
    goto DE;
  } else {
    while (1) {
      systemClear();
      printf("Which data would you like to edit?\n");
      printf("1.Brand name\n");
      printf("2.Generic name\n");
      printf("3.Manufacturering company\n");
      printf("4.Dosage form\n");
      printf("5.Strength\n");
      printf("6.Price/Pack\n");
      printf("7.In stock\n");
      printf("8.Indications\n");
      printf("0.Return\n");
      scanf("%d", &option);
      switch (option) {
      case 1:
        printf("Brand name: ");
        scanf(" %[^\n]%*c", drug[id - 101].brandName);
        break;
      case 2:
        printf("Generic name: ");
        scanf(" %[^\n]%*c", drug[id - 101].genericName);
        break;
      case 3:
        printf("Manufacturing company: ");
        scanf(" %[^\n]%*c", drug[id - 101].manufacturingCompany);
        break;
      case 4:
        printf("Dosage form: ");
        scanf(" %[^\n]%*c", drug[id - 101].dosageForm);
        break;
      case 5:
        printf("Dose strength: ");
        scanf(" %[^\n]%*c", drug[id - 101].strength);
        break;
      case 6:
        printf("Price/pack: ");
        scanf("%lf", &drug[id - 101].pricePerPack);
        break;
      case 7:
        printf("In stock: ");
        scanf("%d", &drug[id - 101].inStock);
        break;
      case 8:
        printf("Indications: ");
        scanf(" %[^\n]%*c", drug[id - 101].indications);
        break;
      case 0:
        break;
      default:
        printf("Wrong Input!");
        break;
      }
      updateFile();
      if (option == 0)
        break;
    }
  }
}

// SUPPLIER PART

void addSupplier() {
  sTop++;

  sup[sTop].supID = sTop + 101;
  printf("\nSuppiler ID: %d\n", sup[sTop].supID);
  printf("Enter the company Name: ");
  scanf(" %[^\n]%*c", sup[sTop].comName);
  printf("Enter the dealer's Name: ");
  scanf("%[^\n]%*c", sup[sTop].salesMan);
  printf("Enter the phone Number: ");
  scanf("%[^\n]%*c", sup[sTop].phnNum);
  printf("Enter the email: ");
  scanf("%[^\n]%*c", sup[sTop].email);
  updatefileSup();
  printf("\nSuccesfully Updated!\n");
  goBack();
}

void displaySupplier() {
  for (int i = 0; i <= sTop; i++) {
    printf("\nSuppiler ID: %d\n", sup[i].supID);
    printf("Company Name: %s\n", sup[i].comName);
    printf("Dealer's Name: %s\n", sup[i].salesMan);
    printf("Phone Number: %s\n", sup[i].phnNum);
    printf("Email: %s\n", sup[i].email);
  }
}

int searchSupplier(int Bool) {
  char key[20];
  int count = 0;
  printf("\nSearch Company or Dealer: ");
  scanf(" %[^\n]%*c", key);
  char temp_cN[70], temp_sM[70];
  for (int i = 0; i <= sTop; i++) {
    strcpy(temp_cN, sup[i].comName);
    strcpy(temp_sM, sup[i].salesMan);

    if (strstr(strlwr(temp_cN), strlwr(key)) || strstr(strlwr(temp_sM), strlwr(key))) {
      printf("\nSuppiler ID: %d\n", sup[i].supID);
      printf("Company Name: %s\n", sup[i].comName);
      printf("Dealer's Name : %s\n", sup[i].salesMan);
      printf("Phone Number: %s\n", sup[i].phnNum);
      printf("Email: %s\n", sup[i].email);
      count++;
    }
  }
  if (count < 1)
    printf("\nSearch result not found.\n");

  if (Bool) {
    goBack();
    return count;
  } else
    return count;
}

void delSupplier() {
  int del;
  foundIndex = -1;
  int res = searchSupplier(0);
  if (res == 0) {
    printf("\n***Showing all available data***\n");
    displaySupplier();
  }
  printf("\nEnter the supplier ID to remove: ");
  scanf("%d", &del);
  for (int i = 0; i <= sTop; i++) {
    if (sup[i].supID == del) {
      foundIndex = i;
      break;
    }
  }
  if (foundIndex < 0) {
    printf("\nNot in database.\n");
  } else {
    for (int i = foundIndex; i < sTop; i++) {
      strcpy(sup[i].comName, sup[i + 1].comName);
      strcpy(sup[i].salesMan, sup[i + 1].salesMan);
      strcpy(sup[i].phnNum, sup[i + 1].phnNum);
      strcpy(sup[i].email, sup[i + 1].email);
    }
    sTop--;
    systemClear();
    printf("\nSuccessfully removed!\n");
    updatefileSup();
  }
}

void editSupplier() {
  foundIndex = -1;
  int edit;
  int res = searchSupplier(0);
  if (res == 0) {
    printf("\n***Showing all available data***\n");
    displaySupplier();
  }
  printf("\nEnter the supplier ID to edit: ");
  scanf("%d", &edit);
  for (int i = 0; i <= sTop; i++) {
    if (sup[i].supID == edit) {
      foundIndex = i;
      break;
    }
  }
  if (foundIndex < 0) {
    printf("\nNot in database.\n");
  } else {
    int op;
  WI:
    systemClear();
    printf("\n");
    alignment(20, 8);
    printf("You can replace\n");
    printf("%s", SB);
    printf("\n1. Company Name");
    printf("\n2. Dealer's Name");
    printf("\n3. Phone Number");
    printf("\n4. Email");
    printf("\n0. Return\n");
    printf("%s", SB);
    printf("\nSelect an option: ");
    scanf("%d", &op);
    switch (op) {
    case 1:
      printf("\nNew company name: ");
      scanf(" %[^\n]%*c", sup[foundIndex].comName);
      break;
    case 2:
      printf("\nNew Dealer's name: ");
      scanf(" %[^\n]%*c", sup[foundIndex].salesMan);
      break;
    case 3:
      printf("\nNew Phone Number: ");
      scanf(" %[^\n]%*c", sup[foundIndex].phnNum);
      break;
    case 4:
      printf("\nNew Email: ");
      scanf(" %[^\n]%*c", sup[foundIndex].email);
      break;
    case 0:
      supplierPanel();
      break;
    default:
      printf("\nWrong Input!\n");
      goto WI;
      break;
    }
    printf("\nData updated!\n");
    updatefileSup();
  }
}

void updatefileSup() {
  FILE *fpwSup, *fpwsTop;
  fpwSup = fopen("SupplierInfo.dat", "w");
  fpwsTop = fopen("sTop.dat", "w");
  if (fpwSup == NULL || fpwsTop == NULL)
    printf("Failed to open file in write mode!\n");
  for (int i = 0; i <= sTop; i++) {
    fprintf(fpwSup, SUP_DATA_FORMAT_OUT, sup[i].supID, sup[i].comName,
            sup[i].salesMan, sup[i].phnNum, sup[i].email);
  }
  fprintf(fpwsTop, "%d", sTop);
  fclose(fpwsTop);
  fclose(fpwSup);
}

// LOGIN & MENU PART

void menu() {

  while (1) {
    int op;
    systemClear();
    printf("\n");
    alignment(30, 4);
    printf("MAIN MENU\n");
    printf("%s", UB);
    printf("%s\n", UB);
    alignment(30, 12);
    printf("Enter an option <1 to 4> \n");
    printf("%s", UB);
    printf("\n");
    alignment(30, 6);
    printf("1. Search\n");
    alignment(30, 6);
    printf("2. Browse\n");
    alignment(30, 6);
    printf("3. Order now\n");
    alignment(30, 6);
    printf("4. Contact us\n");
    alignment(30, 6);
    printf("0. Exit\n");
    printf("%s", UB);
    printf("\n");
    alignment(30, 12);
    printf("Enter < 5 > Admin Panel\n");
    printf("%s\n", UB);
    printf("Select an option: ");
    scanf("%d", &op);
    switch (op) {
    case 1:
      search(1);
      break;
    case 2:
      systemClear();
      display();
      goBack();
      break;
    case 3:
      systemClear();
      addOrder();
      break;
    case 4:
      systemClear();
      contactInfo();
      goBack();
      break;
    case 5:
      while (1) {
        int o;
        systemClear();
        printf("\n");
        alignment(30, 4);
        printf("SIGN IN\n");
        printf("%s\n", UB);
        alignment(30, 7);
        printf("1. Login\n");
        alignment(30, 7);
        printf("2. Reset Password\n");
        alignment(30, 7);
        printf("0. Return\n");
        printf("%s\n", UB);
        printf("Select an option: ");
        scanf(" %d", &o);
        systemClear();
        if (o == 1) {
          login();
        } else if (o == 2)
          loginInfoWrite();
        else if (o == 0) {
          break;
        }
      }
      break;
    case 0:
      systemClear();
      printf("\n\n        !! THANK YOU FOR USING OUR SERVICE !!\n\n");
      exit(0);
      break;
    default:
      printf("Wrong input!\n");
      break;
    }
  }
}

void supplierPanel() {
  while (1) {
    systemClear();
    printf("\n");
    alignment(30, 5);
    printf("SUPPLIER\n");
    printf("%s\n", RB);
    alignment(30, 7);
    printf("Your options\n");
    printf("%s", RB);
    printf("\n1. Add");
    printf("\n2. Remove");
    printf("\n3. Edit");
    printf("\n4. Browse");
    printf("\n5. Search");
    printf("\n0. Return\n");
    printf("%s\n", RB);
    printf("%s\n", RB);
    printf("Select an option: ");

    int op;
    scanf("%d", &op);
    switch (op) {
    case 1:
      systemClear();
      addSupplier();
      break;
    case 2:
      delSupplier();
      goBack();
      break;
    case 3:
      editSupplier();
      goBack();
      break;
    case 4:
      systemClear();
      displaySupplier();
      goBack();
      break;
    case 5:
      searchSupplier(1);
      break;
    case 0:
      AdminPanel();
      break;
    default:
      printf("Wrong Input!");
      break;
    }
  }
}

void AdminPanel() {
  int choice;
  while (1) {
    systemClear();
    printf("\n");
    alignment(30, 3);
    printf("ADMIN\n");
    printf("%s\n", UB);
    alignment(30, 6);
    printf("Your options\n");
    printf("%s\n", UB);
    printf("1. Add\n");
    printf("2. Remove\n");
    printf("3. Edit\n");
    printf("4. Browse\n");
    printf("5. Search\n");
    printf("6. Sales\n");
    printf("7. Supplier\n");
    printf("8. Tech-Support\n");
    printf("%s\n", UB);
    alignment(30, 8);
    printf("Press <0> To Logout\n");
    printf("%s\n", UB);
    // printf("%s", L);
    printf("Select an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addNew();
      systemClear();
      break;
    case 2:
      delData();
      break;
    case 3:
      editData();
      break;
    case 4:
      systemClear();
      display();
      goBack();
      break;
    case 5:
      search(1);
      break;
    case 6:
      sales();
      break;
    case 7:
      supplierPanel();
      break;
    case 8:
      techTeam();
      break;
    case 0:
      printf("Logging out......\n");
      systemClear();
      menu();
      break;
    }
  }
}

typedef struct admin {
  char userName[20];
  char password[20];
} admin;
admin ad;

void loginInfoWrite() {
  printf("\nSet the new username & password.\n\n");
  printf("username: ");
  scanf("%s", ad.userName);
  printf("password: ");
  scanf("%s", ad.password);
  FILE *fpwlogin;
  fpwlogin = fopen("loginInfo.dat", "w");
  if (fpwlogin == NULL)
    printf("Failed to open file in write mode!\n");
  fprintf(fpwlogin, "%s %s", ad.userName, ad.password);
  fclose(fpwlogin);
}
void login() {
  while (1) {
    char c, userName[20], password[20];
    int i;
    systemClear();
    printf("\n");
    alignment(20, 3);
    printf("LOGIN\n");
    printf("__________________________________________\n");
    printf("\nUsername: ");
    scanf("%s", userName);
    printf("Password: ");
    i = 0;
    while ((c = _getch()) != 13) { //password masking for CB
       password[i] = c;
       printf("*");
       i++;
     }
    password[i] = '\0';
    //scanf("%s", password);
    if (strcmp(userName, ad.userName) == 0 &&
        strcmp(password, ad.password) == 0) {
      systemClear();
      AdminPanel();
    } else {

      printf("\nWrong Login Info!\n\n");

      printf("Press < 1 > to try again.\n");
      printf("Press < 2 > to go back.\n");
      int op;
      while (1) {

        scanf("%d", &op);
        if (op == 1)
          break;
        else if (op == 2)
          break;
        else
          printf("\nOption does not exist! Try again!\n\n");
      }
      if (op == 2)
        break;
    }
  }
}
void loginInfoRead() {
  FILE *fprlogin;
  fprlogin = fopen("loginInfo.dat", "r");
  fscanf(fprlogin, "%s %s", ad.userName, ad.password);
  fclose(fprlogin);
}

void techTeam() {
  systemClear();
  printf("\n");
  alignment(30, 6);
  printf("TECH-TEAM \n");
  printf("%s", RB);
  printf("%s\n", RB);
  printf("Abu Saleh Mohammad Naeem\n");
  printf("Phone number: 01**-*******\n");
  printf("Email: saleh.naeem.cse@ulab.edu.bd\n\n");
  printf("Urbana Jaman Orthee\n");
  printf("Phone number: 01**-*******\n");
  printf("Email: urbana.jaman.cse@ulab.edu.bd\n\n");
  printf("Tamanna Khatun\n");
  printf("Phone number: 01**-*******\n");
  printf("Email: tamanna.khatun.cse@ulab.edu.bd\n");
  printf("%s", RB);
  printf("%s\n", RB);
  goBack();
}

void contactInfo() {
  systemClear();
  printf("\n                     PHARMA-CARE           \n");
  printf("________________%s", SB);
  printf("________________%s\n", SB);
  printf("Address: Beribadh Road, Mohammadpur, Dhaka, Bangladesh\n\n");
  printf("Phone number: 01**-*******\n\n");
  printf("Email: pharma-care@gmail.com\n\n");
  printf("________________%s", SB);
}

void goBack() {
  char op;
  printf("\nEnter any key to return..\n");
  scanf(" %c", &op);
  systemClear();
}

// ORDER PART

typedef struct orderInfo {
  int orderId;
  int receiptId;
  char name[50];
  char address[50];
  char contactNum[20];
  char status[20];
} orderInfo;

orderInfo order[MAX];

int oTop = -1;

const char *ORDER_INFO_OUT =
    "{\"Order ID\": %d, \"Receipt ID\": %d, \"Name\": \"%s\", \"Address\": "
    "\"%s\", \"Contact Number\": \"%s\"}\n";

const char *ORDER_INFO_IN = "{\"Order ID\": %d, \"Receipt ID\": %d, \"Name\": "
                            "\"%[^\"]\", \"Address\": \"%[^\"]\", "
                            "\"Contact Number\": \"%[^\"]\"}\n";

void addOrder() {
  oTop++;
  order[oTop].orderId = oTop + 101;
  printf("Order ID: %d\n", order[oTop].orderId);
  printf("Name: ");
  scanf(" %[^\n]%*c", order[oTop].name);
  printf("Address: ");
  scanf("%[^\n]%*c", order[oTop].address);
  printf("Contact Number: ");
  scanf("%[^\n]%*c", order[oTop].contactNum);
  addReceipt(1);
  order[oTop].receiptId = rec[rTop].RID;
  orderInfoWrite();
}

void orderInfoWrite() {
  FILE *fpworder, *fpwotop;
  fpworder = fopen("orderInfo.dat", "w");
  fpwotop = fopen("oTop.dat", "w");
  if (fpworder == NULL || fpwotop == NULL) {
    printf("Failed to open file in write mode!\n");
    exit(0);
  }
  fprintf(fpwotop, "%d", oTop);
  for (int i = 0; i <= oTop; i++) {
    fprintf(fpworder, ORDER_INFO_OUT, order[i].orderId, order[i].receiptId,
            order[i].name, order[i].address, order[i].contactNum);
  }
  fclose(fpworder);
  fclose(fpwotop);
}

void orderInfoRead() {
  FILE *fprorder, *fprotop;
  char str[10];
  fprorder = fopen("orderInfo.dat", "r");
  fprotop = fopen("oTop.dat", "r");
  if (fprorder == NULL || fprotop == NULL) {
    printf("Failed to open file in read mode!\n");
    exit(0);
  }
  fscanf(fprotop, "%d", &oTop);
  for (int i = 0; i <= oTop; i++) {
    fscanf(fprorder, ORDER_INFO_IN, &order[i].orderId, &order[i].receiptId,
           order[i].name, order[i].address, order[i].contactNum);
  }
  fclose(fprorder);
  fclose(fprotop);
}

void displayOrder(int id) {

  systemClear();
  printf("Order ID: %d\n", order[id - 101].orderId);
  printf("Customer Name: %s\n", order[id - 101].name);
  printf("Address: %s\n", order[id - 101].address);
  printf("Contact Number: %s\n", order[id - 101].contactNum);
  displayReceipt(order[id - 101].orderId - 101);
}

void Orders() {
  systemClear();
  printf("\n");
  printf("OR-ID");
  alignment(16, strlen("OR-ID"));
  printf("NAME");
  alignment(29, strlen("NAME"));
  printf("DATE");
  printf("\n");
  printf("%s\n", RB);
  for (int i = 0; i <= oTop; i++) {
    printf("%d", order[i].orderId);
    alignment(15, 2);
    printf("%s", order[i].name);
    alignment(29, strlen(order[i].name));
    printf("%s\n", rec[order[i].orderId - 101].rDate);
  }
  printf("%s\n", RB);
  int id;
  while (1) {
    printf("\nInput ID to view details(0 to return): ");
    scanf("%d", &id);
    if (id > 100 && id <= order[oTop].orderId) {
      displayOrder(id);
      break;
    } else if (id == 0)
      break;
    else
      printf("\n**There is no such order, Try Again!**\n");
  }
}

// sales info

void sales() {
  int choice, k, L;
  while (1) {
    systemClear();
    printf("\n\n");
    alignment(30, 5);
    printf("SALES\n");
    //                       |
    printf("%s\n", RB);
    //                    |
    alignment(30, 8);
    printf("Your options\n");
    printf("%s", RB);
    printf("\n1. Make Receipts");
    k = 41 - strlen("1. Make Receipts");
    while (k != 0) {
      printf(" ");
      k--;
    }
    printf("Total Sale: $%0.2lf", Total_Sales);
    printf("\n2. Order List");
    L = 44 - strlen("1. Make Receipts");
    while (L != 0) {
      printf(" ");
      L--;
    }
    printf("Profit: $%.2lf", Total_Sales * (10.0 / 100.0));
    printf("\n3. Receipts");
    printf("\n0. Return\n");
    printf("%s\n", RB);

    printf("Select an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("\n");
      addReceipt(0);
      break;
    case 2:
      Orders();
      break;
    case 3:
      Receipts();
      break;
    case 0:
      break;
    default:
      systemClear();
      printf("\n**Wrong Input, Try Again!**\n\n");
    }
    if (choice == 0)
      break;
  }
}

// RECIEPT PART

const char *RECEIPT_OUT_A = "%d \"%s\" \"%s\" \"%s\" %d %d \"%s\" %d\n";
const char *RECEIPT_OUT_B = "\"%s\" %d %lf\n";
const char *RECEIPT_OUT_C = "%lf\n\n";

const char *RECEIPT_IN_A =
    "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d %d \"%[^\"]\" %d\n";
const char *RECEIPT_IN_B = "\"%[^\"]\" %d %lf\n";
const char *RECEIPT_IN_C = "%lf\n\n";
char *testing;

void addReceipt(int Bool) {
  if (rTop < 100) {

    rTop++;
    rec[rTop].RID = rTop + 101;
    rec[rTop].totalPrice = 0.0;
    if (Bool)
      printf("\n\n");
    printf("Receipt ID: %d\n", rec[rTop].RID);
    printf("%s\n", rec[rTop].rDate);
    if (Bool) {
      order[oTop].receiptId = rec[rTop].RID;
      strcpy(rec[rTop].cName, order[oTop].name);
      strcpy(rec[rTop].cPhone, order[oTop].contactNum);
      printf("Customer Name: %s\n", rec[rTop].cName);
      printf("Phone: %s\n", rec[rTop].cPhone);

    } else {
      printf("Customer Name: ");
      scanf(" %[^\n]%*c", rec[rTop].cName);
      printf("Phone: ");
      scanf("%[^\n]%*c", rec[rTop].cPhone);
    }
    printf("Number of item(s): ");
    scanf("%d", &rec[rTop].items);
    int id, i = 0;
    int res = 0;
    while (i < rec[rTop].items) {
      if (res == 0 && search(0) < 1) {
        printf("\n***Showing all available data***\n\n");
        display();
        res++;
      }
    RE:
      printf("\nMedID: ");
      scanf("%d", &id);
      if (id < 101 || id > drug[top].MedID) {
        printf("Wrong id try again!\n");
        goto RE;
      }

      else {
        strcpy(rec[rTop].meds[i], drug[id - 101].brandName);
        printf("Unit(s): ");
        scanf("%d", &rec[rTop].units[i]);
        drug[id - 101].inStock -= rec[rTop].units[i];
        rec[rTop].unitPrice[i] = drug[id - 101].pricePerUnit;
        rec[rTop].totalPrice += (rec[rTop].units[i]) * (rec[rTop].unitPrice[i]);
        i++;
        printf("added!\n");
      }
    }
    currentDate();
    currentTime();
    Total_Sales += rec[rTop].totalPrice;
    updateReceipts();
    systemClear();
    displayReceipt(rTop);
  }
}
/*void test() {
  rTop++;
  rec[rTop].RID = rTop + 101;

  time_t currentTime;
  time(&currentTime);
  strcpy(rec[rTop].cName, "orthee j.");
  strcpy(rec[rTop].cPhone, "017XXXXXXX");
  rec[rTop].items = 3;
  strcpy(rec[rTop].rDate, "24/04/2202");
  rec[rTop].totalPrice = 0.0;
  for (int i = 0; i < rec[rTop].items; i++) {
    strcpy(rec[rTop].meds[i], drug[i].brandName);
    rec[rTop].units[i] = i + 1;
    rec[rTop].unitPrice[i] = drug[i].pricePerUnit;
    rec[rTop].totalPrice += (rec[rTop].units[i] * rec[rTop].unitPrice[i]);
  }
}*/

void updateReceipts() {
  FILE *fpw, *fpwt, *fpwsales;
  fpwsales = fopen("salesRecord.dat", "w");
  fpw = fopen("receipts.dat", "w");
  fpwt = fopen("rTop.dat", "w");
  if (fpw == NULL || fpwt == NULL || fpwsales == NULL) {
    printf("Failed to open file in write mode\n");
    exit(1);
  }
  fprintf(fpwsales, "%.2lf", Total_Sales);
  fprintf(fpwt, "%d", rTop);
  for (int i = 0; i <= rTop; i++) {
    fprintf(fpw, RECEIPT_OUT_A, rec[i].RID, rec[i].cName, rec[i].cPhone,
            rec[i].rDate, rec[i].hour, rec[i].min, rec[i].AMPM, rec[i].items);
    for (int j = 0; j < rec[i].items; j++)
      fprintf(fpw, RECEIPT_OUT_B, rec[i].meds[j], rec[i].units[j],
              rec[i].unitPrice[j]);
    fprintf(fpw, RECEIPT_IN_C, rec[i].totalPrice);
  }
  fclose(fpw);
  fclose(fpwt);
  fclose(fpwsales);
}

void loadReceipts() {
  FILE *fpr, *fprt, *fprsales;
  fpr = fopen("receipts.dat", "r");
  fprt = fopen("rTop.dat", "r");
  fprsales = fopen("salesRecord.dat", "r");
  if (fpr == NULL || fprt == NULL || fprsales == NULL) {
    printf("Failed to open file in write mode\n");
    exit(1);
  }
  fscanf(fprsales, "%lf", &Total_Sales);
  fscanf(fprt, "%d", &rTop);
  for (int i = 0; i <= rTop; i++) {
    fscanf(fpr, RECEIPT_IN_A, &rec[i].RID, rec[i].cName, rec[i].cPhone,
           rec[i].rDate, &rec[i].hour, &rec[i].min, rec[i].AMPM, &rec[i].items);
    for (int j = 0; j < rec[i].items; j++)
      fscanf(fpr, RECEIPT_IN_B, rec[i].meds[j], &rec[i].units[j],
             &rec[i].unitPrice[j]);
    fscanf(fpr, RECEIPT_IN_C, &rec[i].totalPrice);
  }

  fclose(fpr);
  fclose(fprt);
  fclose(fprsales);
}

void Receipts() {
  systemClear();
  printf("\n");
  printf("RE-ID");
  alignment(16, strlen("RE-ID"));
  printf("NAME");
  alignment(29, strlen("NAME"));
  printf("DATE");
  printf("\n");
  printf("%s\n", RB);
  for (int i = 0; i <= rTop; i++) {
    printf("%d", rec[i].RID);
    alignment(15, 3);
    printf("%s", rec[i].cName);
    alignment(29, strlen(rec[i].cName));
    printf("%s\n", rec[i].rDate);
  }
  printf("%s\n", RB);
  int id;
  while (1) {
    printf("\nInput ID to view details (0 to return): ");
    scanf("%d", &id);
    if (id > 100 && id <= rec[rTop].RID) {
      displayReceipt(id - 101);
      break;
    } else if (id == 0)
      break;
    else
      printf("\n**There is no such receipt, try again!**\n");
  }
}

void displayReceipt(int id) {
  systemClear();
  int k, Length, L, P;
  printf("\n");
  printf("                      PHARMA-CARE\n");
  printf("      Beribadh Road, Mohammadpur, Dhaka, Bangladesh\n");
  printf("                Contact: 01**-*******\n");
  printf("                Email: pharma-care@gmail.com\n");
  printf("\n\n");
  printf("RecieptID: %d\n", rec[id].RID);
  printf("%s\n", RB);
  printf("Customer name: %s\n", rec[id].cName);
  printf("                                         %s", rec[id].rDate);
  printf("\n");
  printf("Phone number: %s", rec[id].cPhone);
  P = 29 - strlen(rec[id].cPhone);
  while (P != 0) {
    printf(" ");
    P--;
  }
  if (rec[id].hour <= 9) {
    if (rec[id].min <= 9)
      printf("0%d:0%d %s\n", rec[id].hour, rec[id].min, rec[id].AMPM);
    else
      printf("0%d:%d %s\n", rec[id].hour, rec[id].min, rec[id].AMPM);
  } else
    printf("%d:%d %s\n", rec[id].hour, rec[id].min, rec[id].AMPM);
  printf("%s", RB);
  printf("%s\n", RB);
  printf("Item");
  printf("                    Qty");
  printf("                  Price\n");
  printf("%s\n", RB);

  for (int j = 0; j < rec[id].items; j++) {
    printf("%s", rec[id].meds[j]);
    alignment(21, strlen(rec[id].meds[j]));
    printf("\t%d", rec[id].units[j]);
    if (rec[id].units[j] <= 9)
      Length = 1;
    else if (rec[id].units[j] >= 10 && rec[id].units[j] <= 99)
      Length = 2;
    else if (rec[id].units[j] >= 100 && rec[id].units[j] <= 999)
      Length = 3;
    else {
      L = 1 + (int)log10(rec[id].units[j]);
      Length = L;
    }
    alignment(21, Length);
    printf("$%0.2f", rec[id].unitPrice[j]);
    printf("\n");
  }
  printf("%s\n", RB);
  printf("                                  Total:     $%.2lf\n",
         rec[id].totalPrice);
  printf("\n\n\n");
  printf("           !! THANK YOU FOR USING OUR SERVICE !!\n\n");
  goBack();
}

// DATE & TIME PART START

void currentDate() {
  time_t t;
  t = time(NULL);
  struct tm tm = *localtime(&t);
  char day[100], month[100], year[100];
  sprintf(day, "%d", tm.tm_mday);
  int m;
  m = tm.tm_mon + 1;
  switch (m) {
  case 1:
    strcpy(month, " Jan, ");
    break;
  case 2:
    strcpy(month, " Feb, ");
    break;
  case 3:
    strcpy(month, " Mar, ");
    break;
  case 4:
    strcpy(month, " Apr, ");
    break;
  case 5:
    strcpy(month, " May, ");
    break;
  case 6:
    strcpy(month, " June, ");
    break;
  case 7:
    strcpy(month, " July, ");
    break;
  case 8:
    strcpy(month, " Aug, ");
    break;
  case 9:
    strcpy(month, " Sep, ");
    break;
  case 10:
    strcpy(month, " Oct, ");
    break;
  case 11:
    strcpy(month, " Nov, ");
    break;
  case 12:
    strcpy(month, " Dec, ");
    break;
  }
  sprintf(year, "%d", tm.tm_year + 1900);
  strcat(day, month);
  strcat(day, year);
  strcpy(rec[rTop].rDate, day);
}

void currentTime() {
  time_t t;
  int hour, min;
  t = time(NULL);
  struct tm tm = *localtime(&t);
  min = tm.tm_min;
  rec[rTop].min = min;
  if (tm.tm_hour >= 12) {
    if (tm.tm_hour == 12) {
      hour = 12;
      rec[rTop].hour = hour;
    } else {
      hour = tm.tm_hour - 12;
      rec[rTop].hour = hour;

    }
    strcpy(rec[rTop].AMPM, "PM");
  } else {
    rec[rTop].hour = tm.tm_hour;
    strcpy(rec[rTop].AMPM, "AM");
  }
}

int main() {
  loadAll();
  menu();
  return 0;
}
