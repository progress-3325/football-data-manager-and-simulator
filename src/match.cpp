// club_match.cpp
#include <iostream>
#include "match_manager.h"
#include <fstream>
#include "json.hpp"
#include "match_simulation.h"

using json = nlohmann::json;

void clubMatch() {
    std::ifstream file("team_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }

    json teamDataArray;
    file >> teamDataArray;
    file.close();

    for (const auto& teamData : teamDataArray) {
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Club ID: " << teamData["id"] << "\nClub Name: " << teamData["name"] << std::endl;
    }

    int teamID;
    std::cout << "Select Home Club by ID: ";
    std::cin >> teamID;
    std::cin.ignore();

    bool teamFound = false;
    json homeTeam;

    for (const auto& teamData : teamDataArray) {
        if (teamData["id"] == teamID) {
            teamFound = true;
            homeTeam = teamData;
            break;
        }
    }

    if (!teamFound) {
        std::cerr << "Team ID not found. Please try again.\n";
        return;
    }

    std::cout << "You selected: " << homeTeam["name"] << std::endl;

    json awayTeam;
    int awayID;
    bool awayFound = false;

    do {
        std::cout << "Select Away Club by ID: ";
        std::cin >> awayID;
        std::cin.ignore();

        if (awayID == teamID) {
            std::cerr << "You cannot select the same Away Club as the Home Club. Try again.\n";
            continue;
        }

        for (const auto& teamData : teamDataArray) {
            if (teamData["id"] == awayID) {
                awayFound = true;
                awayTeam = teamData;
                break;
            }
        }

        if (!awayFound) {
            std::cerr << "Away Team ID not found. Please try again.\n";
        }
    } while (!awayFound);

    std::cout << "Away Club selected: " << awayTeam["name"] << std::endl;
    
    matchSettings();

}

void nationMatch() {
    std::ifstream file("team_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }

    json teamDataArray;
    file >> teamDataArray;
    file.close();

    for (const auto& teamData : teamDataArray) {
        std::cout << "---------------------------------" << std::endl;
        std::cout << "National Team Name: " << teamData["name"] << std::endl;
    }

    std::string nationName;
    std::cout << "Select National Team by Name: ";
    getline(std::cin, nationName);

    bool teamFound = false;
    json selectedTeam;

    for (const auto& teamData : teamDataArray) {
        if (teamData["name"] == nationName) {
            teamFound = true;
            selectedTeam = teamData;
            break;
        }
    }

    if (!teamFound) {
        std::cerr << "Team Name not found. Please try again.\n";
        return;
    }

    std::cout << "You selected: " << selectedTeam["name"] << std::endl;

    json awayTeam;
    std::string awayName;
    bool awayFound = false;

    do {
        std::cout << "Select Away National Team by Name: ";
        getline(std::cin, awayName);

        if (awayName == nationName) {
            std::cerr << "You cannot have the same away team as home team. Try again.\n";
            continue;
        }

        for (const auto& teamData : teamDataArray) {
            if (teamData["name"] == awayName) {
                awayFound = true;
                awayTeam = teamData;
                break;
            }
        }

        if (!awayFound) {
            std::cerr << "Away Team ID not found. Please try again.\n";
        }
    } while (!awayFound);

    std::cout << "Away Team Found\n You have selected: " << awayTeam << "\n";
    matchSettings();
}
