// match_manager.cpp
#include <iostream>
#include "match_manager.h"

void matchManager() {
	int choice;

	while (true) {
		std::cout << "\nMatch Manager Menu:\n";
		std::cout << "1. Simulate Match\n";
		std::cout << "2. See Past Results\n";
		std::cout << "3. Select League\n";
		std::cout << "4. Go Back\n";
		std::cout << "Enter Choice: ";
		std::cin >> choice;
		std::cin.ignore();

		switch (choice) {
		case 1:
			simulateMatch();
			continue;
		case 2:
			displayResults();
			continue;
		case 3:
			selectLeague();
			continue;
		case 4:
			break;
		default:
			std::cout << "Invalid Choice\n";
			continue;
		}
	}
	
}



void displayResults() {
	std::cout << "\nDisplaying Past Results...\n";
	// TODO: Add functionality to retrieve and display stored match results.
	// - Fetch data from a storage file.
	// - Provide filters for specific teams, leagues, or time periods.
	// - Display match statistics (e.g., scores, top performers).
}

void selectLeague() {
	std::cout << "\nSelecting a League...\n";
	// TODO: Add functionality to manage league selection.
	// - Allow the user to choose a league or tournament from available options.
	// - Load league-specific data (teams, schedules, etc.).
	// - Prepare for future league simulation compatibility.
}
