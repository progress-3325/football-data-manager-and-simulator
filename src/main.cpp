#include <iostream>
#include "player_data.h"
#include "team_data.h"
#include <ctime>
#include "version.h"
#include <windows.h>
#include "data_manager.h"

void setColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (backgroundColor << 4));
}

int main() {
    srand(time(NULL));
    int choice;

    setColor(10, 0);
    std::cout << "Project Version: " << PROJECT_VERSION << std::endl;

    setColor(4, 0);

    while (true) {
        std::cout << "\nMenu: \n";
        std::cout << "1. Data Manager\n";
        std::cout << "2. Match Manager (WIP)\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            dataManager();
            break;
        case 2:
            std::cout << "Work In Progress...";
            break;
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
        return 0;
    }
}
