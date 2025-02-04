#include <iostream>
#include "match_manager.h"
#include <fstream>
#include "json.hpp"
#include "match_setup.h"

using nlohmann::json;

void getClubMatchTeams(json& team1, json& team2) {
    std::ifstream file("team_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }

    json teamDataArray;
    file >> teamDataArray;
    file.close();

    for (const auto& teamData : teamDataArray) {
        if (teamData["national_team"] == false) {
            std::cout << "---------------------------------" << std::endl;
            std::cout << "Club ID: " << teamData["id"] << "\nClub Name: " << teamData["name"] << std::endl;
        }
    }
    std::string teamID;
    std::cout << "Select Home Club by ID: ";
    std::getline(std::cin, teamID);

    bool teamFound = false;
    json homeTeam;

    do {

        for (const auto& teamData : teamDataArray) {
            if (teamData["id"] == teamID) {
                teamFound = true;
                homeTeam = teamData;
                break;
            }
        }

        if (!teamFound) {
            std::cerr << "Team ID not found. Please try again.\n";
            continue;
        }

        if (homeTeam["national_team"] == true) {
            std::cerr << "You are not allowed to select a National Team in a club match.";
            continue;
        }
    } while (!teamFound);
    std::cout << "Home Club selected: " << homeTeam["name"] << std::endl;


    json awayTeam;
    std::string awayID;
    bool awayFound = false;

    do {
        std::cout << "Select Away Club by ID: ";
        std::getline(std::cin, awayID);

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
            continue;
        }

        if (awayTeam["national_team"] == true) {
            std::cerr << "You are not allowed to select a National Team in a club match.";
            continue;
        }
    } while (!awayFound);

    std::cout << "Away Club selected: " << awayTeam["name"] << std::endl;
    team1 = homeTeam;
    team2 = awayTeam;
}

void getNationMatchTeams(json& team1, json& team2) {
    std::ifstream file("team_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }

    json teamDataArray;
    file >> teamDataArray;
    file.close();

    for (const auto& teamData : teamDataArray) {
        if (teamData["national_team"] == true) {
            std::cout << "---------------------------------" << std::endl;
            std::cout << "National Team ID: " << teamData["id"] << "\nNational Team Name: " << teamData["name"] << std::endl;
        }
    }

    std::string nationName;
    std::cout << "Select National Team by Name: ";
    getline(std::cin, nationName);

    bool teamFound = false;
    json homeTeam;

    for (const auto& teamData : teamDataArray) {
        if (teamData["name"] == nationName) {
            teamFound = true;
            homeTeam = teamData;
            break;
        }
    }

    if (!teamFound) {
        std::cerr << "Team Name not found. Please try again.\n";
        return;
    }

    std::cout << "You selected: " << homeTeam["name"] << std::endl;

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

    team1 = homeTeam;
    team2 = awayTeam;
}

void getClubNationMatchTeams(json& team1, json& team2) {
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
        std::cout << "Club ID: " << teamData["id"] << "\nClub/National Team Name: " << teamData["name"] << std::endl;
    }

    std::string teamID;
    std::cout << "Select Home Club/National Team by ID: ";
    std::getline(std::cin, teamID);

    bool teamFound = false;
    json homeTeam;

    do {

        for (const auto& teamData : teamDataArray) {
            if (teamData["id"] == teamID) {
                teamFound = true;
                homeTeam = teamData;
                break;
            }
        }

        if (!teamFound) {
            std::cerr << "Team ID not found. Please try again.\n";
            continue;
        }

        if (homeTeam["national_team"] == true) {
            std::cout << "You selected a national team: " << homeTeam["name"] << std::endl;
        }
        else {
            std::cout << "You selected a club team: " << homeTeam["name"] << std::endl;
        }
    } while (!teamFound);

    if (homeTeam["national_team"] == true) {
        std::cout << "Home National Team selected: " << homeTeam["name"] << std::endl;
    }
    else {
        std::cout << "Home Club selected: " << homeTeam["name"] << std::endl;
    }

    json awayTeam;
    std::string awayID;
    bool awayFound = false;

    do {
        std::cout << "Select Away Club/National Team by ID: ";
        std::getline(std::cin, awayID);

        if (awayID == teamID) {
            std::cerr << "You cannot select the same Away Club/National Team as the Home Club/National Team. Try again.\n";
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
            continue;
        }

        if (awayTeam["national_team"] == homeTeam["national_team"]) {
            std::cout << "You cannot have a Club vs. CLub/National Team vs. National Team match in a Club vs. National Team match\n";
            continue;
        }

        if (awayTeam["national_team"] == true) {
            std::cout << "You selected a national team: " << awayTeam["name"] << std::endl;
        }
        else {
            std::cout << "You selected a club team: " << awayTeam["name"] << std::endl;
        }
    } while (!awayFound);

    if (awayTeam["national_team"] == true) {
        std::cout << "Away National Team selected: " << awayTeam["name"] << std::endl;
    }
    else {
        std::cout << "Away Club selected: " << awayTeam["name"] << std::endl;
    }

    team1 = homeTeam;
    team2 = awayTeam;
}

void getClubPlayers(const json& team1, const json& team2, std::vector<json>& homePlayers, std::vector<json>& awayPlayers) {
    std::ifstream pFile("player_data.json");
    if (!pFile.is_open()) {
        std::cerr << "Error opening the JSON file!\n";
        return;
    }

    json playerDataArray;
    pFile >> playerDataArray;
    pFile.close();

    for (const auto& player : playerDataArray) {
        if (player["team_id"] == team1["id"]) {
            homePlayers.push_back(player);
        }
        else if (player["team_id"] == team2["id"]) {
            awayPlayers.push_back(player);
        }
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