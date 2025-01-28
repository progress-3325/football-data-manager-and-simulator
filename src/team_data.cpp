#include <iostream>
#include <fstream>
#include "json.hpp"
#include "team_data.h"
#include <string>
#include <cstdlib>
#include <random>
#include <algorithm>

// team_data.cpp
// adds functionality to functions defined in team_data.h
// using an external library, it makes functions create a .json file to store in multiple teams
// it can also read .json files if it's according to its conditions
// progress-3325

using json = nlohmann::json;


std::string generateRandomString(bool national) {
    std::string result;
    int size = rand() % 21;
    if (size <= 4) {
        size = size + 1;
    }
    std::string charset = "0"; // Default value
    if (national) {
        charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Use uppercase for national teams
    }
    else {
        charset = "abcdefghijklmnopqrstuvwxyz"; // Use lowercase for non-national teams
    }

    const size_t charsetSize = charset.size();

    // Random device and generator
    std::random_device rd;  // Seed
    std::mt19937 generator(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> distribution(0, charsetSize - 1);

    for (size_t i = 0; i < size; ++i) {
        result += charset[distribution(generator)];
    }

    return result;
}

// writeTeamData()
// Purpose:
// Writes team data from input and then saves it to "team_data.json".
// Inputs: 
// Variables related to club information useful enough to be stored and used for future plans.
// Outputs:
// "team_data.json" file
void writeTeamData() {
    {
        // Open or create the JSON file
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

        // Defining club related variables
        bool nationalTeam = false;
        std::string teamID, clubName, clubHeadCoach, ultrasName, stadiumName, clubOwner;
        int clubYearFounded, leagueTitles, cupsWon, stadiumCapacity, squadSize, trainingFacilities, youthClubSquadMembers, youthClubRating, popularity;
        std::vector<std::string> rivalTeams;
        std::vector<std::string> clubColors;

        std::string ynChoice; // Defining yes/no variable for booleans
        std::cout << "Is the club a national team? (y/n): ";
        getline(std::cin, ynChoice);
        if (ynChoice == "y" || ynChoice == "Y") {
            nationalTeam = true;
        }
        else if (ynChoice == "n" || ynChoice == "N") {
            nationalTeam = false;
        }

        if (!nationalTeam) {
            std::vector<std::string> existingIDs;
            for (const auto& team : teamData) {
                if (team.contains("id")) {
                    existingIDs.push_back(team["id"].get<std::string>());
                }
            }
            int newID = rand();
            std::string sID = std::to_string(newID);
            do {
                std::string sSID = generateRandomString(false);
                sID = "ID-" + sID + "-" + sSID;
            } while (std::find(existingIDs.begin(), existingIDs.end(), sID) != existingIDs.end());

            teamID = sID;

        }   
        else if (nationalTeam) {
            std::vector <std::string> existingIDs;
            for (const auto& team : teamData) {
                if (team.contains("id")) {
                    existingIDs.push_back(team["id"].get<std::string>());
                }
            }
            int newID = rand();
            std::string sID = std::to_string(newID);
            do {
                std::string sSID = generateRandomString(true);
                sID = "ID-" + sID + "-" + sSID;
            } while (std::find(existingIDs.begin(), existingIDs.end(), sID) != existingIDs.end());
            teamID = sID;
        }


        // Row of setting a value to each variable
        std::cout << "Enter club's name: ";
        getline(std::cin, clubName);

        std::cout << "Enter club's head coach: ";
        getline(std::cin, clubHeadCoach);

        std::cout << "Enter the year the club was founded: ";
        std::cin >> clubYearFounded;

        std::cout << "Enter how many league cups has the club won until now (if national team enter -1): ";
        std::cin >> leagueTitles;
        std::cin.ignore();

        std::cout << "Enter how many national cups has the club won (if national team enter -1): ";
        std::cin >> cupsWon;
        std::cin.ignore();

        std::cout << "Enter the total amount of players (if national team enter the call ups): ";
        std::cin >> squadSize;
        std::cin.ignore();

        std::cout << "Enter the rating of the club's training facilities (enter from 1 to 5,if national team enter -1): ";
        std::cin >> trainingFacilities;
        std::cin.ignore();

        int numRivalries;
        std::cout << "Enter number of rival teams: ";
        std::cin >> numRivalries;
        std::cin.ignore();

        for (int i = 0; i < numRivalries; i++) {
            std::string rivalryId;
            std::cout << "Enter rival team ID " << i + 1 << ": ";
            std::cin >> rivalryId;
            std::cin.ignore();
            rivalTeams.push_back(rivalryId);
        }

        std::cout << "Enter the name of the club's fans: ";
        getline(std::cin, ultrasName);

        std::cout << "Enter how many followers the club has on any social media platform: ";
        std::cin >> popularity;
        std::cin.ignore();

        std::cout << "Enter the name of the club's stadium: ";
        getline(std::cin, stadiumName);

        std::cout << "Enter the stadium capacity: ";
        std::cin >> stadiumCapacity;
        std::cin.ignore();

        std::cout << "Enter the name of the person and/or organization that owns the club: ";
        getline(std::cin, clubOwner);

        int numColors;
        std::cout << "Enter how many main colors does your team have: ";
        std::cin >> numColors;
        std::cin.ignore();
        for (int i = 0; i < numColors; i++) {
            std::string color;
            std::cout << "Enter color name (or hex code): ";
            getline(std::cin, color);
            clubColors.push_back(color);
        }

        std::cout << "How many players are there in your youth club/academy: ";
        std::cin >> youthClubSquadMembers;
        std::cin.ignore();

        std::cout << "What is the rating of the youth club (1-100): ";
        std::cin >> youthClubRating;
        std::cin.ignore();

        json newTeam = {
            {"id", teamID},
            {"national_team", nationalTeam},
            {"name", clubName},
            {"head_coach", clubHeadCoach},
            {"year_founded", clubYearFounded},
            {"club_owner", clubOwner},
            {"club_color(s)", clubColors},
            {"league_titles", leagueTitles},
            {"national_cup_titles", cupsWon},
            {"squad_size", squadSize},
            {"training_facilities_rating", trainingFacilities},
            {"rival_teams", rivalTeams},
            {"fans_name", ultrasName},
            {"stadium_name", stadiumName},
            {"stadium_capacity", stadiumCapacity},
            {"youth_club_rating", youthClubRating},
            {"youth_club_members", youthClubSquadMembers},
            {"popularity", popularity}
        };

        teamData.push_back(newTeam);
        std::ofstream outFile("team_data.json");
        outFile << teamData.dump(4); // Pretty-print with 4-space indentation
        outFile.close();
    }
}

// displayTeamData()
// Purpose:
// Reads contents of "team_data.json".
// Input:
// None.
// Output:
// All contents of "team_data.json" in a set order unlike the raw file.
void displayTeamData() {
    // Opening the saved file
    std::ifstream file("team_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }



    json teamDataArray;
    file >> teamDataArray;
    file.close();

    if (!teamDataArray.is_array()) {
        std::cerr << "Error: JSON data is not an array!" << std::endl;
        return;
    }
    // Reading saved data from "team_data.json"

        for (const auto& teamData : teamDataArray) {
            std::cout << "---------------------------------" << std::endl;
            std::cout << "Team ID: " << teamData["id"] << std::endl;
            std::cout << "National team: " << (teamData["national_team"].get<bool>() ? "Yes" : "No") << std::endl;
            std::cout << "Club Name: " << teamData["name"] << std::endl;
            std::cout << "Head Coach: " << teamData["head_coach"] << std::endl;
            std::cout << "Year Founded: " << teamData["year_founded"] << std::endl;
            std::cout << "Owner: " << teamData["club_owner"] << std::endl;
            std::cout << "Colors: ";
            for (const auto& color : teamData["club_color(s)"]) {
                std::cout << color << " ";
            }
            std::cout << std::endl;
            std::cout << "League Titles: " << teamData["league_titles"] << std::endl;
            std::cout << "National Cup Titles: " << teamData["national_cup_titles"] << std::endl;
            std::cout << "Squad Size: " << teamData["squad_size"] << std::endl;
            std::cout << "Training Facilities Rating: " << teamData["training_facilities_rating"] << std::endl;
            std::cout << "Stadium Name: " << teamData["stadium_name"] << std::endl;
            std::cout << "Stadium Capacity: " << teamData["stadium_capacity"] << std::endl;
            std::cout << "Rival Teams: ";
            for (const auto& id : teamData["rival_teams"]) {
                std::cout << id << " ";
            }
            std::cout << std::endl;
            std::cout << "Fan Group Name: " << teamData["fans_name"] << std::endl;
            std::cout << "Social Media Followers: " << teamData["popularity"] << std::endl;
            std::cout << "Youth Club Rating: " << teamData["youth_club_rating"] << std::endl;
            std::cout << "Youth Club Members: " << teamData["youth_club_members"] << std::endl;
        }
    std::cout << "End of team data." << std::endl;
}

void displayTeamPlayersData() {
    std::cout << "Enter Desired Team ID: ";
    std::string selectedTeamID;
    std::getline(std::cin, selectedTeamID);

    // Display players of the selected team
    std::ifstream playerFile("player_data.json");
    if (!playerFile.is_open()) {
        std::cerr << "Error opening the player data file!" << std::endl;
        return;
    }

    json playerDataArray;
    playerFile >> playerDataArray;
    playerFile.close();

    std::cout << "\nPlayers in Team ID " << selectedTeamID << ":\n";
    for (const auto& playerData : playerDataArray) {
        if (playerData["team_id"] == selectedTeamID) {
            std::cout << "---------------------------------" << std::endl;
            std::cout << "Team ID: " << playerData["team_id"] << std::endl;
            std::cout << "Player ID: " << playerData["id"] << std::endl;
            std::cout << "Player Name: " << playerData["name"] << std::endl;
            std::cout << "Player Height: " << playerData["height"] << std::endl;
            std::cout << "Player Weight: " << playerData["weight"] << std::endl;
            std::cout << "Player Nationality: " << playerData["nationality"] << std::endl;
            std::cout << "Player Birthday: " << playerData["date_of_birth"] << std::endl;
            std::cout << "Player Position: " << playerData["position"] << std::endl;
            std::cout << "Player Number: " << playerData["number"] << std::endl;
            std::cout << "Player Is Captain? " << playerData["is_captain"] << std::endl;
            if (playerData["ambidextrous"] == true) {
                std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
            }
            else if (playerData["right_foot"] == true) {
                std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
                std::cout << "Player Is Right Footed" << std::endl;
            }
            else if (playerData["left_foot"] == true) {
                std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
                std::cout << "Player Is Left Footed" << std::endl;
            }
            std::cout << "Player Overall Rating: " << playerData["rating"] << std::endl;
            std::cout << "Player Pace Rating: " << playerData["pace"] << std::endl;
            std::cout << "Player Dribbling Rating: " << playerData["dribbling"] << std::endl;
            std::cout << "Player Passing Rating: " << playerData["passing"] << std::endl;
            std::cout << "Player Shooting Rating: " << playerData["shooting"] << std::endl;
            std::cout << "Player Defending Rating: " << playerData["defending"] << std::endl;
            std::cout << "Player Physicality Rating: " << playerData["physicality"] << std::endl;
            std::cout << "Player Composure Rating: " << playerData["composure"] << std::endl;
            std::cout << "Player Vision Rating: " << playerData["vision"] << std::endl;
            std::cout << "Player Positioning Rating: " << playerData["positioning"] << std::endl;
            std::cout << "Player Shooting Rating: " << playerData["shooting"] << std::endl;
            std::cout << "Player Aggression Rating" << playerData["aggression"] << std::endl;
            std::cout << "Player Penalty Rating: " << playerData["penalty"] << std::endl;
            std::cout << "Player Set Pieces Rating: " << playerData["set_pieces"] << std::endl;
            std::cout << "Player Ball Control Rating: " << playerData["ball_control"] << std::endl;
            std::cout << "Player Stamina Rating: " << playerData["stamina"] << std::endl;
            std::cout << "Player Special Traits: ";
            for (const auto& trait : playerData["special_traits"]) {
                std::cout << trait << " ";
            }
            std::cout << "Player Defensive and Offensive Work Rate: " << playerData["work_rate"] << std::endl;
            std::cout << "Player Training Work Rate: " << playerData["training"] << std::endl;
            std::cout << "Player Potential Rating: " << playerData["potential"] << std::endl;
            std::cout << "Contract Expiry Date: " << playerData["contract_expiry_date"] << std::endl;
            std::cout << "Player Preffered Role: " << playerData["preffered_role"] << std::endl;
            std::cout << "Player Value: " << playerData["value"] << std::endl;
            std::cout << "Player Wage: " << playerData["wage"] << std::endl;
            std::cout << "Player Morale: " << playerData["morale"] << std::endl;
            std::cout << "Player Consistency: " << playerData["morale"] << std::endl;
            std::cout << "Player Unselfishness: " << playerData["team_player"] << std::endl;

            // Display versatility values
            std::cout << "Player Versatility:" << std::endl;
            if (playerData.contains("versatility")) {
                const json& versatility = playerData["versatility"];
                for (const auto& [position, score] : versatility.items()) {
                    std::cout << "  Position: " << position << ", Score: " << score << std::endl;
                }
            }
            else {
                std::cout << "  No versatility data available." << std::endl;
            }
        }
        
    }
}

void displayNationalityPlayersData() {
    std::cout << "Enter Desired Nation Name: ";
    int selectedNationName;
    std::cin >> selectedNationName;

    std::ifstream playerFile("player_data.json");
    if (!playerFile.is_open()) {
        std::cerr << "Error opening the player data file!" << std::endl;
        return;
    }

    json playerDataArray;
    playerFile >> playerDataArray;
    playerFile.close();
    
    std::cout << "\nPlayers in Team ID " << selectedNationName << ":\n";
    for (const auto& playerData : playerDataArray) {
        if (playerData["nationality"] == selectedNationName)
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Team ID: " << playerData["team_id"] << std::endl;
        std::cout << "Player ID: " << playerData["id"] << std::endl;
        std::cout << "Player Name: " << playerData["name"] << std::endl;
        std::cout << "Player Height: " << playerData["height"] << std::endl;
        std::cout << "Player Weight: " << playerData["weight"] << std::endl;
        std::cout << "Player Nationality: " << playerData["nationality"] << std::endl;
        std::cout << "Player Birthday: " << playerData["date_of_birth"] << std::endl;
        std::cout << "Player Position: " << playerData["position"] << std::endl;
        std::cout << "Player Number: " << playerData["number"] << std::endl;
        std::cout << "Player Is Captain? " << playerData["is_captain"] << std::endl;
        if (playerData["ambidextrous"] == true) {
            std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
        }
        else if (playerData["right_foot"] == true) {
            std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
            std::cout << "Player Is Right Footed" << std::endl;
        }
        else if (playerData["left_foot"] == true) {
            std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
            std::cout << "Player Is Left Footed" << std::endl;
        }
        std::cout << "Player Overall Rating: " << playerData["rating"] << std::endl;
        std::cout << "Player Pace Rating: " << playerData["pace"] << std::endl;
        std::cout << "Player Dribbling Rating: " << playerData["dribbling"] << std::endl;
        std::cout << "Player Passing Rating: " << playerData["passing"] << std::endl;
        std::cout << "Player Shooting Rating: " << playerData["shooting"] << std::endl;
        std::cout << "Player Defending Rating: " << playerData["defending"] << std::endl;
        std::cout << "Player Physicality Rating: " << playerData["physicality"] << std::endl;
        std::cout << "Player Composure Rating: " << playerData["composure"] << std::endl;
        std::cout << "Player Vision Rating: " << playerData["vision"] << std::endl;
        std::cout << "Player Positioning Rating: " << playerData["positioning"] << std::endl;
        std::cout << "Player Shooting Rating: " << playerData["shooting"] << std::endl;
        std::cout << "Player Aggression Rating" << playerData["aggression"] << std::endl;
        std::cout << "Player Penalty Rating: " << playerData["penalty"] << std::endl;
        std::cout << "Player Set Pieces Rating: " << playerData["set_pieces"] << std::endl;
        std::cout << "Player Ball Control Rating: " << playerData["ball_control"] << std::endl;
        std::cout << "Player Stamina Rating: " << playerData["stamina"] << std::endl;
        std::cout << "Player Special Traits: ";
        for (const auto& trait : playerData["special_traits"]) {
            std::cout << trait << " ";
        }
        std::cout << "Player Defensive and Offensive Work Rate: " << playerData["work_rate"] << std::endl;
        std::cout << "Player Training Work Rate: " << playerData["training"] << std::endl;
        std::cout << "Player Potential Rating: " << playerData["potential"] << std::endl;
        std::cout << "Contract Expiry Date: " << playerData["contract_expiry_date"] << std::endl;
        std::cout << "Player Preffered Role: " << playerData["preffered_role"] << std::endl;
        std::cout << "Player Value: " << playerData["value"] << std::endl;
        std::cout << "Player Wage: " << playerData["wage"] << std::endl;
        std::cout << "Player Morale: " << playerData["morale"] << std::endl;
        std::cout << "Player Consistency: " << playerData["morale"] << std::endl;
        std::cout << "Player Unselfishness: " << playerData["team_player"] << std::endl;

        // Display versatility values
        std::cout << "Player Versatility:" << std::endl;
        if (playerData.contains("versatility")) {
            const json& versatility = playerData["versatility"];
            for (const auto& [position, score] : versatility.items()) {
                std::cout << "  Position: " << position << ", Score: " << score << std::endl;
            }
        }
        else {
            std::cout << "  No versatility data available." << std::endl;
        }
    }
}
