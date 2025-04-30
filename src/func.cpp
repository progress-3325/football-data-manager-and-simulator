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
#include <private.h>

using nlohmann::json;
 // General
void setColor(int textColor, int backgroundColor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (backgroundColor << 4));
}

 // ID generation
std::string generateClubID() 
{
    std::fstream file("team_data.json", std::ios::in | std::ios::out | std::ios::app);
    json teamData;

    // Read existing data or initialize empty array
    if (std::filesystem::exists("team_data.json") && file.peek() != std::ifstream::traits_type::eof()) /**/ file >> teamData; // Parse existing JSON
    else /**/ teamData = json::array(); // Initialize empty array
    file.close();

    std::string id;
    std::string charset = "abcdefghijklmnopqrstuvwxyz";
    int size = rand() % 21;
    if (size <= 4) /**/ size = 5;
    const size_t charsetSize = charset.size();

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, charsetSize - 1);

    for (size_t i = 0; i < size; ++i) id += charset[distribution(generator)];

    std::vector<std::string> existingIDs;
    for (const auto& team : teamData) /**/ if (team.contains("id")) /**/ existingIDs.push_back(team["id"].get<std::string>());
    int newID = rand();
    std::string sID = std::to_string(newID);
    do /**/ id = "ID-" + sID + "-" + id; 
    while (std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end());

    return id;
}

std::string generateNationID() 
{
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

std::string generatePlayerID() 
{
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
        if (team.contains("id")) existingIDs.push_back(team["id"].get<std::string>());
    }
    int newID = rand();
    std::string sID = std::to_string(newID);
    do {
        id = "ID-" + sID + "-" + id;
    } while (std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end());

    return id;
}

 // Match Making
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
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";
            homePositionMappings[playerIDs[2]] = "CB3";

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LWB";

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RWB";

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CM1";
            homePositionMappings[playerIDs[1]] = "CM2";

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "CAM";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";

            selectPosition("SS", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "SS";
        }
        else if (home == "3-2-4-1") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 3);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";
            homePositionMappings[playerIDs[2]] = "CB3";

            selectPosition("DM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "DM1";
            homePositionMappings[playerIDs[1]] = "DM2";

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LM";

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RM";

            selectPosition("CAM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CAM1";
            homePositionMappings[playerIDs[1]] = "CAM2";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";
        }
        else if (home == "4-4-2") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "GK";

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CB1";
            homePositionMappings[playerIDs[1]] = "CB2";
        
            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LB";

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RB";

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "CM1";
            homePositionMappings[playerIDs[1]] = "CM2";

            selectPosition("LM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "LM";

            selectPosition("RM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "RM";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "ST";

            selectPosition("SS", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "SS";
        }
        else if (home == "4-4-2 DIAMOND" || home == "4-4-2 NARROW") 
        {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("CB", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "";
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("LB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("RB", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("CM", playerIDs, 2);
            homePositionMappings[playerIDs[0]] = "";
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("ST", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "";

            selectPosition("SS", playerIDs, 1);
            homePositionMappings[playerIDs[0]] = "";
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

    for (const auto& PL : awayPL)
    {
        player = PL;
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

 // Data
#include <cstdio>
#include <memory>
#include <stdexcept>
void exportPlayerData(const json obj)
{
    const std::string path = pv::path + "export_player_data.py";
    std::string command = "python3 " + path;

    FILE* pipe = _popen(command.c_str(), "w");
    if (!pipe) /**/ throw std::runtime_error("Failed to open Python script\n");

    try
    {
        std::string jsonString = obj.dump();
        fwrite(jsonString.c_str(), sizeof(char), jsonString.size(), pipe);
        _pclose(pipe);
    }
    catch (...)
    {
        _pclose(pipe);
        throw;
    }
    
}

#include <sstream>
json importPlayerData(std::vector<std::string>* ids, std::string* teamID)
{
    const std::string path = pv::path + "import_player_data.py";
    if (ids == NULL && teamID == NULL)
    {
        std::string command = "python3 " + path;

        FILE* pipe = _popen(command.c_str(), "r");
        if (!pipe) /**/ throw std::runtime_error("Failed to run Python script (import_player_data.py)\n");

        char buffer[128];
        std::stringstream result;

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) /**/ result << buffer;
        _pclose(pipe);
        return json::parse(result.str());
    }
    else if (ids != NULL && teamID == NULL)
    {
        std::string command = "python3 " + path + " ids";

        FILE* pipe = _popen(command.c_str(), "r");
        if (!pipe) /**/ throw std::runtime_error("Failed to run Python script\n");

        char buffer[128];
        std::stringstream result;

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) /**/ result << buffer;

        _pclose(pipe);
        return json::parse(result.str());
    }
    else if (ids == NULL && teamID != NULL)
    {
        std::string command = "python3 " + path + " team";

        FILE* pipe = _popen(command.c_str(), "r");
        if (!pipe) /**/ throw std::runtime_error("Failed to run Python script\n");

        char buffer[128];
        std::stringstream result;

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) /**/ result << buffer;

        _pclose(pipe);
        return json::parse(result.str());
    }
    else
    {
        throw std::runtime_error("Invalid parameters");
    }

}

void calculateWithPos(std::string& playerPosition, float& playerRating, int pace, int dribbling, int passing, int shooting, int defending, int physicality)
{
    while (true)
    {
        std::cout << "Enter Player's Position: ";
        std::getline(std::cin, playerPosition);
        if (playerPosition == "goalkeeper" || playerPosition == "Goalkeeper" || playerPosition == "GK") {
            playerPosition = "GK"; // Assign the position abbreviation
            // Calculate the player's rating based on weighted attributes
            playerRating = (pace * .05) + (dribbling * .05) + (passing * .2) + (shooting * .05) + (defending * .3) + (physicality * .35);
        }
        // Check if the player's position matches "center back" or its variations
        else if (playerPosition == "center back" || playerPosition == "Center Back" || playerPosition == "CB") {
            playerPosition = "CB";
            playerRating = (pace * .15) + (dribbling * .1) + (passing * .15) + (shooting * .05) + (defending * .3) + (physicality * .25);
        }
        // Check if the player's position matches "left back" or its variations
        else if (playerPosition == "left back" || playerPosition == "Left Back" || playerPosition == "LB") {
            playerPosition = "LB";
            playerRating = (pace * .25) + (dribbling * .15) + (passing * .2) + (shooting * .05) + (defending * .25) + (physicality * .1);
        }
        // Check if the player's position matches "right back" or its variations
        else if (playerPosition == "right back" || playerPosition == "Right Back" || playerPosition == "RB") {
            playerPosition = "RB";
            playerRating = (pace * .25) + (dribbling * .15) + (passing * .2) + (shooting * .05) + (defending * .25) + (physicality * .1);
        }
        // Check if the player's position matches "light wing-back" or its variations
        else if (playerPosition == "light wing-back" || playerPosition == "Light Wing-Back" || playerPosition == "LWB") {
            playerPosition = "LWB";
            playerRating = (pace * .3) + (dribbling * .2) + (passing * .2) + (shooting * .05) + (defending * .15) + (physicality * .1);
        }
        // Check if the player's position matches "right wing-back" or its variations
        else if (playerPosition == "right wing-back" || playerPosition == "Right Wing-Back" || playerPosition == "RWB") {
            playerPosition = "RWB";
            playerRating = (pace * .3) + (dribbling * .2) + (passing * .2) + (shooting * .05) + (defending * .15) + (physicality * .1);
        }
        // Check if the player's position matches "sweeper" or its variations
        else if (playerPosition == "sweeper" || playerPosition == "Sweeper" || playerPosition == "SW") {
            playerPosition = "SW";
            playerRating = (pace * .2) + (dribbling * .1) + (passing * .2) + (shooting * .05) + (defending * .35) + (physicality * .1);
        }
        // Check if the player's position matches "defensive midfielder" or its variations
        else if (playerPosition == "defensive midfielder" || playerPosition == "Defensive Midfielder" || playerPosition == "DM") {
            playerPosition = "DM";
            playerRating = (pace * .15) + (dribbling * .15) + (passing * .25) + (shooting * .05) + (defending * .3) + (physicality * .1);
        }
        // Check if the player's position matches "left defensive midfielder" or its variations
        else if (playerPosition == "left defensive midfielder" || playerPosition == "Left Defensive Midfielder" || playerPosition == "LDM") {
            playerPosition = "LDM";
            playerRating = (pace * .15) + (dribbling * .15) + (passing * .25) + (shooting * .05) + (defending * .3) + (physicality * .1);
        }
        // Check if the player's position matches "right defensive midfielder" or its variations
        else if (playerPosition == "right defensive midfielder" || playerPosition == "Right Defensive Midfielder" || playerPosition == "RDM") {
            playerPosition = "RDM";
            playerRating = (pace * .15) + (dribbling * .15) + (passing * .25) + (shooting * .05) + (defending * .3) + (physicality * .1);
        }
        // Check if the player's position matches "central defensive midfielder" or its variations
        else if (playerPosition == "central defensive midfielder" || playerPosition == "Central Defensive Midfielder" || playerPosition == "CDM") {
            playerPosition = "CDM";
            playerRating = (pace * .15) + (dribbling * .2) + (passing * .25) + (shooting * .05) + (defending * .25) + (physicality * .1);
        }
        // Check if the player's position matches "central midfielder" or its variations
        else if (playerPosition == "central midfielder" || playerPosition == "Central Midfielder" || playerPosition == "CM") {
            playerPosition = "CM";
            playerRating = (pace * 0.15) + (dribbling * 0.2) + (passing * 0.3) + (shooting * 0.15) + (defending * 0.1) + (physicality * 0.1);
        }
        // Check if the player's position matches "left midfielder" or its variations
        else if (playerPosition == "left midfielder" || playerPosition == "Left Midfielder" || playerPosition == "LM") {
            playerPosition = "LM";
            playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.15) + (defending * 0.05) + (physicality * 0.1);
        }
        // Check if the player's position matches "right midfielder" or its variations
        else if (playerPosition == "right midfielder" || playerPosition == "Right Midfielder" || playerPosition == "RM") {
            playerPosition = "RM";
            playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.15) + (defending * 0.05) + (physicality * 0.1);
        }
        // Check if the player's position matches "central attacking midfielder" or its variations
        else if (playerPosition == "central attacking midfielder" || playerPosition == "Central Attacking Midfielder" || playerPosition == "CAM") {
            playerPosition = "CAM";
            playerRating = (dribbling * 0.3) + (passing * 0.3) + (shooting * 0.2) + (pace * 0.1) + (physicality * 0.05) + (defending * 0.05);
        }
        // Check if the player's position matches "attacking midfielder" or its variations
        else if (playerPosition == "attacking midfielder" || playerPosition == "Attacking Midfielder" || playerPosition == "AM") {
            playerPosition = "AM";
            playerRating = (dribbling * 0.3) + (passing * 0.3) + (shooting * 0.2) + (pace * 0.1) + (physicality * 0.05) + (defending * 0.05);
        }
        // Check if the player's position matches "wide midfielder" or its variations
        else if (playerPosition == "wide midfielder" || playerPosition == "Wide Midfielder" || playerPosition == "W") {
            playerPosition = "W";
            playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.25) + (shooting * 0.1) + (defending * 0.1) + (physicality * 0.05);
        }
        // Check if the player's position matches "center forward" or its variations
        else if (playerPosition == "center forward" || playerPosition == "Center Forward" || playerPosition == "CF") {
            playerPosition = "CF";
            playerRating = (pace * 0.15) + (dribbling * 0.2) + (passing * 0.1) + (shooting * 0.4) + (defending * 0.05) + (physicality * 0.1);
        }
        // Check if the player's position matches "striker" or its variations
        else if (playerPosition == "striker" || playerPosition == "Striker" || playerPosition == "ST") {
            playerPosition = "ST";
            playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
        }
        // Check if the player's position matches "left winger" or its variations
        else if (playerPosition == "left winger" || playerPosition == "Left Winger" || playerPosition == "LW") {
            playerPosition = "LW";
            playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
        }
        // Check if the player's position matches "right winger" or its variations
        else if (playerPosition == "right winger" || playerPosition == "Right Winger" || playerPosition == "RW") {
            playerPosition = "RW";
            playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
        }
        // Check if the player's position matches "second striker" or its variations
        else if (playerPosition == "second striker" || playerPosition == "Second Striker" || playerPosition == "SS") {
            playerPosition = "SS";
            playerRating = (pace * 0.15) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.3) + (defending * 0.05) + (physicality * 0.05);
        }
        else
        {
            std::cout << "Invalid input. Please try again\n";
            continue;
        }
        return;
    }
    return;
}