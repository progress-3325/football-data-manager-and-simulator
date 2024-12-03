#include <iostream>
#include "player_data.h"
#include "team_data.h"

int main() {
    int choice;

    while (true) {
        // Display the menu to the user
        std::cout << "\nMenu:\n";
        std::cout << "1. Write Player Data\n";
        std::cout << "2. Write Team Data\n";
        std::cout << "3. Read Player Data\n";
        std::cout << "4. Read Team Data\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer after reading the choice

        // Handle user input based on the menu choice
        switch (choice) {
        case 1:
            writePlayerData(); // Call the function to write player data
            break;
        case 2:
            writeTeamData();   // Call the function to write team data
            break;
        case 3:
            displayPlayerData();
            break;
        case 4:
            displayTeamData();
            break;
        case 5:
            std::cout << "Exiting program...\n";
            return 0; // Exit the program
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
