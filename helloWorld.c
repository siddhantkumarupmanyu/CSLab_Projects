#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif  // _WIN32

// TODO make this clean code; this is very ugly

#define TERMINAL_WIDTH 80
#define TERMINAL_HEIGHT 24

static char *car[] = {
    "          ___________",
    "  -  ----// --|||-- \\\\",
    " ---- __//____|||____\\\\____",
    "     | _|    \" | \"   --_  ||",
    " ----|/ \\______|______/ \\_||",
    "______\\_/_____________\\_/_______"};

static const int carMaxLineLength = 33;

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

void printBillStruct(struct Bill *bill, int initialSpace, int inBetweenSpace);

void initializeBillStructWithZeros(struct Bill *userBill);

int calculateTax(int fare, int percentage) {
    return (percentage * fare) / 100.0;
}

int calculateFare(int distance) {
    if (distance == 0) {
        return 0;
    }
    int fare = 1000;
    if (distance <= 10) {
        fare += distance * 15;
        fare += calculateTax(fare, 18);
        return fare;
    }
    fare += 10 * 15;  // for first 10 km
    distance = distance - 10;

    if (distance <= 50) {
        fare += distance * 14;
        fare += calculateTax(fare, 18);
        return fare;
    }
    fare += 50 * 14;  // for next 50 km
    distance = distance - 50;

    if (distance <= 100) {
        fare += distance * 12;
        fare += calculateTax(fare, 18);
        return fare;
    }
    fare += 100 * 12;  // for next 100 km
    distance = distance - 100;

    if (distance <= 500) {
        fare += distance * 10;
        fare += calculateTax(fare, 18);
        return fare;
    }
    fare += 500 * 10;  // for next 500 km
    distance = distance - 500;

    if (distance <= 1000) {
        fare += distance * 9;
        fare += calculateTax(fare, 18);
        return fare;
    }
    fare += 1000 * 9;  // for next 1000 km
    distance = distance - 1000;

    fare += distance * 8;  // remaining distance
    fare += calculateTax(fare, 18);
    return fare;
}

int main() {
    animateCar(40, TERMINAL_WIDTH);
    animateCar(40, TERMINAL_WIDTH);
    animateCar(40, (TERMINAL_WIDTH + carMaxLineLength) / 2);

    struct Bill userBill;

    initializeBillStructWithZeros(&userBill);

    printBillStruct(&userBill, 1, 14);

    getStringInput(userBill.driverName, "Enter Driver Name: ", 5);
    printBillStruct(&userBill, 1, 14);

    getStringInput(userBill.driverLicense, "Enter Driver License: ", 5);
    printBillStruct(&userBill, 1, 14);

    getStringInput(userBill.taxiNumber, "Enter Taxi Number: ", 5);
    printBillStruct(&userBill, 1, 14);

    getIntInput(&(userBill.distance), "Enter Distance Traveled: ", 5);
    printBillStruct(&userBill, 1, 14);

    int fare = calculateFare(userBill.distance);
    userBill.fare = fare;
    printBillStruct(&userBill, 1, 14);

    return 0;
}

void initializeBillStructWithZeros(struct Bill *userBill) {
    strcpy(userBill->driverName, "---");
    strcpy(userBill->driverLicense, "---");
    strcpy(userBill->taxiNumber, "---");
    userBill->distance = 0;
    userBill->fare = 0;
}

void printBillStruct(struct Bill *bill, int initialSpace, int inBetweenSpace) {
    clearScreen();
    printCar((TERMINAL_WIDTH - carMaxLineLength) / 2);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("Driver Name: %s", bill->driverName);
    printSpaces(inBetweenSpace);
    printf("Driver License Number: %s", bill->driverLicense);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("Taxi Number: %s", bill->taxiNumber);
    printSpaces(inBetweenSpace);
    printf("Distance: %d km", bill->distance);

    printf("\n");
    printf("\n");

    printSpaces(initialSpace);
    printf("Fare: %d", bill->fare);

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