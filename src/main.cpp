#include <iostream>
#include <ctime>
#include "version.h"
#include <windows.h>
#include "data_manager.h"
#include "match_manager.h"
#include <stdexcept>
#include "func.h"

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
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
        case 1:
            dataManager();
            continue;
        case 2:
            matchManager();
            continue;
        case 3:
            return 0;
        default:
            std::cout << "Invalid input, please try again\n";
            continue;
        }
        return 0;
    }
}
