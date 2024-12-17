#include <iostream>
#include "match_manager.h"

MatchManager::MatchManager(const std::map<int, Team>& teams) : teams(teams) {}

void MatchManager::selectTeams(int& team1ID, int& team2ID) {
    std::cout << "Available Teams:" << std::endl;
    for (const auto& pair : teams) {
        std::cout << "ID: " << pair.first << " - Team Name: " << pair.second.name << std::endl;
    }
    std::cout << "Enter ID for Team 1: ";
    std::cin >> team1ID;
    std::cin.ignore();
    std::cout << "Enter ID for Team 2: ";
    std::cin >> team2ID;
    std::cin.ignore();
}

void MatchManager::simulateMatch(int team1ID, int team2ID) {
    Team team1 = teams.at(team1ID);
    Team team2 = teams.at(team2ID);

    int minutes = 90;
    for (int minute = 1; minute <= minutes; ++minute) {
        std::cout << "Minute " << minute << ": " << team1.name << " vs " << team2.name << std::endl;

        // Simulate match events here (goals, fouls, etc.)
        std::cout << "Simulating actions..." << std::endl;

        std::cout << "Press 1 to continue to the next minute..." << std::endl;
        int input;
        std::cin >> input;

        while (input != 1) {
            std::cout << "Invalid input. Please enter 1 to continue." << std::endl;
            std::cin >> input;
        }
    }

    std::cout << "Match Finished!" << std::endl;
    // Print final score, stats, etc.
}
