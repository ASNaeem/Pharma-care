#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu();
void updateFile();
void addNew();
void loadAll();
void display();
void search();
void delData();
void editData();
void addSupplier();
void displaySupplier();
void searchSupplier();
void delSupplier();
void editSupplier();
void updatefileSup();
void AdminPanel();
void supplierPanel();
void loginInfoWrite();
void loginInfoRead();
void orderInfoWrite();
void orderInfoRead();
void displayOrder();
void contactInfo();
void goBack();


const char *UB = "_________________________________________\n";
const char *L = {"|"};
const char *R = {"|\n"};

#define MAX 100
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

supplier sup[100];
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
// void delay(int seconds) {
//   int mseconds = 1000 * seconds;
//   clock_t startTime = clock();
//   while (clock() < startTime + mseconds)
//     ;
// }

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
}

void addNew() {
  if (top <= MAX) {
    top++;
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

    printf("Price/pack: ");
    scanf("%lf", &drug[top].pricePerPack);
    printf("Price/unit: ");
    scanf("%lf", &drug[top].pricePerUnit);

    printf("In stock(unit): ");
    scanf("%d", &drug[top].inStock);

    printf("Indications: ");
    scanf(" %[^\n]%*c", drug[top].indications);

    printf("\n");
    updateFile();
  } else
    printf("Maximum stack size reached\n");
}

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
  int data = 0;
  printf("\nloading data....\n");
  // delay(2000);
  printf("\ntop index is %d\n", top);
  while (i <= top) {

    data +=
        fscanf(fpr, MED_DATA_FORMAT_IN, &drug[i].MedID, drug[i].brandName,
               drug[i].genericName, drug[i].manufacturingCompany,
               drug[i].dosageForm, drug[i].strength, &drug[i].pricePerPack,
               &drug[i].pricePerUnit, &drug[i].inStock, drug[i].indications);
    i++;
  }
  printf("\n%d data loaded\n\n", data / 9);
  fclose(ftop);
  fclose(fpr);
  orderInfoRead(); // issue here
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
  goBack();
}

int returnToMain() { return 0; }

void search() {
  system("clear");
  char key[100];
  char const *back = "0";
  int count;
mac:
  count = 0;
  printf("\n                     SEARCH           \n");
  printf("_____________%s\n", UB);
  printf("Input the search key (case sensitive, 0 to return): ");
  scanf(" %[^\n]%*c", key);
  printf("\n");
  if (strstr(key, back))
    returnToMain();
  else if (strlen(key) < 3) {
    printf("\nPlease input at least 3 characters!\n");
    goto mac;
  } else {
    for (int i = 0; i <= top; i++) {
      if (strstr(drug[i].brandName, key) || strstr(drug[i].genericName, key) ||
          strstr(drug[i].manufacturingCompany, key) ||
          strstr(drug[i].indications, key)) {
        printf(MED_DATA_FORMAT_CONSOLE, drug[i].MedID, drug[i].brandName,
               drug[i].genericName, drug[i].manufacturingCompany,
               drug[i].dosageForm, drug[i].strength, drug[i].pricePerPack,
               drug[i].pricePerUnit, drug[i].inStock, drug[i].indications);
        count++;
      }
    }
    printf("\na total of %d results found\n___________________________\n",
           count);
  }
  goBack();
}

void delData() {
  int id = 1, i, j;
REDEL:
  search();
  printf("Input the MedID to delete(0 to return): ");
  scanf("%d", &id);
  if (id == 0)
    goto REDEL;
  for (i = 0; i <= top; i++) {
    if (drug[i].MedID == id) {
      break;
    }
  }
  for (j = i; j < top; j++) {
    drug[j].MedID = drug[j + 1].MedID;
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

void editData() {
  int id = 1, i, option;
  search();
RE:
  printf("Input the MedID to edit(0 to return): ");
  scanf("%d", &id);
  if (id == 0)
    returnToMain();
  for (i = 0; i <= top; i++) {
    if (drug[i].MedID == id) {
      break;
    }
  }
  printf("Which data would you like to edit?\n");
  printf("1.Brand name\n");
  printf("2.Generic name\n");
  printf("3.Manufacturering company\n");
  printf("4.Dosage form\n");
  printf("5.Strength\n");
  printf("6.Price/Pack\n");
  printf("7.Price/Unit\n");
  printf("8.In stock\n");
  printf("9.Indications\n");
  printf("10.All\n");
  printf("0.Return\n");
  scanf("%d", &option);
  switch (option) {
  case 1:
    printf("Brand name: ");
    scanf(" %[^\n]%*c", drug[i].brandName);
    break;
  case 2:
    printf("Generic name: ");
    scanf("%[^\n]%*c", drug[i].genericName);
  case 3:
    printf("Manufacturing company: ");
    scanf("%[^\n]%*c", drug[i].manufacturingCompany);
    break;
  case 4:
    printf("Dosage form: ");
    scanf("%[^\n]%*c", drug[i].dosageForm);
    break;
  case 5:
    printf("Dose strength: ");
    scanf("%[^\n]%*c", drug[i].strength);
    break;
  case 6:
    printf("Price/pack: ");
    scanf("%lf", &drug[i].pricePerPack);
    break;
  case 7:
    printf("Price/unit: ");
    scanf("%lf", &drug[i].pricePerUnit);
    break;
  case 8:
    printf("In stock: ");
    scanf("%d", &drug[i].inStock);
    break;
  case 9:
    printf("Indications: ");
    scanf(" %[^\n]%*c", drug[i].indications);
    break;
  }
  updateFile();
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
  // loadAll();
  printf("\nSuccesfully Updated!");
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

void searchSupplier() {
  char key[20];
  int count = 0;
  printf("\nSearch Company or Dealer (case sensitive): ");
  scanf(" %[^\n]%*c", key);
  // system("clear");
  for (int i = 0; i <= sTop; i++) {
    if (strstr(sup[i].comName, key) || strstr(sup[i].salesMan, key)) {
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

  // goBack();
}

void delSupplier() {
  int del;
  // system("clear");
  searchSupplier();
  printf("\nEnter the supplier ID to remove: ");
  scanf("%d", &del);
  for (int i = 0; i <= sTop; i++) {
    if (sup[i].supID == del) {
      foundIndex = i;
      break;
    }
  }
  // if (foundIndex < 0) {
  //   printf("Not in database.\n");
  // } else {
  foundIndex = del - 101;
  if (foundIndex < 0) {
    printf("\nNot in database.\n");
  } else {
    sTop--;
    for (int i = foundIndex; i < sTop; i++) {
      strcpy(sup[i].comName, sup[i + 1].comName);
      strcpy(sup[i].salesMan, sup[i + 1].salesMan);
      strcpy(sup[i].phnNum, sup[i + 1].phnNum);
      strcpy(sup[i].email, sup[i + 1].email);
    }
    printf("\nSuccessfully removed!\n");
  }
  updatefileSup();
}

void editSupplier() {
  int edit;
  searchSupplier();
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
  }
  //   foundIndex = edit - 101;
  //   if (foundIndex < 0) {
  //     printf("\nNot in database.\n");
  //   }
  // }
  else {
    int op;
    system("clear");
    printf("\n            You can replace\n");
    printf("%s", UB);
    printf("\n1. Company Name");
    printf("\n2. Dealer's Name");
    printf("\n3. Phone Number");
    printf("\n4. Email\n");
    printf("%s", UB);
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
  int op;
  while (1) {
    system("clear");
    printf("               MAIN MENU           \n");
    printf("%s", UB);
    printf("%s", UB);
    printf("\n        Enter an option <1 to 4> \n");
    printf("%s", UB);
    printf("\n");
    printf("\n");
    printf("               1. Search             \n");
    printf("               2. Browse             \n");
    printf("               3. Order here             \n");
    printf("               4. Contact us             \n");
    printf("\n");
    printf("%s", UB);
    printf("\n");
    printf("         Press < 5 > To Sign-in \n");
    printf("%s\n", UB);
    printf("Select an option: ");

    scanf("%d", &op);
    switch (op) {
    case 1:
      search();
      break;
    case 2:
      system("clear");
      display();
      break;
    case 3:
      system("clear");
      display();
      break;
    case 4:
      system("clear");
      contactInfo();
      break;
    case 5:
      system("clear");
    RETRY:
      printf("\n                 SIGN IN\n");
      printf("%s", UB);
      printf("\n           1. Login");
      printf("\n           2. Reset Password\n");
      printf("%s\n", UB);
      printf("Select an option: ");
      scanf("%d", &op);
      system("clear");
      if (op == 1) {
        loginInfoRead();
      } else if (op == 2)
        loginInfoWrite();
      else {
        system("clear");
        printf("\nOption does not exist! Try again!\n");
        goto RETRY;
      }
      break;
    }
  }
}

void supplierPanel() {
  while (1) {
    system("clear");
    printf("\n                SUPPLIER\n");
    printf("%s\n", UB);
    printf("              Your options\n");
    printf("%s", UB);
    printf("\n1. Add");
    printf("\n2. Remove");
    printf("\n3. Edit");
    printf("\n4. Browse");
    printf("\n5. Search\n");
    printf("%s\n", UB);
    printf("%s\n", UB);
    printf("Select an option: ");

    int op;
    scanf("%d", &op);
    switch (op) {
    case 1:
      system("clear");
      addSupplier();
      break;
    case 2:
      delSupplier();
      goBack();
      break;
      break;
    case 3:
      editSupplier();
      goBack();
      break;
    case 4:
      system("clear");
      displaySupplier();
      goBack();
      break;
    case 5:
      searchSupplier();
      goBack();
      break;
    }
  }
}

void AdminPanel() {
  int choice;
  while (choice != 0) {
    printf("\n");
    printf("                  ADMIN\n");
    printf("%s\n", UB);
    printf("              Your options\n");
    printf("%s", UB);
    printf("\n1. Add	      ");
    printf("\n2. Remove	      ");
    printf("\n3. Edit		      ");
    printf("\n4. Browse    ");
    printf("\n5. Search 	      ");
    printf("\n6. Sales");
    printf("\n7. Supplier\n");
    printf("%s", UB);
    printf("\n            Press <0> To Logout\n");
    printf("%s\n", UB);
    // printf("%s", L);
    printf("Select an option: ");
    // printf("%s", R);
    // printf("%s", TB);
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addNew();
      system("clear");
      break;
    case 2:
      delData();
      break;
    case 3:
      editData();
      break;
    case 4:
      display(); // browse all files
      break;
    case 5:
      search();
      break;
    case 6:

      break;
    case 7:
      supplierPanel();
      break;
    case 0:
      printf("Logging out......\n");
      system("clear");
      menu();
      break;
    }
  }
}

typedef struct login {
  char userName[20];
  char password[20];
} login;
login user;

void loginInfoWrite() {
  printf("\nSet the new username & password.\n\n");
  printf("username: ");
  scanf("%s", user.userName);
  printf("password: ");
  scanf("%s", user.password);
  FILE *fpwlogin;
  fpwlogin = fopen("loginInfo.dat", "w");
  if (fpwlogin == NULL)
    printf("Failed to open file in write mode!\n");
  fprintf(fpwlogin, "%s %s", user.userName, user.password);
  fclose(fpwlogin);
}

void loginInfoRead() {
  char userName[20], password[20];
wrongPass:
  system("clear");
  printf("\n                LOGIN\n");
  printf("%s\n", UB);
  printf("Username: ");
  scanf("%s", userName);
  printf("Password: ");
  scanf("%s", password);
  FILE *fprlogin;
  fprlogin = fopen("loginInfo.dat", "r");
  fscanf(fprlogin, "%s %s", user.userName, user.password);

  if (strcmp(userName, user.userName) == 0 &&
      strcmp(password, user.password) == 0) {
    system("clear");
    // printf("Login Successful!\n");
    AdminPanel();
  } else {
    printf("\nWrong Login Info!\n\n");
    int op;
    printf("Press < 1 > to try again.\n");
    printf("Press < 2 > to go back.\n");
  RETRY:
    scanf("%d", &op);
    if (op == 1) {
      goto wrongPass;
    } else if (op == 2) {
      menu();
    } else
      printf("\nOption does not exist! Try again!\n\n");
    goto RETRY;
  }
}

void contactInfo() {
  system("clear");
  printf("\n                     PHARMA-CARE           \n");
  printf("_____________%s", UB);
  printf("_____________%s\n", UB);
  printf("Address: Beribadh Road, Mohammadpur, Dhaka, Bangladesh\n\n");
  printf("Phone number: 01**-*******\n\n");
  printf("Email: pharma-care@gmail.com\n\n");
  printf("_____________%s", UB);
  goBack();
}

void goBack() {
  char op;
  printf("\n\nPress any key to go back...\n");
  scanf(" %c", &op);
}

// ORDER PART

typedef struct orderInfo {
  int orderId;
  char firstName[20];
  char lastName[20];
  char area[20];
  char city[20];
  char contactNum[20];
  int totalItem;
  char medName[20][50];
  int qty[20];
  char status[20];
} orderInfo;

orderInfo order[100];

int oTop = -1;

const char *ORDER_INFO_OUT_START =
    "{\"First Name\": \"%s\", \"Last Name\": \"%s\", "
    "\"Area\": \"%s\", \"City\": \"%s\", \"Contact Number\": \"%s\", \"Total "
    "Item\": %d, \"Status\": \"%s\",";
const char *ORDER_INFO_OUT_MID =
    " \"Med\": \"%s\", \"qt\": %d,"; // med name and qty
const char *ORDER_INFO_OUT_END = " \"OrderID\": %d}\n";

const char *ORDER_INFO_IN_START =
    "{\"First Name\": \"%[^\"]\", \"Last Name\": \"%[^\"]\", "
    "\"Area\": \"%[^\"]\", \"City\": \"%[^\"]\", \"Contact Number\": "
    "\"%[^\"]\", \"Total Item\": %d, \"Status\": \"%[^\"]\",";
const char *ORDER_INFO_IN_MID =
    " \"Med\": \"%[^\"]\", \"qt\": %d,"; // med name and qty
const char *ORDER_INFO_IN_END = " \"OrderID\": %d}\n";

/*void editOrder(){

}*/

void displayOrder() {
  printf("%d\n", oTop);
  for (int i = 0; i <= oTop; i++) {
    printf("%s\n%s\n%s\n%s\n%s\n%d\n%s\n", order[i].firstName,
           order[i].lastName, order[i].area, order[i].city, order[i].contactNum,
           order[i].totalItem, order[i].status);
    for (int j = 0; j < order[i].totalItem; j++) {
      printf("%s\t%d\n", order[i].medName[j], order[i].qty[j]);
    }
    printf("%d\n", order[i].orderId);
  }
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
    fprintf(fpworder, ORDER_INFO_OUT_START, order[i].firstName,
            order[i].lastName, order[i].area, order[i].city,
            order[i].contactNum, order[i].totalItem, order[i].status);
    for (int j = 0; j < order[i].totalItem; j++) {
      fprintf(fpworder, ORDER_INFO_OUT_MID, order[i].medName[j],
              order[i].qty[j]);
    }
    fprintf(fpworder, ORDER_INFO_OUT_END, order[i].orderId);
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
    fscanf(fprorder, ORDER_INFO_IN_START, &order[i].orderId, order[i].firstName,
           order[i].lastName, order[i].area, order[i].city, order[i].contactNum,
           order[i].totalItem, order[i].status);
    for (int j = 0; j < order[i].totalItem; j++) {
      fscanf(fprorder, ORDER_INFO_IN_MID, order[i].medName[j], order[i].qty[j]);
    }
    fscanf(fprorder, ORDER_INFO_IN_END, order[i].orderId);
  }
  fclose(fprorder);
  fclose(fprotop);
}

void testOrder() {
  oTop++;
  order[oTop].orderId = oTop + 101;
  strcpy(order[oTop].firstName, "Tamanna");
  strcpy(order[oTop].lastName, "Khatun");
  strcpy(order[oTop].area, "Savar");
  strcpy(order[oTop].city, "Dhaka");
  strcpy(order[oTop].contactNum, "0123456789");
  order[oTop].totalItem = 2;
  strcpy(order[oTop].status, "incomplete");
  for (int i = 0; i < order[oTop].totalItem; i++) {
    scanf("%s", order[oTop].medName[i]);
    scanf("%d", &order[oTop].qty[i]);
  }
  orderInfoWrite();
}

// RECIEPT PART

typedef struct receipt {
  int RID;
  char cName[30];
  char cPhone[20];
  int items;
  char rDate[30];
  char rTime[20];
  char meds[30][50];
  double unitPrice[30];
  int units[30];
  double totalPrice;
} receipt;
receipt rec[10];
int rTop = -1;
void addReceipt() {
  int i = 0, med_id;
  rTop++;
  printf("Customer: ");
  scanf("%[^\n]%*c", rec[rTop].cName);
  printf("Phone: ");
  scanf("%[^\n]%*c", rec[rTop].cPhone);
  time_t currentTime;
  time(&currentTime);
  strcpy(rec[rTop].rDate, ctime(&currentTime));
  printf("Number of items: ");
  scanf("%d", &rec[rTop].items);
  while (i < rec[rTop].items) {
    printf("Item %d(MedID): ", i + 1);
    scanf("%d", &med_id);
    strcpy(rec[rTop].meds[i], drug[med_id - 101].brandName);
    rec[rTop].unitPrice[i] = drug[med_id - 101].pricePerUnit;
    printf("Units: ");
    scanf("%d", &rec[rTop].units[i]);
    rec[rTop].totalPrice += (rec[rTop].unitPrice[i] * rec[rTop].units[i]);
    i++;
  }
}
void displayReceipt() {
  system("clear");
  for (int i = 0; i <= rTop; i++) {
    printf("Date/Time: %s\n", rec[i].rDate);
    printf("Customer: %s\n", rec[i].cName);
    printf("Phone: %s\n", rec[i].cPhone);
    printf("\n___________________________________________\n");
    printf("item\t\t\tamount\t\t\tunit price\n");
    printf("\n___________________________________________\n");
    for (int j = 0; j < rec[i].items; j++) {
      printf("%s", rec[i].meds[j]);
      printf("\t\t\t\t%.2d", rec[i].units[j]);
      printf("\t\t\t\t%.2lf\n", rec[i].unitPrice[j]);
    }
    printf("\n___________________________________________\n");
    printf("\n\t\t\t\t\t\tTotal: %.2lf\n", rec[i].totalPrice);
  }
}
// void test() {
//   sTop++;
//   sup[sTop].supID = sTop + 101;
//   // sup[sTop].comName = "Beximco Pharma";
//   strcpy(sup[sTop].comName, "Beximco pharma");
//   strcpy(sup[sTop].salesMan, "orthee j.");
//   strcpy(sup[sTop].phnNum, "012312312");
//   strcpy(sup[sTop].email, "orth@gmail.com");
//   updatefileSup();
// }
int main() {
   loadAll();

 // orderInfoRead();
   //displayOrder();
  // system("clear");
  // AdminPanel();
  //testOrder();
  // orderInfoWrite();
  menu();

  return 0;
}