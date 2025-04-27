#include <iostream> // For input and output operations
#include <ctime> // For time-related functions (used for seeding random number generator)
#include "version.h" // Custom header for project version information
#include <windows.h> // For Windows-specific functionality (e.g., setColor function)
#include "data_manager.h" // Custom header for data management functionality
#include "match_manager.h" // Custom header for match management functionality
#include <stdexcept> // For exception handling
#include "func.h" // Custom header for additional utility functions

int main() {
    // Seed the random number generator with the current time
    srand(time(NULL));
    int choice; // Variable to store the user's menu choice

    // Set console text color to green (foreground: 10, background: 0)
    setColor(10, 0);
    // Display the project version using the PROJECT_VERSION macro from "version.h"
    std::cout << "Project Version: " << PROJECT_VERSION << std::endl;

    // Set console text color to red (foreground: 4, background: 0)
    setColor(4, 0);

    // Infinite loop to display the menu and handle user input
    while (true) {
        // Display the menu options
        std::cout << "\nMenu: \n";
        std::cout << "1. Data Manager\n"; // Option to access the Data Manager
        std::cout << "2. Match Manager (WIP)\n"; // Option to access the Match Manager (Work In Progress)
        std::cout << "3. Exit\n"; // Option to exit the program
        std::cout << "Enter your choice: ";
        
        // Read the user's choice
        std::cin >> choice;
        std::cin.ignore(); // Clear the input buffer to avoid issues with subsequent input

        // Handle the user's choice using a switch statement
        switch (choice) {
        case 1:
            // Call the dataManager function (defined in "data_manager.h")
            dataManager();
            continue; // Return to the menu after executing the Data Manager
        case 2:
            // Call the matchManager function (defined in "match_manager.h")
            matchManager();
            continue; // Return to the menu after executing the Match Manager
        case 3:
            // Exit the program
            return 0;
        default:
            // Handle invalid input
            std::cout << "Invalid input, please try again\n";
            continue; // Return to the menu after displaying the error message
        }
        // This return statement is unreachable but included for completeness
        return 0;
    }
}
