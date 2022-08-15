#include <stdio.h>
#include <string.h>
int top = -1;
// const char MED_DATA_FORMAT_IN = "{Brand name: %s\nGeneric name:
// %s\nManufaacturer: %s\nDosage form: %s\n}\n";
typedef struct med {
  char brandName[20];
  char genericName[20];
  char manufacturingCompany[30];
  char dosageForm[20];
  char strength[10];
  double pricePerPack;
  double pricePerUnit;
  int inStock;
  char indications[300];
} med;
med drug[10];
void addNew() {
  top++;
  printf("Brand name: ");
  scanf("%20[^\n]%*c", drug[top].brandName);
  printf("Generic name: ");
  scanf("%20[^\n]%*c", drug[top].genericName);
  printf("Manufacturing company: ");
  scanf("%20[^\n]%*c", drug[top].manufacturingCompany);
  printf("Dosage form: ");
  scanf("%20[^\n]%*c", drug[top].dosageForm);
  printf("Dose strength: ");
  scanf("%20[^\n]%*c", drug[top].strength);

  printf("Price/unit: ");
  scanf("%lf", &drug[top].pricePerUnit);
  printf("Price/pack: ");
  scanf("%lf", &drug[top].pricePerPack);
  printf("In stock: ");
  scanf("%d", &drug[top].inStock);

  printf("Indications: ");
  scanf(" %300[^\n]%*c", drug[top].indications);
  printf("\n\n");
}
void display() {
  if (top < 0) {
    printf("List is empty\n");
  }
  for (int i = 0; i <= top; i++) {
    printf("Brand name: %s\n", drug[i].brandName);
    printf("Generic name: %s\n", drug[i].genericName);
    printf("Manufacturer: %s\n", drug[i].manufacturingCompany);
    printf("Dosage form: %s\n", drug[i].dosageForm);
    printf("Strength: %s\n", drug[i].strength);
    printf("Price/unit: %.2lf\n", drug[i].pricePerUnit);
    printf("Price/pack: %.2lf\n", drug[i].pricePerPack);
    printf("In stock: %d\n", drug[i].inStock);
    printf("Indications: %s\n", drug[i].indications);
    printf("\n\n");
  }
}
int main() {
  top++;
  strcpy(drug[top].brandName, "Napa");
  strcpy(drug[top].genericName, "Paracetamol");
  strcpy(drug[top].manufacturingCompany, "Beximco Pharmaceuticals Ltd.");
  strcpy(drug[top].dosageForm, "Tablet");
  strcpy(drug[top].strength, "500mg");
  drug[top].pricePerUnit = 20;
  drug[top].pricePerPack = 220;
  drug[top].inStock = 50;
  strcpy(drug[top].indications, "Used for Fever and cold");
  display();
  addNew();
  display();
  return 0;
}