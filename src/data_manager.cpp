#include <iostream>
#include "player_data.h"
#include "team_data.h"
#include "data_manager.h"
#include <ctime>

void dataManager() {
    int choice;
    while (true) {
        // Display the menu to the user
        std::cout << "\nData Manager Menu:\n";
        std::cout << "1. Write Player Data\n";
        std::cout << "2. Write Team Data\n";
        std::cout << "3. Read Player Data\n";
        std::cout << "4. Read Team Data\n";
        std::cout << "5. Go Back\n";
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
            std::cout << "1. Display all players of a team\n";
            std::cout << "2. Display all players of a nationality\n";
            std::cout << "3. Go Back\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();
            switch (choice) {
            case 1:
                displayTeamPlayersData();
                break;
            case 2:
                displayNationalityPlayersData();
                break;
            case 3:
                break;
            }
            break;
        case 5:
            std::cout << "Going Back...\n";
            return;
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    }
}