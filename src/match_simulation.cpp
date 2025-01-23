// match_simulation.cpp
#include <iostream>
#include "match_manager.h"
#include "match_simulation.h"
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
		std::cout << "4. Go Back\n";
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
			break;
		default:
			std::cout << "\nInvalid Choice\n";
			continue;
		}
		break;
	}
	
}

void matchSettings() {
	std::fstream sFile("match_settings.json", std::ios::in | std::ios::out | std::ios::app);
	json settings;
	if (std::filesystem::exists("match_settings.json") && sFile.peek() != std::ifstream::traits_type::eof()) {
		sFile >> settings;
	}
	else {
		settings = json::basic_json();
	}
	sFile.close();

	

}
