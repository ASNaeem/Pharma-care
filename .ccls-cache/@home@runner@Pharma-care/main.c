#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
const char *MED_DATA_FORMAT_IN =
    "{\"Brand name\": \"%[^\"]\", \"Generic name\": \"%[^\"]\", "
    "\"Manufacturer\": \"%[^\"]\", \"Dosage form\": \"%[^\"]\", \"Strength\": "
    "\"%[^\"]\", \"Price/Pack\": %lf, \"Price/Unit\": %lf, \"In stock\": "
    "%d, "
    "\"Indications\": \"%[^\"]\"}\n";
const char *MED_DATA_FORMAT_OUT =
    "{\"Brand name\": \"%s\", \"Generic name\": \"%s\", \"Manufacturer\": "
    "\"%s\", \"Dosage form\": \"%s\", \"Strength\": \"%s\", \"Price/Pack\": "
    "%lf, \"Price/Unit\": %lf, \"In stock\": %d, \"Indications\": \"%s\"}\n";
const char *MED_DATA_FORMAT_CONSOLE = {
    "Brand name: %s\nGeneric name: %s\nManufacturer: %s\nDosage form: "
    "%s\nStrength: %s\nPrice/Pack: %.2lf\nPrice/Unit: %.2lf\nIn stock: "
    "%d\nIndications: %s\n\n"};
typedef struct med {
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
void addToFile() {
  FILE *fpwrite, *fptop;
  fpwrite = fopen("medinfo.dat", "w");
  fptop = fopen("top.dat", "w");
  if (fpwrite == NULL || fptop == NULL) {
    printf("Failed to write!\n");
    exit(1);
  }
  int err = 0, i = 0;
  while (i <= top) {
    err += fprintf(fpwrite, MED_DATA_FORMAT_OUT, drug[i].brandName,
                   drug[i].genericName, drug[i].manufacturingCompany,
                   drug[i].dosageForm, drug[i].strength, drug[i].pricePerPack,
                   drug[i].pricePerUnit, drug[i].inStock, drug[i].indications);
    i++;
  }
  fprintf(fptop, "%d", top);
  if (err != 0)
    printf("\nData saved!");
  fclose(fptop);
  fclose(fpwrite);
}
void addNew() {
  if (top <= MAX) {
    top++;
    printf("Brand name: ");
    fflush(stdin);
    scanf("%[^\n]%*c", drug[top].brandName);
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
    addToFile();
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
  printf("\ntop index: %d\n", top);
  while (i <= top) {

    err += fscanf(fpr, MED_DATA_FORMAT_IN, drug[i].brandName,
                  drug[i].genericName, drug[i].manufacturingCompany,
                  drug[i].dosageForm, drug[i].strength, &drug[i].pricePerPack,
                  &drug[i].pricePerUnit, &drug[i].inStock, drug[i].indications);
    i++;
  }
  printf("data read: %d\n", err / 9);
  fclose(ftop);
  fclose(fpr);
}

void display() {
  int i = 0;
  while (i <= top) {
    printf(MED_DATA_FORMAT_CONSOLE, drug[i].brandName, drug[i].genericName,
           drug[i].manufacturingCompany, drug[i].dosageForm, drug[i].strength,
           drug[i].pricePerPack, drug[i].pricePerUnit, drug[i].inStock,
           drug[i].indications);
    i++;
  }
}
int returnToMain() { return 0; }
void search() {
  char key[100];
  char const *string = "some value of string";
	char const *back = "0";
mac:
printf("Input the search key (0 to return): ");
  scanf("%[^\n]%*c", key);
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
        printf(MED_DATA_FORMAT_CONSOLE, drug[i].brandName, drug[i].genericName,
               drug[i].manufacturingCompany, drug[i].dosageForm,
               drug[i].strength, drug[i].pricePerPack, drug[i].pricePerUnit,
               drug[i].inStock, drug[i].indications);
      }
    }
  }
}
int main() {
  loadAll();

  int choice;
  // while (choice != 0) {
  //   printf("1.Create a new medicine data\n");
  //   printf("2.Remove a medicine data\n");
  //   printf("3.Update an old medicine data\n");
  //   printf("4.Display all medicine data\n");
  //   printf("5.Search a medicine data\n");
  //   printf("6.Sells\n");
  //   printf("7.Dealers\n");
  //   printf("0.Logout\n\n");

  //   printf("Option: ");
  //  fflush(stdin);
  //   scanf("%d", &choice);
  //   printf("\n");
  //   switch (choice) {
  //   case 1: addNew();
  //     break;
  //   case 2:
  //     break;
  //   case 3:
  //     break;
  //   case 4:
  //     display();
  //     break;
  //   case 5:
  //     break;
  //   case 6:
  //     break;
  //   case 7:
  //     break;
  //   case 0:
  //     printf("Logging out\n");
  //     exit(1);
  //     break;
  //   }
  //  fflush(stdin);
  // }
  // display();
  // addNew();
  search();
 // display();
  return 0;
}