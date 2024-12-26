#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include <stdbool.h>
// Include the inventory header file

int main() {
    int choice, id, quantity, index;
    float price;
    char name[MAX_NAME_LENGTH];
    Inventory inventory;

    initInventory(&inventory);

    do {
        printf("\n----- Inventory Management System -----\n");
        printf("1. Add Item\n");
        printf("2. View Inventory\n");
        printf("3. Search Item by Id\n");
        printf("4. Update Item by Id\n");
        printf("5. Delete Item by Id\n");
        printf("6. Calculate Total Value\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item ID: ");
                scanf("%d", &id);
                printf("Enter item name: ");
                scanf(" %[^\n]", name);  // To allow spaces in the name
                printf("Enter item quantity: ");
                scanf("%d", &quantity);
                printf("Enter item price: ");
                scanf("%f", &price);

                if (addItem(&inventory, id, name, quantity, price)) {
                    printf("Item added successfully.\n");
                }
                break;

            case 2:
                if (inventory.count == 0) {
                    printf("Inventory is empty!\n");
                } else {
                    printf("\n--- Inventory ---\n");
                    for (int i = 0; i < inventory.count; i++) {

                        printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n",
                               inventory.items[i].id,
                               inventory.items[i].name,
                               inventory.items[i].quantity,
                               inventory.items[i].price);
                    }
                }
                break;

            case 3:
                printf("Enter item ID to search: ");
                scanf("%d", &id);
                index = searchItem(&inventory, id);
                if (index != -1) {
                    printf("Found Item - ID: %d, Name: %s, Quantity: %d, Price: %.2f\n",
                           inventory.items[index].id,
                           inventory.items[index].name,
                           inventory.items[index].quantity,
                           inventory.items[index].price);
                } else {
                    printf("Item with ID %d not found.\n", id);
                }
                break;

            case 4:
                printf("Enter item ID to update: ");
                scanf("%d", &id);
                index = searchItem(&inventory, id);
                if (index != -1) {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", name);
                    printf("Enter new quantity: ");
                    scanf("%d", &quantity);
                    printf("Enter new price: ");
                    scanf("%f", &price);
                    updateItem(&inventory, index, name, quantity, price);
                    printf("Item updated successfully.\n");
                } else {
                    printf("Item with ID %d not found.\n", id);
                }
                break;

            case 5:
                printf("Enter item ID to delete: ");
                scanf("%d", &id);
                index = searchItem(&inventory, id);
                if (index != -1) {
                    deleteItem(&inventory, index);
                    printf("Item with ID %d deleted successfully.\n", id);
                } else {
                    printf("Item with ID %d not found.\n", id);
                }
                break;

            case 6:
                printf("Total value of inventory: %.2f\n", calculateTotalValue(&inventory));
                break;

            case 7:
                freeInventory(&inventory);

                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
