#include <stdio.h>
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

void animateCar();

void clearScreen();

void printSpaces(int count);

void sleepcp(int milliseconds);

void printCar();

int main() {
    animateCar(170);

    printf("\n");
    return 0;
}

void printCar(int spaces) {
    for (int i = 0; i < 6; i++) {
        printSpaces(spaces);
        printf("%s", car[i]);
        printf("\n");
    }
}

void animateCar(int sleepTime) {
    int increament = 1;
    for (int j = carMaxLineLength, k = 0; j < TERMINAL_WIDTH;) {
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