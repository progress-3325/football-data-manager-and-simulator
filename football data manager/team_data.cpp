#include <iostream>
#include <fstream>
#include "json.hpp"
#include "team_data.h"

using json = nlohmann::json;

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

        // Find the smallest available ID
        std::vector<int> existingIDs;
        for (const auto& team : teamData) {
            if (team.contains("id")) {
                existingIDs.push_back(team["id"].get<int>());
            }
        }
        int newID = 1;
        sort(existingIDs.begin(), existingIDs.end());
        for (int id : existingIDs) {
            if (id == newID) {
                ++newID;
            }
            else {
                break;
            }
        }

        bool nationalTeam;
        std::string clubName, clubHeadCoach, ultrasName, stadiumName, clubOwner;
        int teamID, clubYearFounded, leagueTitles, cupsWon, stadiumCapacity, squadSize, trainingFacilities, youthClubSquadMembers, youthClubRating, popularity;
        std::vector<int> rivalTeams;
        std::vector<std::string> clubColors;

        teamID = newID;

        std::string ynChoice;
        std::cout << "Is the club a national team? (y/n): ";
        getline(std::cin, ynChoice);
        if (ynChoice == "y" || ynChoice == "Y") {
            nationalTeam = true;
        }
        else if (ynChoice == "n" || ynChoice == "N") {
            nationalTeam = false;
        }

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

        for (int i = 0; i < numRivalries; i++) {
            int rivalryId;
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

        std::cout << "What is the rating of the youth club (1-100) (1 would mean they are the weakest youth club in the country, basically a club for kindergartners, and 100 would mean on par with the first squad): ";
        std::cin >> youthClubRating;
        std::cin.ignore();

        // Create a JSON object and populate it with the team data
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

        std::cout << "Team added with ID: " << newID << std::endl;
    }
}

void displayTeamData() {
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
