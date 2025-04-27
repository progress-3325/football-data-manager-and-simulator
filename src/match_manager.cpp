#include <iostream> // For input and output operations
#include "match_manager.h" // Header file for match manager declarations
#include "func.h" // Header file for additional utility functions

// Function to manage the match menu and handle user choices
void matchManager() {
    setColor(2, 0); // Set console text color (foreground: green, background: black)

    int choice; // Variable to store user input

    // Infinite loop to display the menu until the user chooses to exit
    while (true) {
        // Display the match manager menu
        std::cout << "\nMatch Manager Menu:\n";
        std::cout << "1. Simulate Match\n";
        std::cout << "2. See Past Results\n";
        std::cout << "3. Select League\n";
        std::cout << "4. Go Back\n";
        std::cout << "Enter Choice: ";
        std::cin >> choice; // Get user input
        std::cin.ignore(); // Ignore any leftover input in the buffer

        // Handle user input using a switch statement
        switch (choice) {
        case 1:
            simulateMatch(); // Call function to simulate a match
            continue; // Continue to display the menu
        case 2:
            displayResults(); // Call function to display past results
            continue; // Continue to display the menu
        case 3:
            selectLeague(); // Call function to select a league
            continue; // Continue to display the menu
        case 4:
            return; // Exit the function and return to the previous menu
        default:
            std::cout << "Invalid Choice\n"; // Handle invalid input
            continue; // Continue to display the menu
        }
    }
}

// Function to display past match results
void displayResults() {
    std::cout << "\nDisplaying Past Results...\n"; // Placeholder for displaying results
}

// Function to handle league selection
void selectLeague() {
    std::cout << "\nSelecting a League...\n"; // Placeholder for selecting league
}
