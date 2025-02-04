#include "func.h"
#include <iostream>
#include <string>
#include <random>
#include <Windows.h>
#include <fstream>
#include "json.hpp"
#include <vector>

using nlohmann::json;

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


void setColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (backgroundColor << 4));
}