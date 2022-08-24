#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

const char *TB = " _-_-_-_-_-_-_-_-_\n";
const char *BB = " -_-_-_-_-_-_-_-_-\n";
const char *L = {"|"};
const char *R = {"|\n"};
typedef struct med {
  int MedID;
  char brandName[100];
  char genericName[100];
  char manufacturingCompany[100];
  char dosageForm[30];
  char strength[30];
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
    fflush(stdin);
    scanf(" %[^\n]%*c", drug[top].brandName);
    printf("Generic name: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[top].genericName);
    printf("Manufacturing company: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[top].manufacturingCompany);
    printf("Dosage form: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[top].dosageForm);
    printf("Dose strength: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[top].strength);

    printf("Price/pack: ");
    fflush(stdin);
    scanf("%lf", &drug[top].pricePerPack);
    printf("Price/unit: ");
    fflush(stdin);
    scanf("%lf", &drug[top].pricePerUnit);

    printf("In stock: ");
    fflush(stdin);
    scanf("%d", &drug[top].inStock);

    printf("Indications: ");
    fflush(stdin);
    scanf(" %[^\n]%*c", drug[top].indications);
    fflush(stdin);

    printf("\n");
    updateFile();
  } else
    printf("Maximum stack size reached\n");
}
void loadAll() {

  FILE *fpr, *ftop;
  ftop = fopen("top.dat", "r");
  fpr = fopen("medinfo.dat", "r");
  if (fpr == NULL || ftop == NULL) {
    fprintf(stderr, "Error while opening file!");
    exit(1);
  }
  fscanf(ftop, "%d", &top);
  int i = 0;
  int err = 0;
  printf("loading data....\n");
  // delay(2000);
  printf("\ntop index is %d\n", top);
  while (i <= top) {

    err += fscanf(fpr, MED_DATA_FORMAT_IN, &drug[i].MedID, drug[i].brandName,
                  drug[i].genericName, drug[i].manufacturingCompany,
                  drug[i].dosageForm, drug[i].strength, &drug[i].pricePerPack,
                  &drug[i].pricePerUnit, &drug[i].inStock, drug[i].indications);
    i++;
  }
  printf("\n%d data loaded\n\n", err / 9);
  fclose(ftop);
  fclose(fpr);
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
int returnToMain() { return 0; }
void search() {
  char key[100];
  char const *back = "0";
  int count;
mac:
  count = 0;
  printf("Input the search key (case sensitive, 0 to return): ");
  fflush(stdin);
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
    fflush(stdin);
    scanf(" %[^\n]%*c", drug[i].brandName);
    break;
  case 2:
    printf("Generic name: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[i].genericName);
  case 3:
    printf("Manufacturing company: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[i].manufacturingCompany);
    break;
  case 4:
    printf("Dosage form: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[i].dosageForm);
    break;
  case 5:
    printf("Dose strength: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[i].strength);
    break;
  case 6:
    printf("Price/pack: ");
    fflush(stdin);
    scanf("%lf", &drug[i].pricePerPack);
    break;
  case 7:
    printf("Price/unit: ");
    fflush(stdin);
    scanf("%lf", &drug[i].pricePerUnit);
    break;
  case 8:
    printf("In stock: ");
    fflush(stdin);
    scanf("%d", &drug[i].inStock);
    break;
  case 9:
    printf("Indications: ");
    fflush(stdin);
    scanf(" %[^\n]%*c", drug[i].indications);
    fflush(stdin);
    break;
  }
  updateFile();
	
}
int main() {
  loadAll();

  int choice;
  while (choice != 0) {
    printf("%s", TB);
    printf("%s", L);
    printf("1.Add		      ");
    printf("%s", R);
    printf("%s", L);
    printf("2.Remove	      ");
    printf("%s", R);
    printf("%s", L);
    printf("3.Edit		      ");
    printf("%s", R);
    printf("%s", L);
    printf("4.Display all    ");
    printf("%s", R);
    printf("%s", L);
    printf("5.Search 	      ");
    printf("%s", R);
    printf("%s", L);
    printf("6.Clear screen   ");
    printf("%s", R);
    //   printf("6.Sells\n");
    //   printf("7.Dealers\n");
    printf("%s", L);
    printf("0.Logout	      ");
    printf("%s", R);
    printf("%s", BB);
    // printf("%s", L);
    printf("Option: ");
    // printf("%s", R);
    // printf("%s", TB);
    fflush(stdin);
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addNew();
      break;
    case 2:
      delData();
      break;
    case 3:
      editData();
      break;
    case 4:
      display();
      break;
    case 5:
      search();
      break;
    case 6:
      system("clear");
      break;
      //   case 7:
      //     break;
    case 0:
      printf("Logging out......\n");
      // delay(2000);
      exit(0);
      break;
    }
    //  fflush(stdin);
  }
  // display();
  // addNew();
  // search();
  // display();
  return 0;
}