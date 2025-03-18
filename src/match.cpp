// club_match.cpp
#include <iostream>
#include "match_manager.h"
#include <fstream>
#include "json.hpp"
#include "match_setup.h"
#include <Windows.h>
#include <map>
#include "func.h"

using json = nlohmann::json;


void clubMatch() {
    json homeTeam;
    json awayTeam;

    getClubMatchTeams(homeTeam, awayTeam);

    std::ifstream pFile("player_data.json");
    if (!pFile.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }

    json playerDataArray;
    pFile >> playerDataArray;
    pFile.close();

    std::vector<json> homePlayers;
    std::vector<json> awayPlayers;

    getClubPlayers(homeTeam, awayTeam, homePlayers, awayPlayers);

    int homePlayerCount = homePlayers.size(), awayPlayerCount = awayPlayers.size();

    std::vector<std::string> positionOrder = {
        "GK", 
        "CB", "LB", "RB", "LWB", "RWB", "SW",
        "DM", "CDM", "CM", "LM", "RM", "CAM", "AM", "W", 
        "CF", "ST", "LW", "RW", "SS" 
    };

    std::map<std::string, int> positionRank;
    for (size_t i = 0; i < positionOrder.size(); ++i) {
        positionRank[positionOrder[i]] = i;
    }

    auto sortPlayers = [&](std::vector<json>& players) {
        std::sort(players.begin(), players.end(), [&](const json& a, const json& b) {
            int posA = positionRank.count(a["position"]) ? positionRank[a["position"]] : 100;
            int posB = positionRank.count(b["position"]) ? positionRank[b["position"]] : 100;

            if (posA == posB) {
                return a["rating"] > b["rating"];  // Higher rating first
            }
            return posA < posB;  // Position order first
        });
    };

    sortPlayers(homePlayers);
    sortPlayers(awayPlayers);

    std::map<std::string, int> positionColors = {
    {"GK", 9},  // Blue for Goalkeepers
    {"CB", 12}, {"LB", 12}, {"RB", 12}, {"LWB", 12}, {"RWB", 12}, {"SW", 12},  // Red for Defenders
    {"DM", 14}, {"CDM", 14}, {"CM", 14}, {"LM", 14}, {"RM", 14}, {"CAM", 14}, {"AM", 14}, {"W", 14},  // Yellow for Midfielders
    {"CF", 2}, {"ST", 2}, {"LW", 2}, {"RW", 2}, {"SS", 2} // Green for Attackers
    };

    std::cout << "Lineups recieved!\n";

    //

    std::cout << homeTeam["name"] << " Players:\n";
    std::string lastPosition = "";
    for (const auto& player : homePlayers) {
        std::string pos = player["position"];

        // Print position once
        if (pos != lastPosition) {
            std::cout << "\n";
            lastPosition = pos;
            setColor(positionColors[pos], 0);
            std::cout << "  " << pos << ":\n";
        }

        std::cout << "    " << player["name"] << " - Rating: " << player["rating"] << "     ID" << player["id"] << "\n\n";
    }

    std::cout << awayTeam["name"] << " Players:\n";
    lastPosition = "";
    for (const auto& player : awayPlayers) {
        std::string pos = player["position"];

        if (pos != lastPosition) {
            std::cout << "\n";
            lastPosition = pos;
            setColor(positionColors[pos], 0);
            std::cout << "  " << pos << ":\n";
        }

        std::cout << "    " << player["name"] << " - Rating: " << player["rating"] << "     ID" << player["id"] << "\n";
    }

    setColor(4, 0);

    std::string homeFormation;

    std::cout << "Select Home Team formation: ";
    std::getline(std::cin, homeFormation);

    std::string awayFormation;
    std::cout << "Select Awat Team formation ";
    std::getline(std::cin, awayFormation);

    std::map<std::string, std::string> homePlayerMappings;
    std::map<std::string, std::string> awayPlayerMappings;

    formation(homeFormation, awayFormation, homePlayers, awayPlayers, homePlayerMappings, awayPlayerMappings);
    

    /*
        simulate(1, 1);
    */
    
}

void nationMatch() {
    json homeTeam;
    json awayTeam;
    getNationMatchTeams(homeTeam, awayTeam);


}

void clubNationMatch() {
    json homeTeam;
    json awayTeam;
    getNationMatchTeams(homeTeam, awayTeam);


}
