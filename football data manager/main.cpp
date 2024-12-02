#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include <vector>
#include <filesystem>
#include <algorithm>

using json = nlohmann::json;

// Function to write player data to a JSON file
static void writePlayerData() {
    // Open or create the JSON file
    json playerDataArray;
    std::ifstream inputFile("player_data.json");
    if (std::filesystem::exists("player_data.json") && inputFile.peek() != std::ifstream::traits_type::eof()) {
        inputFile >> playerDataArray; // Parse existing JSON
    }
    else {
        playerDataArray = json::array(); // Initialize empty array
    }
    inputFile.close();

    // Find the smallest available ID
    std::vector<int> existingIDs;
    for (const auto& player : playerDataArray) {
        if (player.contains("id")) {
            existingIDs.push_back(player["id"].get<int>());
        }
    }
    int newID = 1;
    std::sort(existingIDs.begin(), existingIDs.end());
    for (int id : existingIDs) {
        if (id == newID) {
            ++newID;
        }
        else {
            break;
        }
    }
    int playerID = newID;

    // Prompt user for player data
    std::string playerName, playerPosition;
    int playerRating, playerNumber, pace, dribbling, passing, shooting, defending, physicality;
    bool playerIsCaptain, playerIsAmbidextrous{}, rightFoot, leftFoot;
    float playerHeight, playerWeight;

    std::cout << "Enter player's name: ";
    getline(std::cin, playerName);

    std::cout << "Enter player's height (meters): ";
    std::cin >> playerHeight;
    std::cin.ignore();

    std::cout << "Enter player's weight (kilograms): ";
    std::cin >> playerWeight;
    std::cin.ignore();

    std::cout << "Enter player's position: ";
    getline(std::cin, playerPosition);

    std::cout << "Enter player's number: ";
    std::cin >> playerNumber;
    std::cin.ignore();

    std::string ynChoice;
    std::cout << "Enter if the player is the captain (y/n): ";
    getline(std::cin, ynChoice);
    if (ynChoice == "y" || "Y") {
        playerIsCaptain = true;
    }
    else if (ynChoice == "n" || "N") {
        playerIsCaptain = false;
    }
    else {
        std::cerr << "Invalid character entered, please try again" << std::endl;
    }

    std::cout << "Enter if the player can play with both feet (y/n): ";
    getline(std::cin, ynChoice);
    if (ynChoice == "y" || ynChoice == "Y") {
        playerIsAmbidextrous = true;
    }
    else if (ynChoice == "n" || ynChoice == "N") {
        playerIsAmbidextrous = false;
    }
    else {
        std::cerr << "Invalid character entered, please try again" << std::endl;
    }

    if (playerIsAmbidextrous == false) {
        std::cout << "Is the player right footed (y/n)? ";
        getline(std::cin, ynChoice);
        if (ynChoice == "y" || "Y") {
            rightFoot = true;
            leftFoot = false;
        }
        else if (ynChoice == "n" || "N") {
            rightFoot = false;
            leftFoot = true;
        }
        else {
            std::cerr << "Invalid character entered, please try again" << std::endl;
        }
    }

    std::cout << "Enter how fast the player is (1-100): ";
    std::cin >> pace;
    std::cin.ignore();

    std::cout << "Enter the player's on ball skills (1-100): ";
    std::cin >> dribbling;
    std::cin.ignore();

    std::cout << "Enter the player's passing/crossing accuracy (1-100): ";
    std::cin >> passing;
    std::cin.ignore();

    std::cout << "Enter the player's accuracy and power of a shot (1-100): ";
    std::cin >> shooting;
    std::cin.ignore();

    std::cout << "Enter the player's defending capabilities (1-100): ";
    std::cin >> defending;
    std::cin.ignore();

    std::cout << "Enter the player's strenght and stamina (1-100): ";
    std::cin >> physicality;
    std::cin.ignore();

    std::string position;
    if (playerPosition == "goalkeeper" || playerPosition == "Goalkeeper" || playerPosition == "GK") {
        position = "GK";
        playerRating = (pace * .05) + (dribbling * .05) + (passing * .2) + (shooting * .05) + (defending * .3) + (physicality * .35);
    }
    else if (playerPosition == "center back" || playerPosition == "Center Back" || playerPosition == "CB") {
        position = "CB";
        playerRating = (pace * .15) + (dribbling * .1) + (passing * .15) + (shooting * .05) + (defending * .3) + (physicality * .25);
    }
    else if (playerPosition == "left back" || playerPosition == "Left Back" || playerPosition == "LB") {
        position = "LB";
        playerRating = (pace * .25) + (dribbling * .15) + (passing * .2) + (shooting * .05) + (defending * .25) + (physicality * .1);
    }
    else if (playerPosition == "right back" || playerPosition == "Right Back" || playerPosition == "RB") {
        position = "RB";
        playerRating = playerRating = (pace * .25) + (dribbling * .15) + (passing * .2) + (shooting * .05) + (defending * .25) + (physicality * .1);
    }
    else if (playerPosition == "light wing-back" || playerPosition == "Light Wing-Back" || playerPosition == "LWB") {
        position = "LWB";
        playerRating = (pace * .3) + (dribbling * .2) + (passing * .2) + (shooting * .05) + (defending * .15) + (physicality * .1);
    }
    else if (playerPosition == "right wing-back" || playerPosition == "Right Wing-Back" || playerPosition == "RWB") {
        position = "RWB";
        playerRating = (pace * .3) + (dribbling * .2) + (passing * .2) + (shooting * .05) + (defending * .15) + (physicality * .1);
    }
    else if (playerPosition == "sweeper" || playerPosition == "Sweeper" || playerPosition == "SW") {
        position = "SW";
        playerRating = (pace * .2) + (dribbling * .1) + (passing * .2) + (shooting * .05) + (defending * .35) + (physicality * .1);
    }
    else if (playerPosition == "defensive midfielder" || playerPosition == "Defensive Midfielder" || playerPosition == "DM") {
        position = "DM";
        playerRating = (pace * .15) + (dribbling * .15) + (passing * .25) + (shooting * .05) + (defending * .3) + (physicality * .1);
    }
    else if (playerPosition == "central defensive midfielder" || playerPosition == "Central Defensive Midfielder" || playerPosition == "CDM") {
        position = "CDM";
        playerRating = (pace * .15) + (dribbling * .2) + (passing * .25) + (shooting * .05) + (defending * .25) + (physicality * .1);
    }
    else if (playerPosition == "central midfielder" || playerPosition == "Central Midfielder" || playerPosition == "CM") {
        position = "CM";
        playerRating = (pace * 0.15) + (dribbling * 0.2) + (passing * 0.3) + (shooting * 0.15) + (defending * 0.1) + (physicality * 0.1);
    }
    else if (playerPosition == "left midfielder" || playerPosition == "Left Midfielder" || playerPosition == "LM") {
        position = "LM";
        playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.15) + (defending * 0.05) + (physicality * 0.1);
    }
    else if (playerPosition == "right midfielder" || playerPosition == "Right Midfielder" || playerPosition == "RM") {
        position = "RM";
        playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.15) + (defending * 0.05) + (physicality * 0.1);
    }
    else if (playerPosition == "central attacking midfielder" || playerPosition == "Central Attacking Midfielder" || playerPosition == "CAM") {
        position = "CAM";
        playerRating = (dribbling * 0.3) + (passing * 0.3) + (shooting * 0.2) + (pace * 0.1) + (physicality * 0.05) + (defending * 0.05);
    }
    else if (playerPosition == "attacking midfielder" || playerPosition == "Attacking Midfielder" || playerPosition == "AM") {
        position = "AM";
        playerRating = (dribbling * 0.3) + (passing * 0.3) + (shooting * 0.2) + (pace * 0.1) + (physicality * 0.05) + (defending * 0.05);
    }
    else if (playerPosition == "wide midfielder" || playerPosition == "Wide Midfielder" || playerPosition == "W") {
        position = "W";
        playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.25) + (shooting * 0.1) + (defending * 0.1) + (physicality * 0.05);
    }
    else if (playerPosition == "center forward" || playerPosition == "Center Forward" || playerPosition == "CF") {
        position = "CF";
        playerRating = (pace * 0.15) + (dribbling * 0.2) + (passing * 0.1) + (shooting * 0.4) + (defending * 0.05) + (physicality * 0.1);
    }
    else if (playerPosition == "striker" || playerPosition == "Striker" || playerPosition == "ST") {
        position = "ST";
        playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
    }
    else if (playerPosition == "left winger" || playerPosition == "Left Winger" || playerPosition == "LW") {
        position = "LW";
        playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
    }
    else if (playerPosition == "right winger" || playerPosition == "Right Winger" || playerPosition == "RW") {
        position = "RW";
        playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
    }
    else if (playerPosition == "second striker" || playerPosition == "Second Striker" || playerPosition == "SS") {
        position = "SS";
        playerRating = (pace * 0.15) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.3) + (defending * 0.05) + (physicality * 0.05);
    }

    // Create a JSON object for the new player
    json newPlayer = {
        {"id", playerID},
        {"name", playerName},
        {"rating", playerRating},
        {"position", position},
        {"number", playerNumber},
        {"is_captain", playerIsCaptain},
        {"ambidextrous", playerIsAmbidextrous},
        {"right_foot", rightFoot},
        {"left_foot", leftFoot},
        {"pace", pace},
        {"dribbling", dribbling},
        {"passing", passing},
        {"shooting", shooting},
        {"defending", defending},
        {"physicality", physicality}
    };

    // Add the new player to the array
    playerDataArray.push_back(newPlayer);

    // Write updated data back to file
    std::ofstream outputFile("player_data.json");
    if (outputFile.is_open()) {
        outputFile << playerDataArray.dump(4); // Pretty print with indentation
        std::cout << "Player data saved to player_data.json\n";
        outputFile.close();
    }
    else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
}


static void writeTeamData() {
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

static void displayPlayerData() {
    std::ifstream file("player_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening the JSON file!" << std::endl;
        return;
    }
    json playerDataArray;
    file >> playerDataArray;
    file.close();

    if (!playerDataArray.is_array()) {
        std::cerr << "Error: JSON data is not an array!" << std::endl;
        return;
    }

    for (const auto& playerData : playerDataArray) {
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Player ID: " << playerData["id"] << std::endl;
        std::cout << "Player Name: " << playerData["name"] << std::endl;
        std::cout << "Player Position: " << playerData["position"] << std::endl;
        std::cout << "Player Overall Rating: " << playerData["rating"] << std::endl;
        std::cout << "Player Pace Rating: " << playerData["pace"] << std::endl;
        std::cout << "Player Dribbling Rating: " << playerData["dribbling"] << std::endl;
        std::cout << "Player Passing Rating: " << playerData["passing"] << std::endl;
        std::cout << "Player Shooting Rating: " << playerData["shooting"] << std::endl;
        std::cout << "Player Defending Rating: " << playerData["defending"] << std::endl;
        std::cout << "Player Physicality Rating: " << playerData["physicality"] << std::endl;
        std::cout << "Player Number: " << playerData["number"] << std::endl;

    }
}

static void displayTeamData() {
    // Open and read the JSON file
    std::ifstream file("team_data.json");
    if (!file.is_open()) {
        std::cerr << "Error opening JSON file!" << std::endl;
        return;
    }

    json teamDataArray;
    file >> teamDataArray; // Parse the JSON file
    file.close();

    // Check if the data is an array
    if (!teamDataArray.is_array()) {
        std::cerr << "Error: JSON data is not an array!" << std::endl;
        return;
    }

    // Iterate through each team and display its data
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
        std::cout << "---------------------------------" << std::endl;
    }

    std::cout << "End of team data." << std::endl;
}

int main() {
    int choice;

    while (true) {
        // Display the menu to the user
        std::cout << "\nMenu:\n";
        std::cout << "1. Write Player Data\n";
        std::cout << "2. Write Team Data\n";
        std::cout << "3. Read Player Data\n";
        std::cout << "4. Read Team Data\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Clear the input buffer after reading the choice

        // Handle user input based on the menu choice
        switch (choice) {
        case 1:
            writePlayerData();  // Call the function to write player data
            break;
        case 2:
            writeTeamData();    // Call the function to write team data
            break;
        case 3:
            displayPlayerData();
            break;
        case 4:
            displayTeamData();
            break;
        case 5:
            std::cout << "Exiting program...\n";
            return 0;  // Exit the program
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
