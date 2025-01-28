// club_match.cpp
#include <iostream>
#include "match_manager.h"
#include <fstream>
#include "json.hpp"
#include "match_setup.h"

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

    json homeTeam;
    json awayTeam;

    getClubMatchTeams(homeTeam, awayTeam);

    std::ifstream file("player_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }

    json playerDataArray;
    file >> playerDataArray;
    file.close();

    int homePlayers = NULL;
    int awayPlayers = NULL;
    for (const auto& playerData : playerDataArray) {
        if (playerData["team_id"] == homeTeam["id"]) {
            homePlayers++;
        }
        if (playerData["team_id"] == awayTeam["id"]) {
            homePlayers++;
        }
    }


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
