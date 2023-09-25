#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define NAME_LENGTH 30
#define MAX_PARTS 100

typedef struct{
    int number;
    char name[NAME_LENGTH];
    float price;
    int quantity;
}part;

// Global variable to keep track the number of the parts in inventory
int parts_count = 0;

void insert(part *inventory);
void search(part *inventory);
void update(part *inventory);
void print(part *inventory);
int read_line(char *str, int n);
bool check_inventory(part *inventory, int part_number);
int compare_parts(const void *p, const void *q);

int main(){
    part inventory[MAX_PARTS]; // Creating inventory with max 100 parts;
    char OC;

    while(1){
        printf("\nEnter operation code: ");
        scanf(" %c", &OC); // Gets operation Code

        switch(OC){
            case 'i':
            case 'I':
                insert(inventory);
                break;
            case 's':
            case 'S':
                search(inventory);
                break;
            case 'u':
            case 'U':
                update(inventory);
                break;
            case 'p':
            case 'P':
                print(inventory);
                break;
            case 'q':
            case 'Q':
                printf("Exiting the program...");
                return 1;
            default:
                printf("Illegal code\n");
        }
    }
    return 0;
}

void insert(part *inventory){
    // Function to insert part into the inventory.
    char length;
    part new_part;

    printf("Enter part number: "); // Getting new part`s part number
    scanf(" %d", &new_part.number);
    while ((getchar()) != '\n');

    printf("Enter part name: "); // Getting new part`s name
    read_line(new_part.name, NAME_LENGTH);

    printf("Enter price: "); // Getting new part`s price
    scanf(" %f", &new_part.price);

    printf("Quantity on hand: "); // Getting new part`s quantity
    scanf(" %d", &new_part.quantity);

    //checks if the part already exist or the database is full -->
    if(parts_count >= MAX_PARTS || check_inventory(inventory, new_part.number) == false){
        return;
    }

    inventory[parts_count] = new_part; // Assigning part to the inventory.
    parts_count++;
}

void search(part *inventory){
    // Function to search for a part in the inventory by its part number.
    int part_number;

    printf("Enter part number: ");
    scanf(" %d", &part_number);

    for(int i = 0; i < parts_count; i++){ 
        if(inventory[i].number == part_number){ // checks if anything in inventory`s part number matches the part_number given by the user 
            printf("Part name: %s\n", inventory[i].name);
            printf("Price: $%.2f\n", inventory[i].price);
            printf("Quantity on hand: %d\n", inventory[i].quantity);
            return; // returns, because there is nothing else left to do
        }
    }
    printf("Part not found.\n"); // if nothing matched with part number prints this
}

void update(part *inventory){
    // Function to update a part`s quantity in the inventory by its part number.
    int part_number, change;

    printf("Enter part number: ");
    scanf(" %d", &part_number);

    for(int i = 0; i < parts_count; i++){
        if(inventory[i].number == part_number){
            printf("Enter change in quantity on hand: ");
            scanf(" %d", &change);
            inventory[i].quantity += change;
            return;
        }
    }
    printf("Part not found.\n");
}

void print(part *inventory){
    // Function to print the inventory.
    qsort(inventory, parts_count, sizeof(part), compare_parts);
    printf("PART NUMBER\tPART NAME\t\t\tPRICE\tQUANTITY ON HAND\n");
    printf("-------------------------------------------------------------------------\n");
    for(int i = 0; i < parts_count; i++){
        part current_part = inventory[i];
        printf("%-12d\t%-30s\t$%-8.2f\t%d\n", current_part.number, current_part.name, current_part.price, current_part.quantity);
        // Numbers in printf which has - in front of them makes left justified to make output better. it alligns them in a line with \t, so it just looks better.
    }
}

int read_line(char str[], int n){
    int ch, i = 0; 
    while (isspace(ch = getchar())) // Read characters until a non white space character is found
        ; // Discards the white space char
    
    // Read characters until the end of line
    while (ch != '\n') {
        if (i < n)
            str[i++] = ch; // Store the character in the array and increase the index
        ch = getchar(); // Read the next character
    }
    str[i] = '\0'; // Add the null terminator to the end of the string
    return i; // Return the length of the string
}

bool check_inventory(part *inventory, int part_number){
    // Checks inventory if it has the same part_number, if it has gives an error mesage and returns false
    for(int i = 0; i < parts_count; i++){
        if(inventory[i].number == part_number){
            printf("The part number is already in the inventory, please update it or change the part number and try again.");
            return false;
        }
    }
    return true;
}

int compare_parts(const void *p, const void *q){
    // Casting the void pointers to pointers to type part, to get the actual parts -->
    const part *part1 = (const part *)p; 
    const part *part2 = (const part*)q;

    // Compare the prices of the two parts and return -1 if the first part's price is less than second part`s price, return 0 if equal to, return -1 if greater than the second part's price.
    if(part1->price < part2->price){
        return -1;
    }else if(part1->price > part2->price){
        return 1;
    }else{
        return 0;
    }
}