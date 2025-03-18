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
void formation(std::string home, std::string away, std::vector<json> homePL, std::vector<json> awayPL, std::map<std::string, std::string>& homePositionMappings, std::map<std::string, std::string>& awayPositionMappings) {
    std::vector<std::string> playerIDs;
    while (true) {
        if (home == "1-4-5") {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings["CB"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2); 
            homePositionMappings["CM1"] = playerIDs[0]; 
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("LM", playerIDs, 1); 
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1); 
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("AM", playerIDs, 2); 
            homePositionMappings["AM1"] = playerIDs[0]; 
            homePositionMappings["AM2"] = playerIDs[1];

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "1-3-3-3") {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings["CB"] = playerIDs[0];
        
            selectPosition("CDM", playerIDs, 1); 
            homePositionMappings["CDM"] = playerIDs[0];

            selectPosition("DM", playerIDs, 2); 
            homePositionMappings["DM1"] = playerIDs[0]; 
            homePositionMappings["DM2"] = playerIDs[1];

            selectPosition("CAM", playerIDs, 1); 
            homePositionMappings["CAM"] = playerIDs[0];

            selectPosition("AM", playerIDs, 2); 
            homePositionMappings["AM1"] = playerIDs[0]; 
            homePositionMappings["AM2"] = playerIDs[1];

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "1-3-4-2") {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings["CB"] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1); 
            homePositionMappings["CDM"] = playerIDs[0];

            selectPosition("DM", playerIDs, 2); 
            homePositionMappings["DM1"] = playerIDs[0]; 
            homePositionMappings["DM2"] = playerIDs[1];

            selectPosition("CM", playerIDs, 2); 
            homePositionMappings["CM1"] = playerIDs[0]; 
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("AM", playerIDs, 2); 
            homePositionMappings["AM1"] = playerIDs[0]; 
            homePositionMappings["AM2"] = playerIDs[1];

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "1-2-3-4") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 1); 
            homePositionMappings["CB"] = playerIDs[0];

            selectPosition("DM", playerIDs, 2); 
            homePositionMappings["DM1"] = playerIDs[0]; 
            homePositionMappings["DM2"] = playerIDs[1];

            selectPosition("CM", playerIDs, 1); 
            homePositionMappings["CM"] = playerIDs[0];

            selectPosition("LM", playerIDs, 1); 
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1); 
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("LW", playerIDs, 1); 
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1); 
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1); 
            homePositionMappings["ST"] = playerIDs[0];
            
            selectPosition("SS", playerIDs, 1); 
            homePositionMappings["SS"] = playerIDs[0];
        }
        else if (home == "2-3-5 PYRAMID") {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2); 
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("DM", playerIDs, 3); 
            homePositionMappings["DM1"] = playerIDs[0];
            homePositionMappings["DM2"] = playerIDs[1];
            homePositionMappings["DM3"] = playerIDs[2];

            selectPosition("AM", playerIDs, 2);
            homePositionMappings["AM1"] = playerIDs[0];
            homePositionMappings["AM2"] = playerIDs[1];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];;

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "2-5-3") {
            selectPosition("GK", playerIDs, 1); 
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings["CDM"] = playerIDs[0];
            
            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "2-4-4") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("CF", playerIDs, 1);
            homePositionMappings["CF"] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "2-3-2-3 WW") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("DM", playerIDs, 2);
            homePositionMappings["DM1"] = playerIDs[0];
            homePositionMappings["DM2"] = playerIDs[1];

            selectPosition("CM", playerIDs, 1);
            homePositionMappings["CM"] = playerIDs[0];

            selectPosition("AM", playerIDs, 2);
            homePositionMappings["AM1"] = playerIDs[0];
            homePositionMappings["AM2"] = playerIDs[1];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "3-4-3") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];
            homePositionMappings["CB3"] = playerIDs[2];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "3-5-2") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];
            homePositionMappings["CB3"] = playerIDs[2];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings["LWB"] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings["RWB"] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings["CDM"] = playerIDs[0];

            selectPosition("CM", playerIDs, 1);
            homePositionMappings["CM"] = playerIDs[0];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings["CAM"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];

            selectPosition("SS", playerIDs, 1);
            homePositionMappings["SS"] = playerIDs[0];
        }
        else if (home == "3-4-1-2") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];
            homePositionMappings["CB3"] = playerIDs[2];

            selectPosition("LWB", playerIDs, 1);
            homePositionMappings["LWB"] = playerIDs[0];

            selectPosition("RWB", playerIDs, 1);
            homePositionMappings["RWB"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[0];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings["CAM"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];

            selectPosition("SS", playerIDs, 1);
            homePositionMappings["SS"] = playerIDs[0];
        }
        else if (home == "3-2-4-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 3);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];
            homePositionMappings["CB3"] = playerIDs[2];

            selectPosition("DM", playerIDs, 2);
            homePositionMappings["DM1"] = playerIDs[0];
            homePositionMappings["DM2"] = playerIDs[1];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("CAM", playerIDs, 2);
            homePositionMappings["CAM1"] = playerIDs[0];
            homePositionMappings["CAM2"] = playerIDs[1];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "4-4-2") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];
        
            selectPosition("LB", playerIDs, 1);
            homePositionMappings["LB"] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings["RB"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[0];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];

            selectPosition("SS", playerIDs, 1);
            homePositionMappings["SS"] = playerIDs[0];
        }
        else if (home == "4-4-2 DIAMOND" || home == "4-4-2 NARROW") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings["LB"] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings["RB"] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings["CDM"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["LCM"] = playerIDs[0];
            homePositionMappings["RCM"] = playerIDs[0];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings["CAM"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];

            selectPosition("SS", playerIDs, 1);
            homePositionMappings["SS"] = playerIDs[0];
        }
        else if (home == "4-3-3") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings["LB"] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings["RB"] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings["CDM"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["LCM"] = playerIDs[0];
            homePositionMappings["RCM"] = playerIDs[0];
            
            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "4-3-3 ATK") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings["LB"] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings["RB"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[0];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings["CAM"] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "4-2-3-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings["LB"] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings["RB"] = playerIDs[0];
            
            selectPosition("DM", playerIDs, 2);
            homePositionMappings["DM1"] = playerIDs[0];
            homePositionMappings["DM2"] = playerIDs[1];

            selectPosition("CAM", playerIDs, 1);
            homePositionMappings["CAM"] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "4-1-4-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings["LB"] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings["RB"] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings["CDM"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("LM", playerIDs, 1);
            homePositionMappings["LM"] = playerIDs[0];

            selectPosition("RM", playerIDs, 1);
            homePositionMappings["RM"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "4-5-1") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];

            selectPosition("CB", playerIDs, 2);
            homePositionMappings["CB1"] = playerIDs[0];
            homePositionMappings["CB2"] = playerIDs[1];

            selectPosition("LB", playerIDs, 1);
            homePositionMappings["LB"] = playerIDs[0];

            selectPosition("RB", playerIDs, 1);
            homePositionMappings["RB"] = playerIDs[0];

            selectPosition("CDM", playerIDs, 1);
            homePositionMappings["CDM"] = playerIDs[0];

            selectPosition("CM", playerIDs, 2);
            homePositionMappings["CM1"] = playerIDs[0];
            homePositionMappings["CM2"] = playerIDs[1];

            selectPosition("AM", playerIDs, 1);
            homePositionMappings["AM"] = playerIDs[0];

            selectPosition("LW", playerIDs, 1);
            homePositionMappings["LW"] = playerIDs[0];

            selectPosition("RW", playerIDs, 1);
            homePositionMappings["RW"] = playerIDs[0];

            selectPosition("ST", playerIDs, 1);
            homePositionMappings["ST"] = playerIDs[0];
        }
        else if (home == "4-2-4") {
            selectPosition("GK", playerIDs, 1);
            homePositionMappings["GK"] = playerIDs[0];


        }
        else if (home == "4-2-2-2") {
            selectPosition("GK", playerIDs, 1);
            std::string homeGK = playerIDs[0];
            homePositionMappings["GK"] = homeGK;
        }
        else if (home == "5-3-2") {
            selectPosition("GK", playerIDs, 1);
            std::string homeGK = playerIDs[0];
            homePositionMappings["GK"] = homeGK;
        }
        else if (home == "5-4-1") {
            selectPosition("GK", playerIDs, 1);
            std::string homeGK = playerIDs[0];
            homePositionMappings["GK"] = homeGK;
        }
        else if (home == "5-2-3") {
            selectPosition("GK", playerIDs, 1);
            std::string homeGK = playerIDs[0];
            homePositionMappings["GK"] = homeGK;
        }
        else if (home == "6-3-1") {
            selectPosition("GK", playerIDs, 1);
            std::string homeGK = playerIDs[0];
            homePositionMappings["GK"] = homeGK;
        }
        else if (home == "6-2-2") {
            selectPosition("GK", playerIDs, 1);
            std::string homeGK = playerIDs[0];
            homePositionMappings["GK"] = homeGK;
        }
        else {
            std::cerr << "You have entered an illegal value, please try again.";
            continue;
        }
        break;
    }

    while (true) {}
}
std::map<json, std::pair<int, int>> returnWeights(std::map<json, int>& players)
{
    using std::map;
    using std::pair;

    std::ifstream file("player_data.json"); // Get player data.
    if (!file.is_open()) {
        std::cerr << "Error opening the JSON file!" << std::endl;
        return {};
    } // If player data wasn't saved then the function process will end.

    json playerDataArray; // Defining the array.
    file >> playerDataArray;
    file.close();

    map<json, pair<int, int>> weights;
    std::string player;
    for (const auto playerData : playerDataArray)
    {
        if (players.at("GK") == playerData["id"])
        {
            weights[playerData["id"]] = { 0, -50 };

        }
        if (players.at("CB1") != NULL)
        {
            weights[playerData["id"]] = { -10, -30 };
        }
        if (players.at("CB2") != NULL || players.at("CB") != NULL)
        {
            weights[playerData["id"]] = { 0, -30 };
        }
        if (players.at("CB3") != NULL)
        {
            player = players.at("CB3");
            weights[playerData["id"]] = { 10, -30 };
        }
        if (players.at("SW") != NULL)
        {
            player = players.at("SW");
            weights[playerData["id"]] = { 0, -40 };
        }
        if (players.at("LB") != NULL)
        {
            player = players.at("LB");
            weights[playerData["id"]] = { -40, -25 };
        }
        if (players.at("RB") != NULL)
        {
            player = players.at("RB");
            weights[playerData["id"]] = { 40, -25 };
        }
        if (players.at("LWB") != NULL)
        {
            player = players.at("LWB");
            weights[playerData["id"]] = { -40, -20 };
        }
        if (players.at("RWB") != NULL)
        {
            player = players.at("RWB");
            weights[playerData["id"]] = { 40, -20 };
        }
        if (players.at("DM1") != NULL)
        {
            player = players.at("RWB");
            weights[player].first = 40;
            weights[player].second = -20;
        }
        if (players.at("DM2") != NULL || players.at("DM") != NULL)
        {

        }
        if (players.at("DM3") != NULL)
        {

        }
    }
}

void simulate(int option1, int option2) {
    
}