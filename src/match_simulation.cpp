#include <iostream> // For input and output operations
#include "match_manager.h" // Custom header for managing match-related logic
#include "match_setup.h" // Custom header for setting up matches
#include <fstream> // For file operations (e.g., saving results)
#include "json.hpp" // For handling JSON data

// Alias for the JSON library namespace
using json = nlohmann::json;

// Function to simulate a match
void simulateMatch() {

    int choice; // Variable to store the user's menu choice

    // Infinite loop to display the menu until the user decides to exit
    while (true) {
        // Display the match simulation menu
        std::cout << "\nMatch Simulation Menu:\n";
        std::cout << "1. Club vs. Club\n"; // Option for simulating a match between two clubs
        std::cout << "2. National Team vs. National Team\n"; // Option for simulating a match between two national teams
        std::cout << "3. Club vs. National Team\n"; // Option for simulating a match between a club and a national team
        std::cout << "4. Modify Match Settings\n"; // Option to modify match settings
        std::cout << "5. Go Back\n"; // Option to exit the menu
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Read the user's choice
        std::cin.ignore(); // Clear the input buffer to avoid issues with subsequent input

        // Handle the user's choice using a switch statement
        switch (choice) {
        case 1:
            // Call the function to simulate a club vs. club match
            clubMatch();
            continue; // Return to the menu after the operation
        case 2:
            // Call the function to simulate a national team vs. national team match
            nationMatch();
            continue; // Return to the menu after the operation
        case 3:
            // Placeholder for club vs. national team match logic
            continue; // Return to the menu after the operation
        case 4:
            // Call the function to modify match settings
            matchSettings();
            continue; // Return to the menu after the operation
        case 5:
            // Exit the menu loop
            break;
        default:
            // Handle invalid input
            std::cout << "\nInvalid Choice\n";
            continue; // Return to the menu after displaying the error
        }
        break; // Exit the loop if the user chooses to go back
    }
}
