#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif  // _WIN32

// TODO make this clean code; this is very ugly

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 28

struct Gold {
    int spa;
    int laundry;
    int bar;
    int massage;
};

struct Silver {
    int lunch;
    int dinnner;
    int laundry;
    int additionalBed;
};

struct Bronze {
    int breakFast;
    int carParking;
    int hotWater;
};

struct Bill {
    char name[25];
    char id[25];
    char address[25];
    char contactNo[25];
    int numberOfDays;
    int selectedSuitType;
    void *selectedSuit;
};

void clearScreen();

void getIntInput(int *input, char *prompt, int space);
void getStringInput(char input[], char *prompt, int space);

void printBillStruct(struct Bill *bill, int initialSpace, int inBetweenSpace);

void initializeBillStructWithZeros(struct Bill *userBill);

void getCustomerDetails(struct Bill *userBill);

void printGoldSuitWithoutCost(int space, int n);
void printSilverSuitWithoutCost(int space, int n);
void printBronzeSuitWithoutCost(int space, int n);

void getGoldDetails(struct Bill *userBill, struct Gold *goldStruct);

void getSuit(struct Bill *userBill);

void printSpaces(int count);

int main() {
    struct Bill userBill;

    initializeBillStructWithZeros(&userBill);

    printBillStruct(&userBill, 1, 14);

    getCustomerDetails(&userBill);

    getSuit(&userBill);

    switch (userBill.selectedSuitType) {
        case 1: {
            struct Gold goldStruct;
            getGoldDetails(&userBill, &goldStruct);
            break;
        }

            /* case 2:
            struct Gold silverStruct;
            getSilverDetails(,&silverStruct);
            break;

        case 3:
            struct Gold bronzeStruct;
            getBronzeDetails(,&bronzeStruct);
            break; */

        default:
            printf("Something went wrong");
            exit(0);
            break;
    }

    return 0;
}

void getSuit(struct Bill *userBill) {
    printBillStruct(userBill, 1, 14);
    printGoldSuitWithoutCost(5, 1);
    printf("\n");
    printSilverSuitWithoutCost(5, 2);
    printf("\n");
    printBronzeSuitWithoutCost(5, 3);
    printf("\n\n");
    printf("Enter Suit (1,2,3): ");
    scanf("%d", &(userBill->selectedSuitType));
}

void printGoldSuitWithoutCost(int space, int n) {
    int subListSpace = space + 2;
    printSpaces(space);
    printf("%d.Gold ", n);
    printf("\n");
    printSpaces(subListSpace);
    printf("-spa");
    printf("\n");
    printSpaces(subListSpace);
    printf("-laundry");
    printf("\n");
    printSpaces(subListSpace);
    printf("-bar");
    printf("\n");
    printSpaces(subListSpace);
    printf("-massage");
    printf("\n");
}

void printGoldSuitWithCost(int space, struct Gold *gold) {
    int subListSpace = space + 2;
    printSpaces(space);
    printf("Gold");
    printf("\n");
    printSpaces(subListSpace);
    printf("-spa %d", gold->spa);
    printf("\n");
    printSpaces(subListSpace);
    printf("-laundry %d", gold->laundry);
    printf("\n");
    printSpaces(subListSpace);
    printf("-bar %d", gold->bar);
    printf("\n");
    printSpaces(subListSpace);
    printf("-massage %d", gold->massage);
    printf("\n");
    printf("\n");
}

void initilizeGoldStruct(struct Gold *goldStruct) {
    goldStruct->bar = 0;
    goldStruct->laundry = 0;
    goldStruct->massage = 0;
    goldStruct->spa = 0;
}

void getGoldDetails(struct Bill *userBill, struct Gold *goldStruct) {
    int n = 0;
    initilizeGoldStruct(goldStruct);

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithCost(5, goldStruct);
    getIntInput(&n, "Spa for Nights (Zero for None): ", 5);
    goldStruct->spa = n * 500;

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithCost(5, goldStruct);
    getIntInput(&n, "Laundry for Nights (Zero for None): ", 5);
    goldStruct->laundry = n * 300;

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithCost(5, goldStruct);
    getIntInput(&n, "Bar for Nights (Zero for None): ", 5);
    goldStruct->bar = n * 5000;

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithCost(5, goldStruct);
    getIntInput(&n, "Massage for person (Zero for None): ", 5);
    goldStruct->massage = n * 2000;

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithCost(5, goldStruct);
}

void printSilverSuitWithoutCost(int space, int n) {
    int subListSpace = space + 2;
    printSpaces(space);
    printf("%d.Silver ", n);
    printf("\n");
    printSpaces(subListSpace);
    printf("-lunch");
    printf("\n");
    printSpaces(subListSpace);
    printf("-dinner");
    printf("\n");
    printSpaces(subListSpace);
    printf("-laundry");
    printf("\n");
    printSpaces(subListSpace);
    printf("-additionalBed");
    printf("\n");
}

void printBronzeSuitWithoutCost(int space, int n) {
    int subListSpace = space + 2;
    printSpaces(space);
    printf("%d.Bronze ", n);
    printf("\n");
    printSpaces(subListSpace);
    printf("-breakfast");
    printf("\n");
    printSpaces(subListSpace);
    printf("-carParking");
    printf("\n");
    printSpaces(subListSpace);
    printf("-hotWater");
    printf("\n");
}

void getCustomerDetails(struct Bill *userBill) {
    getStringInput(userBill->name, "Enter Name: ", 5);
    printBillStruct(userBill, 1, 14);

    getStringInput(userBill->id, "Enter Id: ", 5);
    printBillStruct(userBill, 1, 14);

    getStringInput(userBill->address, "Enter Address: ", 5);
    printBillStruct(userBill, 1, 14);

    getStringInput(userBill->contactNo, "Enter Contact No: ", 5);
    printBillStruct(userBill, 1, 14);

    getIntInput(&(userBill->numberOfDays), "Enter Number of days: ", 5);
    printBillStruct(userBill, 1, 14);
}

void initializeBillStructWithZeros(struct Bill *userBill) {
    strcpy(userBill->name, "---");
    strcpy(userBill->id, "---");
    strcpy(userBill->address, "---");
    strcpy(userBill->contactNo, "---");
    userBill->numberOfDays = 0;
    userBill->selectedSuitType = -1;
    userBill->selectedSuit = NULL;
}

void printBillStruct(struct Bill *bill, int initialSpace, int inBetweenSpace) {
    clearScreen();

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("      Name: %s", bill->name);
    printSpaces(inBetweenSpace);
    printf("              Id: %s", bill->id);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("   Address: %s", bill->address);
    printSpaces(inBetweenSpace);
    printf("      Contact No: %s", bill->contactNo);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("No of days: %d", bill->numberOfDays);
    printSpaces(inBetweenSpace);
    printf("Selected Suit Type: %d", bill->selectedSuitType);

    printf("\n");
    printf("\n");
}

void getIntInput(int *input, char *prompt, int space) {
    printSpaces(space);
    printf("%s", prompt);
    scanf("%d", input);
}

void getStringInput(char input[], char *prompt, int space) {
    printSpaces(space);
    printf("%s", prompt);
    scanf("%s", input);
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
    fflush(stdout);
}

void clearScreen() {
    printf("\033[0;0H");
    for (int i = 0; i < TERMINAL_HEIGHT; i++) {
        for (int j = 0; j < TERMINAL_WIDTH; j++) {
            printf(" ");
        }
        printf("\n");
    }
    printf("\033[0;0H");
    fflush(stdout);
}

void sleepcp(int milliseconds)  // Cross-platform sleep function
{
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif  // _WIN32
}