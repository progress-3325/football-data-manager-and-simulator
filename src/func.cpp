#include "func.h"
#include <iostream>
#include <string>
#include <random>
#include <Windows.h>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <map>
#include <utility>

using nlohmann::json;
 // General
void setColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (backgroundColor << 4));
}

 // ID generation
std::string generateClubID() {
    std::fstream file("team_data.json", std::ios::in | std::ios::out | std::ios::app);
    json teamData;

    // Read existing data or initialize empty array
    if (std::filesystem::exists("team_data.json") && file.peek() != std::ifstream::traits_type::eof()) {
        file >> teamData; // Parse existing JSON
    }
    else {
        teamData = json::array(); // Initialize empty array
    }
    file.close();

    std::string id;
    std::string charset = "abcdefghijklmnopqrstuvwxyz";
    int size = rand() % 21;
    if (size <= 4) {
        size = 5;
    }
    const size_t charsetSize = charset.size();

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, charsetSize - 1);

    for (size_t i = 0; i < size; ++i) {
        id += charset[distribution(generator)];
    }

    std::vector<std::string> existingIDs;
    for (const auto& team : teamData) {
        if (team.contains("id")) {
            existingIDs.push_back(team["id"].get<std::string>());
        }
    }
    int newID = rand();
    std::string sID = std::to_string(newID);
    do {
        id = "ID-" + sID + "-" + id;
    } while (std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end());

    return id;
}

std::string generateNationID() {
    std::fstream file("team_data.json", std::ios::in | std::ios::out | std::ios::app);
    json teamData;

    // Read existing data or initialize empty array
    if (std::filesystem::exists("team_data.json") && file.peek() != std::ifstream::traits_type::eof()) {
        file >> teamData; // Parse existing JSON
    }
    else {
        teamData = json::array(); // Initialize empty array
    }
    file.close();

    std::string id;
    std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int size = rand() % 21;
    if (size <= 4) {
        size = 5;
    }
    const size_t charsetSize = charset.size();

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, charsetSize - 1);

    for (size_t i = 0; i < size; ++i) {
        id += charset[distribution(generator)];
    }

    std::vector<std::string> existingIDs;
    for (const auto& team : teamData) {
        if (team.contains("id")) {
            existingIDs.push_back(team["id"].get<std::string>());
        }
    }
    int newID = rand();
    std::string sID = std::to_string(newID);
    do {
        id = "ID-" + sID + "-" + id;
    } while (std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end());

    return id;
}

std::string generatePlayerID() {
    std::fstream file("team_data.json", std::ios::in | std::ios::out | std::ios::app);
    json teamData;

    // Read existing data or initialize empty array
    if (std::filesystem::exists("team_data.json") && file.peek() != std::ifstream::traits_type::eof()) {
        file >> teamData; // Parse existing JSON
    }
    else {
        teamData = json::array(); // Initialize empty array
    }
    file.close();

    std::string id;
    std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-";
    int size = rand() % 31;
    if (size <= 9) {
        size = 10;
    }
    const size_t charsetSize = charset.size();

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, charsetSize - 1);

    for (size_t i = 0; i < size; ++i) {
        id += charset[distribution(generator)];
    }

    std::vector<std::string> existingIDs;
    for (const auto& team : teamData) {
        if (team.contains("id")) {
            existingIDs.push_back(team["id"].get<std::string>());
        }
    }
    int newID = rand();
    std::string sID = std::to_string(newID);
    do {
        id = "ID-" + sID + "-" + id;
    } while (std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end());

    return id;
}

 // Simulation
void selectPosition(const std::string pos, std::vector<std::string>& ids, int tries) {
    ids.clear();
    for (int i = 0; i < tries; i++) {
        std::string id;
        std::cout << "Select " << pos << " " << (tries > 1 ? std::to_string(i + 1) : "") << ": ";
        std::getline(std::cin, id);
        ids.push_back(id);
    }
}
void formation
(
    std::string home, 
    std::string away, 
    std::vector<json> homePL, 
    std::vector<json> awayPL, 
    std::map<std::string, std::string>& homePositionMappings, 
    std::map<std::string, std::string>& awayPositionMappings
) 
{
    std::vector<std::string> playerIDs;
    json player;
    for (int i = 0; i <= sizeof(homePL); i++)
    {
        player = homePL[i];
        playerIDs.push_back(player["id"]);
    }
    while (true) 
    {
        if (home == "1-4-5")
        {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CB";

            selectPosition("CM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "CM1";
            homePositionMappings[playerIDs[1]] = "CM2";

            selectPosition("LM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "LM";

            selectPosition("RM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "RM";

            selectPosition("AM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "AM1";
            homePositionMappings[playerIDs[1]] = "AM2";

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "1-3-3-3")
        {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CB";
        
            selectPosition("CDM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CDM";

            selectPosition("DM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "DM1";
            homePositionMappings[playerIDs[1]] = "DM2";

            selectPosition("CAM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CAM";

            selectPosition("AM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "AM1";
            homePositionMappings[playerIDs[1]] = "AM2";

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "1-3-4-2") 
        {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CB";

            selectPosition("CDM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CDM";

            selectPosition("DM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "DM1";
            homePositionMappings[playerIDs[1]] = "DM2";

            selectPosition("CM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "CM1";
            homePositionMappings[playerIDs[1]] = "CM2";

            selectPosition("AM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "AM1";
            homePositionMappings[playerIDs[1]] = "AM2";

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "1-2-3-4") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CB";

            selectPosition("DM", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "DM1";
            homePositionMappings[playerIDs[1]] = "DM2";

            selectPosition("CM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "CM";

            selectPosition("LM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "LM";

            selectPosition("RM", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "RM";

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "ST";
            
            selectPosition("SS", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "SS";
        }
        else if (home == "2-3-5 PYRAMID") 
        {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 2); 
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";

            selectPosition("DM", playerIDs, 3); 
            homePositionMappings[playerIDs[0]] = "DM1";
            homePositionMappings[playerIDs[1]] = "DM2";
            homePositionMappings[playerIDs[2]] = "DM3";

            selectPosition("AM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "AM1";
            homePositionMappings[playerIDs[1]] = "AM2";

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "2-5-3") 
        {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "CDM";
            
            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CM1";
            homePositionMappings[playerIDs[1]] = "CM2";

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LM";

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RM";

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "2-4-4") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CM1";
            homePositionMappings[playerIDs[1]] = "CM2";

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LM";

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RM";

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("CF", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "CF";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "2-3-2-3 WW") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";

            selectPosition("DM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "DM1";
            homePositionMappings[playerIDs[1]] = "DM2";

            selectPosition("CM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "CM";

            selectPosition("AM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "AM1";
            homePositionMappings[playerIDs[1]] = "AM2";

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "3-4-3") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";
            homePositionMappings[playerIDs[2]] = "CB3";

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CM1";
            homePositionMappings[playerIDs[1]] = "CM2";

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LM";

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RM";

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LW";

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RW";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "3-5-2") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";
            homePositionMappings[playerIDs[2]] = "CB3";

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LWB";

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RWB";

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "CDM";

            selectPosition("CM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "CM";

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "CAM";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";

            selectPosition("SS", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "SS";
        }
        else if (home == "3-4-1-2") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("SS", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "3-2-4-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];

            selectPosition("DM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CAM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-4-2") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
        
            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("SS", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-4-2 DIAMOND" || home == "4-4-2 NARROW") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("SS", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-3-3") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            
            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-3-3 ATK") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-2-3-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            
            selectPosition("DM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-1-4-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-5-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("AM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-2-4") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("CF", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "4-2-2-2") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("SS", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("ST", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
        }
        else if (home == "5-3-2") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];

            selectPosition("ST", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
        }
        else if (home == "5-4-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "5-2-3") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "6-3-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 4);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];
            homePositionMappings[playerIDs[0]] = playerIDs[3];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];

            selectPosition("CF", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
        }
        else if (home == "6-2-2") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CB", playerIDs, 4);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
            homePositionMappings[playerIDs[0]] = playerIDs[2];
            homePositionMappings[playerIDs[0]] = playerIDs[3];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];

            selectPosition("CF", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = playerIDs[0];
            homePositionMappings[playerIDs[0]] = playerIDs[1];
        }
        else {
            std::cerr << "You have entered an illegal value, please try again.";
            continue;
        }
        break;
    }
    playerIDs.clear();

    for (int i = 0; i <= awayPL; i++)
    {
        player = awayPL[i];
        playerIDs.push_back(player["id"]);
    }
    while (true)
    {

    }
}

std::map<std::string, std::pair<int, int>> setPitchPos(std::map<std::string, std::string> positionMap)
{
    std::map<std::string, std::pair<int, int>> pitchPos;
    std::vector<std::string> playerIDs;
    for (auto&& [key, value] : positionMap)
    {
        playerIDs.push_back(key);
    }

    return pitchPos;
}