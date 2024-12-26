#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include<stdbool.h>

// Initialize the inventory
void initInventory(Inventory *inventory) {
    inventory->capacity = 10;  // Initial capacity
    inventory->count = 0;
    inventory->items = (Item *)malloc(sizeof(Item) * inventory->capacity);
    if (inventory->items == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

// Resize the inventory when it reaches capacity
void resizeInventory(Inventory *inventory) {
    inventory->capacity *= 2;
    inventory->items = (Item *)realloc(inventory->items, sizeof(Item) * inventory->capacity);
    if (inventory->items == NULL) {
        printf("Memory allocation failed during resize!\n");
        exit(1);
    }
}

// Add an item to the inventory
bool addItem(Inventory *inventory, int id, char name[], int quantity, float price) {
    if (inventory->count >= inventory->capacity) {
        resizeInventory(inventory);  // Resize if capacity is full
    }

    Item newItem;
    newItem.id = id;
    strncpy(newItem.name, name, MAX_NAME_LENGTH - 1);
    newItem.name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
    newItem.quantity = quantity;
    newItem.price = price;

    inventory->items[inventory->count] = newItem;
    inventory->count++;
    return true;
}

// Search for an item by ID, return index or -1 if not found
int searchItem(const Inventory *inventory, int id) {
    for (int i = 0; i < inventory->count; i++) {
        if (inventory->items[i].id == id) {
            return i;  // Return the index of the found item
        }
    }
    return -1;  // Item not found
}

// Update an item in the inventory by index
void updateItem(Inventory *inventory, int index, char name[], int quantity, float price) {
    if (index >= 0 && index < inventory->count) {
        strncpy(inventory->items[index].name, name, MAX_NAME_LENGTH - 1);
        inventory->items[index].name[MAX_NAME_LENGTH - 1] = '\0';
        inventory->items[index].quantity = quantity;
        inventory->items[index].price = price;
    }
}

// Delete an item from the inventory by index
void deleteItem(Inventory *inventory, int index) {
    if (index >= 0 && index < inventory->count) {
        for (int i = index; i < inventory->count - 1; i++) {
            inventory->items[i] = inventory->items[i + 1];
        }
        inventory->count--;
    }
}

// Calculate the total value of the inventory
float calculateTotalValue(const Inventory *inventory) {
    float total = 0.0;
    for (int i = 0; i < inventory->count; i++) {
        total += inventory->items[i].quantity * inventory->items[i].price;
    }
    return total;
}

// Free the memory allocated for the inventory
void freeInventory(Inventory *inventory) {
    free(inventory->items);
    inventory->items = NULL;
    inventory->count = 0;
    inventory->capacity = 0;
}
