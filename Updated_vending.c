#include <stdio.h>
#include <string.h>

// Define structure for items in the vending machine
struct Item {
    char name[50];
    float price;
    int quantity;
};

// Function to buy an item from the vending machine
void buyItem(struct Item items[], int numItems, char itemName[], float money, float quantities) {
    FILE *receiptFile;
    receiptFile = fopen("receipt.txt", "w+"); // Open file in read and write mode

    int i;
    for (i = 0; i < numItems; i++) {
        if (strcmp(items[i].name, itemName) == 0) {
            if (quantities <= items[i].quantity && items[i].quantity > 0 && money >= items[i].price*quantities) {
                fprintf(receiptFile, "Item: %s - Quantity: %.0f - Price: $%.2f\n", items[i].name, quantities, items[i].price);
                float totalPrice = items[i].price * quantities;
                money = money -totalPrice;
                items[i].quantity = items[i].quantity - quantities;
                fprintf(receiptFile, "Total money used: $%.2f\n", totalPrice);
                fprintf(receiptFile, "Your change: $%.2f\n", money);
                fclose(receiptFile);
                printf("You bought %.0f %s for $%.2f\n", quantities, items[i].name, totalPrice);
                printf("Your change: $%.2f\n", money);
                return;
            } else if (money < items[i].price) {
                printf("Insufficient funds\n");
                fclose(receiptFile);
                return;
            } else {
                printf("Sorry, either %s is out of stock or the number of %s purchased exceeds the stock limit\n", items[i].name, items[i].name);
                fclose(receiptFile);
                return;
            }
        }
    }
    printf("Item not found\n");
    fclose(receiptFile);
}

int main() {
    // Initialize items in the vending machine
    struct Item items[] = {
        {"Soda", 1.50, 10},
        {"Chips", 1.00, 15},
        {"Candy", 0.75, 20}
    };
    
    int numItems = sizeof(items) / sizeof(items[0]);
    
    char itemName[50], choose[2];
    float money, quantity;
    int flag = 1;

    while (flag) {
        printf("Available items:\n");
        for (int i = 0; i < numItems; i++) {
            printf("%s - $%.2f - %d\n", items[i].name, items[i].price, items[i].quantity);
        }

        printf("\nEnter the name of the item you want to buy: ");
        scanf("%s", itemName);

        printf("\nEnter the amount of item you want to purchase: ");
        scanf("%f", &quantity);

        printf("Enter the amount of money you have:");
        scanf("%f", &money);

        buyItem(items, numItems, itemName, money, quantity);
        printf("Press N to discountinue: ");
        scanf(" %s", choose);
        if (strcmp(choose, "N") == 0 || strcmp(choose, "n") == 0) {
            flag = 0;
        }
    }
    return 0;
}
