// match_simulation.cpp
#include <iostream>
#include "match_manager.h"
#include "match_setup.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

void simulateMatch() {
	// TODO: Add logic for match simulation.
	// - Allow user to choose teams (by ID or nationality for national teams).
	// - Incorporate team/player stats into the simulation.
	// - Display results minute-by-minute (if required).
	// - Save results for future reference.
	int choice;

	while (true) {
		std::cout << "\nMatch Simulation Menu:\n";
		std::cout << "1. Club vs. Club\n";
		std::cout << "2. National Team vs. National Team\n";
		std::cout << "3. Club vs. National Team\n";
		std::cout << "4. Modify Match Settings\n";
		std::cout << "5. Go Back\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cin.ignore();

		switch (choice) {
		case 1:
			clubMatch();
			continue;
		case 2:
			nationMatch();
			continue;
		case 3:
			continue;
		case 4:
			matchSettings();
			continue;
		case 5:
			break;
		default:
			std::cout << "\nInvalid Choice\n";
			continue;
		}
		break;
	}
	
}

