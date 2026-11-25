/*
 * Inventory Management System
 * Team 1
 * Concepts: Arrays, Structures, File Handling
 */
#include <stdio.h>
#include <string.h>

struct Item {
    int code;
    char name[40];
    int quantity;
    double unitPrice;
};

void addItem() {
    FILE *fp = fopen("inventory.dat", "ab");
    if (!fp) return;
    struct Item it;
    printf("\nEnter Product Code: ");
    scanf("%d", &it.code);
    getchar();
    printf("Product Name: ");
    fgets(it.name, sizeof(it.name), stdin);
    it.name[strcspn(it.name, "\n")] = 0;
    printf("Quantity in Stock: ");
    scanf("%d", &it.quantity);
    printf("Unit Price ($): ");
    scanf("%lf", &it.unitPrice);
    fwrite(&it, sizeof(struct Item), 1, fp);
    fclose(fp);
    printf(">> Product added to stock.\n");
}

void showInventory() {
    FILE *fp = fopen("inventory.dat", "rb");
    if (!fp) { printf("Inventory file is empty.\n"); return; }
    struct Item it;
    printf("\n======================== CURRENT INVENTORY ========================\n");
    printf("%-8s %-25s %-12s %-12s %-12s\n", "Code", "Name", "Stock", "Price", "Total Value");
    printf("-------------------------------------------------------------------\n");
    while (fread(&it, sizeof(struct Item), 1, fp)) {
        printf("%-8d %-25s %-12d $%-11.2f $%-11.2f\n",
               it.code, it.name, it.quantity, it.unitPrice, it.quantity * it.unitPrice);
    }
    printf("===================================================================\n");
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n--- INVENTORY MANAGER ---\n1. Add Stock Item\n2. View Inventory Report\n3. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1 || choice == 3) break;
        if (choice == 1) addItem();
        else if (choice == 2) showInventory();
    }
    return 0;
}
