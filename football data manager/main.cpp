#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include <vector>
#include <filesystem>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

// Function to write player data to a JSON file
static void writePlayerData() {
    string playerName, playerPosition;
    int playerRating, playerNumber;

    cout << "Enter player's name: ";
    getline(cin, playerName);

    cout << "Enter player's rating (1-100): ";
    cin >> playerRating;
    cin.ignore();  // Clear the input buffer

    cout << "Enter player's position: ";
    getline(cin, playerPosition);

    cout << "Enter player's number: ";
    cin >> playerNumber;

    // Create a JSON object and populate it with the player data
    json playerData;
    playerData["name"] = playerName;
    playerData["rating"] = playerRating;
    playerData["position"] = playerPosition;
    playerData["number"] = playerNumber;

    // Write the player data to player_data.json
    ofstream outputFile("player_data.json");
    if (outputFile.is_open()) {
        outputFile << playerData.dump(4);  // Pretty print with indentation
        cout << "Player data saved to player_data.json\n";
        outputFile.close();
    }
    else {
        cerr << "Error opening file for writing!" << endl;
    }
}

// Function to write team data to a JSON file
static void writeTeamData() {
    // Open or create the JSON file
    fstream file("team_data.json", ios::in | ios::out | ios::app);
    json teamData;

    // Read existing data or initialize empty array
    if (filesystem::exists("team_data.json") && file.peek() != ifstream::traits_type::eof()) {
        file >> teamData; // Parse existing JSON
    }
    else {
        teamData = json::array(); // Initialize empty array
    }
    file.close();

    // Find the smallest available ID
    vector<int> existingIDs;
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
    string clubName, clubHeadCoach, ultrasName, stadiumName, clubOwner;
    int teamID, clubYearFounded, leagueTitles, cupsWon, stadiumCapacity, squadSize, trainingFacilities;
    vector<int> rivalTeams;
    vector<string> clubColors;

    teamID = newID;

    string ynChoice;
    cout << "Is the club a national team? (y/n): ";
    getline(cin, ynChoice);
    if (ynChoice == "y") {
        nationalTeam = true;
    }
    else if (ynChoice == "n") {
        nationalTeam = false;
    }

    cout << "Enter club's name: ";
    getline(cin, clubName);

    cout << "Enter club's head coach: ";
    getline(cin, clubHeadCoach);

    cout << "Enter the year the club was founded: ";
    cin >> clubYearFounded;

    cout << "Enter how many league cups has the club won until now (if national team enter -1): ";
    cin >> leagueTitles;
    cin.ignore();

    cout << "Enter how many national cups has the club won (if national team enter -1): ";
    cin >> cupsWon;
    cin.ignore();

    cout << "Enter the total amount of players (if national team enter the call ups): ";
    cin >> squadSize;
    cin.ignore();

    cout << "Enter the rating of the club's training facilities (enter from 1 to 5,if national team enter -1): ";
    cin >> trainingFacilities;
    cin.ignore();

    int numRivalries;
    cout << "Enter number of rival teams: ";
    cin >> numRivalries;

    for (int i = 0; i < numRivalries; i++) {
        int rivalryId;
        cout << "Enter rival team ID " << i + 1 << ": ";
        cin >> rivalryId;
        cin.ignore();
        rivalTeams.push_back(rivalryId);
    }

    cout << "Enter the name of the club's fans: ";
    getline(cin, ultrasName);

    cout << "Enter the name of the club's stadium: ";
    getline(cin, stadiumName);

    cout << "Enter the stadium capacity: ";
    cin >> stadiumCapacity;
    cin.ignore();

    cout << "Enter the name of the person and/or organization that owns the club: ";
    getline(cin, clubOwner);

    int numColors;
    cout << "Enter how many main colors does your team have: ";
    cin >> numColors;
    cin.ignore();
    for (int i = 0; i < numColors; i++) {
        string color;
        cout << "Enter color name (or hex code): ";
        getline(cin, color);
        clubColors.push_back(color);
    }

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
        {"stadium_capacity", stadiumCapacity}
    };
    
    teamData.push_back(newTeam);
    ofstream outFile("team_data.json");
    outFile << teamData.dump(4); // Pretty-print with 4-space indentation
    outFile.close();

    cout << "Team added with ID: " << newID << endl;
}

static void displayTeamData() {
    // Open and read the JSON file
    ifstream file("team_data.json");
    if (!file.is_open()) {
        cerr << "Error opening JSON file!" << endl;
        return;
    }

    json teamData;
    file >> teamData; // Parse the JSON file
    file.close();

    // Print in desired order
    cout << "National team: " << teamData["national_team"] << endl;
    cout << "Club Name: " << teamData["name"] << endl;
    cout << "Head Coach: " << teamData["head_coach"] << endl;
    cout << "Year Founded: " << teamData["year_founded"] << endl;
    cout << "Owner: " << teamData["club_owner"] << endl;

    cout << "Colors: ";
    for (const auto& color : teamData["club_color(s)"]) {
        cout << color << " ";
    }
    cout << endl;

    cout << "League Titles: " << teamData["league_titles"] << endl;
    cout << "National Cup Titles: " << teamData["national_cup_titles"] << endl;
    cout << "Squad Size: " << teamData["squad_size"] << endl;
    cout << "Training Facilities Rating: " << teamData["training_facilities_rating"] << endl;
    cout << "Stadium Name: " << teamData["stadium_name"] << endl;
    cout << "Stadium Capacity: " << teamData["stadium_capacity"] << endl;

    // Print rival teams
    cout << "Rival Teams: ";
    for (const auto& id : teamData["rival_teams"]) {
        cout << id << " ";
    }
    cout << endl;

    cout << "Fan Group Name: " << teamData["fans_name"] << endl;
}

int main() {
    int choice;

    while (true) {
        // Display the menu to the user
        cout << "\nMenu:\n";
        cout << "1. Write Player Data\n";
        cout << "2. Write Team Data\n";
        cout << "3. Read Player Data\n";
        cout << "4. Read Team Data\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear the input buffer after reading the choice

        // Handle user input based on the menu choice
        switch (choice) {
        case 1:
            writePlayerData();  // Call the function to write player data
            break;
        case 2:
            writeTeamData();    // Call the function to write team data
            break;
        case 3:
            cout << "Not yet available.\n";
            break;
        case 4:
            displayTeamData();
            break;
        case 5:
            cout << "Exiting program...\n";
            return 0;  // Exit the program
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
