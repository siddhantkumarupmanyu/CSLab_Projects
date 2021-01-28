#include <stdbool.h>
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
#define TERMINAL_HEIGHT 30

struct Gold {
    bool spa;
    bool laundry;
    bool bar;
    bool massage;
};

struct Silver {
    bool lunch;
    bool dinner;
    bool laundry;
    bool additionalBed;
};

struct Bronze {
    bool breakFast;
    bool carParking;
    bool hotWater;
};

struct Bill {
    char name[25];
    char id[25];
    char address[25];
    char contactNo[25];
    int nights;
    int persons;
    int selectedSuitType;
    void *selectedSuit;
    int cost;
};

void clearScreen();

void getIntInput(int *input, char *prompt, int space);
void getStringInput(char input[], char *prompt, int space);

void printBillStruct(struct Bill *bill, int initialSpace, int inBetweenSpace);

void initializeBillStructWithZeros(struct Bill *userBill);

void getCustomerDetails(struct Bill *userBill);

void printGoldSuit(int space, int n);
void printSilverSuit(int space, int n);
void printBronzeSuit(int space, int n);

void printGoldSuitWithEnabledOptions(int space, struct Gold *gold);
void printSilverSuitWithEnabledOptions(int space, struct Silver *silver);
void printBronzeSuitWithEnabledOptions(int space, struct Bronze *bronze);

void getGoldDetails(struct Bill *userBill, struct Gold *goldStruct);
void getSilverDetails(struct Bill *userBill, struct Silver *silverStruct);
void getBronzeDetails(struct Bill *userBill, struct Bronze *bronzeStruct);

void getSuit(struct Bill *userBill);

void printSpaces(int count);

void calculateBill(struct Bill *userBill);

// it would be much easier to write if we used oop language

int main() {
    struct Bill userBill;

    initializeBillStructWithZeros(&userBill);

    printBillStruct(&userBill, 1, 14);

    getCustomerDetails(&userBill);

    getSuit(&userBill);

    struct Gold goldStruct;
    struct Silver silverStruct;
    struct Bronze bronzeStruct;

    switch (userBill.selectedSuitType) {
        case 1: {
            getGoldDetails(&userBill, &goldStruct);
            userBill.selectedSuit = &goldStruct;
            break;
        }

        case 2: {
            getSilverDetails(&userBill, &silverStruct);
            userBill.selectedSuit = &silverStruct;
            break;
        }

        case 3: {
            getBronzeDetails(&userBill, &bronzeStruct);
            userBill.selectedSuit = &bronzeStruct;
            break;
        }

        default:
            printf("Something went wrong");
            exit(0);
            break;
    }

    calculateBill(&userBill);

    printBillStruct(&userBill, 1, 14);

    switch (userBill.selectedSuitType) {
        case 1:
            printGoldSuitWithEnabledOptions(10, userBill.selectedSuit);
            break;
        case 2:
            printSilverSuitWithEnabledOptions(10, userBill.selectedSuit);
            break;
        case 3:
            printBronzeSuitWithEnabledOptions(10, userBill.selectedSuit);
            break;
    }

    return 0;
}
// lets suppose; days = nights - 1
void calculateBill(struct Bill *userBill) {
    int days = userBill->nights - 1;
    int cost = 0;
    if (userBill->selectedSuitType == 1) {  // gold case
        cost = 10000 * userBill->nights;
        struct Gold *goldStruct = (struct Gold *)userBill->selectedSuit;
        if (goldStruct->spa) {
            cost += 500 * userBill->nights;
        }
        if (goldStruct->laundry) {
            cost += 300 * userBill->nights;
        }
        if (goldStruct->bar) {
            cost += 5000 * userBill->nights;
        }
        if (goldStruct->massage) {
            cost += 2000 * userBill->persons;
        }
    } else if (userBill->selectedSuitType == 2) {  // silver case
        cost = 7000 * userBill->nights;
        struct Silver *silverStruct = (struct Silver *)userBill->selectedSuit;
        if (silverStruct->lunch) {
            cost += 250 * days * userBill->persons;
        }
        if (silverStruct->dinner) {
            cost += 350 * userBill->nights;
        }
        if (silverStruct->laundry) {
            cost += 150 * userBill->persons;
        }
        if (silverStruct->additionalBed) {
            cost += 1250 * userBill->nights;
        }
    } else if (userBill->selectedSuitType == 3) {  // bronze case
        cost = 4000 * userBill->nights;
        struct Bronze *bronzeStruct = (struct Bronze *)userBill->selectedSuit;
        if (bronzeStruct->breakFast) {
            cost += 100 * days * userBill->persons;
        }
        if (bronzeStruct->carParking) {
            cost += 50 * userBill->nights;
        }
        if (bronzeStruct->hotWater) {
            cost += 50 * userBill->persons * userBill->nights;
        }
    } else {
        printf("Something went wrong");
        exit(0);
    }
    userBill->cost = cost;
}

void getSuit(struct Bill *userBill) {
    printBillStruct(userBill, 1, 14);
    printGoldSuit(10, 1);
    printf("\n");
    printSilverSuit(10, 2);
    printf("\n");
    printBronzeSuit(10, 3);
    printf("\n\n");
    getIntInput(&(userBill->selectedSuitType), "Enter Suit (1,2,3): ", 5);
}

void printGoldSuit(int space, int n) {
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

void printGoldSuitWithEnabledOptions(int space, struct Gold *gold) {
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
    goldStruct->bar = false;
    goldStruct->laundry = false;
    goldStruct->massage = false;
    goldStruct->spa = false;
}

bool getOptInput(char *prompt, int spaces) {
    char ch;
    printSpaces(spaces);
    printf("%s (y/n): ", prompt);
    scanf(" %c", &ch);  // https://stackoverflow.com/a/13543113
    if (ch == 'y' | ch == 'Y') {
        return true;
    }
    return false;
}

void getGoldDetails(struct Bill *userBill, struct Gold *goldStruct) {
    int n = 0;
    initilizeGoldStruct(goldStruct);

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithEnabledOptions(10, goldStruct);
    goldStruct->spa = getOptInput("Spa", 5);

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithEnabledOptions(10, goldStruct);
    goldStruct->laundry = getOptInput("Laundry", 5);

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithEnabledOptions(10, goldStruct);
    goldStruct->bar = getOptInput("Bar", 5);

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithEnabledOptions(10, goldStruct);
    goldStruct->massage = getOptInput("Massage ", 5);

    printBillStruct(userBill, 1, 14);
    printGoldSuitWithEnabledOptions(10, goldStruct);
}

void printSilverSuit(int space, int n) {
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

void printSilverSuitWithEnabledOptions(int space, struct Silver *silver) {
    int subListSpace = space + 2;
    printSpaces(space);
    printf("Silver");
    printf("\n");
    printSpaces(subListSpace);
    printf("-lunch  %d", silver->lunch);
    printf("\n");
    printSpaces(subListSpace);
    printf("-dinner %d", silver->dinner);
    printf("\n");
    printSpaces(subListSpace);
    printf("-laundry %d", silver->laundry);
    printf("\n");
    printSpaces(subListSpace);
    printf("-additionalBed %d", silver->additionalBed);
    printf("\n");
    printf("\n");
}

void initilizeSilverStruct(struct Silver *silverStruct) {
    silverStruct->lunch = false;
    silverStruct->dinner = false;
    silverStruct->laundry = false;
    silverStruct->additionalBed = false;
}

void getSilverDetails(struct Bill *userBill, struct Silver *silverStruct) {
    int n = 0;
    initilizeSilverStruct(silverStruct);

    printBillStruct(userBill, 1, 14);
    printSilverSuitWithEnabledOptions(10, silverStruct);
    silverStruct->lunch = getOptInput("Lunch", 5);

    printBillStruct(userBill, 1, 14);
    printSilverSuitWithEnabledOptions(10, silverStruct);
    silverStruct->dinner = getOptInput("Dinner", 5);

    printBillStruct(userBill, 1, 14);
    printSilverSuitWithEnabledOptions(10, silverStruct);
    silverStruct->laundry = getOptInput("Laundry", 5);

    printBillStruct(userBill, 1, 14);
    printSilverSuitWithEnabledOptions(10, silverStruct);
    silverStruct->additionalBed = getOptInput("Additional Bed", 5);

    printBillStruct(userBill, 1, 14);
    printSilverSuitWithEnabledOptions(10, silverStruct);
}

void printBronzeSuit(int space, int n) {
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

void printBronzeSuitWithEnabledOptions(int space, struct Bronze *bronze) {
    int subListSpace = space + 2;
    printSpaces(space);
    printf("Bronze");
    printf("\n");
    printSpaces(subListSpace);
    printf("-breakfast %d", bronze->breakFast);
    printf("\n");
    printSpaces(subListSpace);
    printf("-carParking %d", bronze->carParking);
    printf("\n");
    printSpaces(subListSpace);
    printf("-hotWater %d", bronze->hotWater);
    printf("\n");
    printf("\n");
}

void initilizeBronzeStruct(struct Bronze *bronzeStruct) {
    bronzeStruct->breakFast = false;
    bronzeStruct->carParking = false;
    bronzeStruct->hotWater = false;
}

void getBronzeDetails(struct Bill *userBill, struct Bronze *bronzeStruct) {
    int n = 0;
    initilizeBronzeStruct(bronzeStruct);

    printBillStruct(userBill, 1, 14);
    printBronzeSuitWithEnabledOptions(10, bronzeStruct);
    bronzeStruct->breakFast = getOptInput("Breakfast", 5);

    printBillStruct(userBill, 1, 14);
    printBronzeSuitWithEnabledOptions(10, bronzeStruct);
    bronzeStruct->carParking = getOptInput("Car Parking", 5);

    printBillStruct(userBill, 1, 14);
    printBronzeSuitWithEnabledOptions(10, bronzeStruct);
    bronzeStruct->hotWater = getOptInput("Hot Water", 5);

    printBillStruct(userBill, 1, 14);
    printBronzeSuitWithEnabledOptions(10, bronzeStruct);
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

    getIntInput(&(userBill->nights), "Enter Number of Nights: ", 5);
    printBillStruct(userBill, 1, 14);

    getIntInput(&(userBill->persons), "Enter Number of Persons: ", 5);
    printBillStruct(userBill, 1, 14);
}

void initializeBillStructWithZeros(struct Bill *userBill) {
    strcpy(userBill->name, "---");
    strcpy(userBill->id, "---");
    strcpy(userBill->address, "---");
    strcpy(userBill->contactNo, "---");
    userBill->nights = 0;
    userBill->persons = 0;
    userBill->selectedSuitType = -1;
    userBill->selectedSuit = NULL;
    userBill->cost = 0;
}

void printBillStruct(struct Bill *bill, int initialSpace, int inBetweenSpace) {
    clearScreen();

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("   Name: %s", bill->name);
    printSpaces(inBetweenSpace);
    printf("        Id: %s", bill->id);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("Address: %s", bill->address);
    printSpaces(inBetweenSpace);
    printf("Contact No: %s", bill->contactNo);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf(" Nights: %d", bill->nights);
    printSpaces(inBetweenSpace);
    printf("      Person: %d", bill->persons);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("Selected Suit Type: %d", bill->selectedSuitType);
    printSpaces(inBetweenSpace);
    printf("Cost: ₹ %d", bill->cost);

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