#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif  // _WIN32

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 24

static char *car[] = {
    "          ___________",
    "  -  ----// --|||-- \\\\",
    " ---- __//____|||____\\\\____",
    "     | _|    \" | \"   --_  ||",
    " ----|/ \\______|______/ \\_||",
    "______\\_/_____________\\_/_______"};

static int carMaxLineLength = 33;

struct Bill {
    char driverName[25];
    char driverLicense[25];
    char taxiNumber[25];
    int distance;
    int fare;
};

void animateCar();

void clearScreen();

void printSpaces(int count);

void sleepcp(int milliseconds);

void printCar();

void getIntInput(int *input, char *prompt, int space);
void getStringInput(char input[], char *prompt, int space);

void printBillStruct(struct Bill bill, int initialSpace, int inBetweenSpace);

void initializeBillStructWithZeros(struct Bill userBill);

int main() {
    animateCar(40, TERMINAL_WIDTH);
    animateCar(40, TERMINAL_WIDTH);
    animateCar(40, (TERMINAL_WIDTH + carMaxLineLength) / 2);

    struct Bill userBill;

    initializeBillStructWithZeros(userBill);

    printBillStruct(userBill, 1, 8);

    getStringInput(userBill.driverName, "Enter Driver Name: ", 5);
    printBillStruct(userBill, 1, 8);

    getStringInput(userBill.driverLicense, "Enter Driver License: ", 5);
    printBillStruct(userBill, 1, 8);

    getStringInput(userBill.taxiNumber, "Enter Taxi Number: ", 5);
    printBillStruct(userBill, 1, 8);

    getIntInput(userBill.distance, "Enter Distance Traveled: ", 5);
    printBillStruct(userBill, 1, 8);

    printf("\n");
    return 0;
}

void initializeBillStructWithZeros(struct Bill userBill) {
    strcpy(userBill.driverName, "---");
    strcpy(userBill.driverLicense, "---");
    strcpy(userBill.taxiNumber, "---");
    userBill.distance = 0;
    userBill.fare = 0;
}

void printBillStruct(struct Bill bill, int initialSpace, int inBetweenSpace) {
    printSpaces(initialSpace);
    printf("Driver Name: %s", bill.driverName);
    printSpaces(inBetweenSpace);
    printf("Driver License Number: %s", bill.driverLicense);

    printSpaces(initialSpace);
    printf("Taxi Number: %s", bill.taxiNumber);
    printSpaces(inBetweenSpace);
    printf("Distance: %d", bill.distance);

    printSpaces(initialSpace);
    printf("Fare: %d", bill.fare);
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

void printCar(int spaces) {
    for (int i = 0; i < 6; i++) {
        printSpaces(spaces);
        printf("%s", car[i]);
        printf("\n");
    }
}

void animateCar(int sleepTime, int width) {
    int increament = 1;
    for (int j = carMaxLineLength, k = 0; j < width;) {
        sleepcp(sleepTime);
        clearScreen();
        printCar(k);
        k += increament;
        j += increament;
    }
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