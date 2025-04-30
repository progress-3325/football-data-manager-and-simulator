#include <iostream> // For input and output operations
#include "player_data.h" // Header file for player data-related functions
#include "team_data.h" // Header file for team data-related functions
#include "data_manager.h" // Header file for the data manager
#include "func.h" // Header file for utility functions like setColor

// Function to manage data-related operations
void dataManager() {
    setColor(10, 0); // Set the console text color (foreground: green, background: black)
    int choice; // Variable to store the user's menu choice

    while (true) { // Infinite loop to keep the menu running until the user exits
        // Display the main menu to the user
        std::cout << "\nData Manager Menu:\n";
        std::cout << "1. Write Player Data\n"; // Option to write player data
        std::cout << "2. Write Team Data\n"; // Option to write team data
        std::cout << "3. Read Player Data\n"; // Option to read/display player data
        std::cout << "4. Read Team Data\n"; // Option to read/display team data
        std::cout << "5. Go Back\n"; // Option to exit the menu
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Read the user's choice
        std::cin.ignore(); // Clear the input buffer after reading the choice

        // Handle user input based on the menu choice
        switch (choice) {
        case 1:
            writePlayerData(); // Call the function to write player data
            break;
        case 2:
            writeTeamData(); // Call the function to write team data
            break;
        case 3:
            displayPlayerData(); // Call the function to display player data
            break;
        case 4:
            displayTeamData(); // Call the function to display team data

            // Display a submenu for additional team data options
            std::cout << "1. Display all players of a team\n"; // Option to display players of a specific team
            std::cout << "2. Display all players of a nationality\n"; // Option to display players of a specific nationality
            std::cout << "3. Go Back\n"; // Option to return to the main menu
            std::cout << "Enter your choice: ";
            std::cin >> choice; // Read the user's choice for the submenu
            std::cin.ignore(); // Clear the input buffer after reading the choice

            // Handle user input for the submenu
            switch (choice) {
            case 1:
                displayTeamPlayersData(); // Call the function to display players of a specific team
                break;
            case 2:
                displayNationalityPlayersData(); // Call the function to display players of a specific nationality
                break;
            case 3:
                break; // Return to the main menu
            }
            break;
        case 5:
            std::cout << "Going Back...\n"; // Inform the user that they are exiting the menu
            return; // Exit the function and return to the previous context
        case 6:
            writePresetPlayerData();
            break;
        default:
            std::cout << "Invalid choice, please try again.\n"; // Handle invalid input
        }
    }
}