#include <iostream>
#include <fstream>
#include "json.hpp"
#include "player_data.h"
#include <ctime>

// player_data.cpp
// adds the role of functions defined in "player_data.h"
// with user input, creates a file with all the needed data
// it can read "player_data.json" and properly organize it

// progress-3325

using json = nlohmann::json;

// writePlayerData()
// Purpose: 
// Writes player data from user input and saves it into a .json file.
// Inputs:
// Questions will be asked, and the answers will go to the respective variables as values.
// Example Input:
// Enter player's name: Player A
// Enter player's height (meters): 1.82
// Enter player's nationality: Romania
// Enter ID of player's team: 1
// Enter player's date of birth: 6/6/2000
// Enter player's weight (kilograms): 100
// Enter player's position: Striker
// Enter player's number: 15
// Enter if the player is the captain(y / n) : y
// Enter if the player can play with both feet(y / n) : y
// Enter how fast the player is(1 - 100) : 100
// Enter player's on ball skills (1-100): 100
// Enter player's passing/crossing accuracy (1-100): 100
// Enter player's accuracy and power of a shot (1-100): 100
// Enter player's defending capabilities (1-100): 100
// Enter player's strenght and stamina (1-100): 100
// Enter player's Composure (1-100): 100
// Enter player's Vision (1-100): 100
// Enter player's Positioning (1-100): 100
// Enter player's aggression: 100
// Enter player's Long Shots (1-100): 100
// Enter player's Defensive Work Rate (1-3): 3
// Enter player's Offensive Work Rate (1-3): 3
// Enter player's Contract Expiry Date: 7/7/2077
// Enter player's Estimated Market Value: 196000000
// Enter player's Wage: 1550000
// Outputs: 
// "player_data.json" file.
// Example Output:
// Player data saved to player_data.json
// [
// {
//        "ambidextrous": true,
//        "defending" : 100,
//        "dribbling" : 100,
//        "id" : 1,
//        "is_captain" : true,
//        "left_foot" : true,
//        "name" : "Player A",
//        "number" : 15,
//        "pace" : 100,
//        "passing" : 100,
//        "physicality" : 100,
//        "position" : "ST",
//        "rating" : 100,
//        "right_foot" : true,
//        "shooting" : 100,
//        "work_rate" : "high/high"
// }
// ]
void writePlayerData() {
    {
        srand(time(NULL));
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
        std::string playerName, playerPosition, playerNationality, dateOfBirth, contractExpiryDate, workRate;
        int playerRating, playerNumber, pace, dribbling, passing, shooting, defending, physicality, playerValue, playerWage, composure, vision, positioning, longShots, defWorkRate, offWorkRate, teamID, aggression, penaltyShoot, setPiece, ballControl, stamina, injuryProne;
        bool playerIsCaptain, playerIsAmbidextrous{}, rightFoot, leftFoot;
        float playerHeight, playerWeight;

        std::cout << "Enter player's name: ";
        getline(std::cin, playerName);

        std::cout << "Enter player's height (meters): ";
        std::cin >> playerHeight;
        std::cin.ignore();

        std::cout << "Enter player's nationality: ";
        getline(std::cin, playerNationality);

        std::cout << "Enter ID of player's team: ";
        std::cin >> teamID;
        std::cin.ignore();

        std::cout << "Enter player's date of birth: ";
        getline(std::cin, dateOfBirth);

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

        std::cout << "Enter player's on ball skills (1-100): ";
        std::cin >> dribbling;
        std::cin.ignore();

        std::cout << "Enter player's passing/crossing accuracy (1-100): ";
        std::cin >> passing;
        std::cin.ignore();

        std::cout << "Enter player's accuracy and power of a shot (1-100): ";
        std::cin >> shooting;
        std::cin.ignore();

        std::cout << "Enter player's defending capabilities (1-100): ";
        std::cin >> defending;
        std::cin.ignore();

        std::cout << "Enter player's strenght and stamina (1-100): ";
        std::cin >> physicality;
        std::cin.ignore();

        std::cout << "Enter player's Composure (1-100): ";
        std::cin >> composure;
        std::cin.ignore();

        std::cout << "Enter player's Vision (1-100): ";
        std::cin >> vision;
        std::cin.ignore();

        std::cout << "Enter player's Positioning (1-100): ";
        std::cin >> positioning;
        std::cin.ignore();

        std::cout << "Enter player's aggression: ";
        std::cin >> aggression;
        std::cin.ignore();

        std::cout << "Enter player's Long Shots (1-100): ";
        std::cin >> longShots;
        std::cin.ignore();

        std::cout << "Enter player's Defensive Work Rate (1-3): ";
        std::cin >> defWorkRate;
        std::cin.ignore();

        std::cout << "Enter player's Offensive Work Rate (1-3): ";
        std::cin >> offWorkRate;
        std::cin.ignore();

        if (defWorkRate == 1) {
            if (offWorkRate == 1) {
                workRate = "low/low";
            }
            else if (offWorkRate == 2) {
                workRate = "low/mid";
            }
            else if (offWorkRate == 3) {
                workRate = "low/high";
            }
            else {
                std::cerr << "Invalid Offensive Work Rate number inserted";
                return;
            }
        }
        else if (defWorkRate == 2) {
            if (offWorkRate == 1) {
                workRate = "mid/low";
            }
            else if (offWorkRate == 2) {
                workRate = "mid/mid";
            }
            else if (offWorkRate == 3) {
                workRate = "mid/high";
            }
            else {
                std::cerr << "Invalid Offensive Work Rate number inserted";
                return;
            }
        }
        else if (defWorkRate == 3) {
            if (offWorkRate == 1) {
                workRate = "high/low";
            }
            else if (offWorkRate == 2) {
                workRate = "high/mid";
            }
            else if (offWorkRate == 3) {
                workRate = "high/high";
            }
            else {
                std::cerr << "Invalid Offensive Work Rate number inserted";
                return;
            }
        }
        else {
            std::cerr << "Invalid Defensive Work Rate number inserted";
            return;
        }

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

        std::cout << "Enter player's Contract Expiry Date: ";
        getline(std::cin, contractExpiryDate);

        std::cout << "Enter player's Estimated Market Value: ";
        std::cin >> playerValue;
        std::cin.ignore();

        std::cout << "Enter player's Wage: ";
        std::cin >> playerWage;
        std::cin.ignore();

        penaltyShoot = (shooting * .35) + (composure * .65);
        setPiece = (passing * .55) + (composure * .45);
        ballControl = (dribbling * .3) + (composure * .7);

        int chance = rand() % 4;
        if (chance == 0) {
            stamina = physicality;
        }
        else if (chance == 1) {
            stamina = physicality / 1.3;
        }
        else if (chance == 2) {
            stamina = physicality / 1.6;
        }
        else if (chance == 3) {
            stamina = physicality / 1.8;
        }
        else if (chance == 4) {
            stamina = physicality / 2;
        }
        stamina = stamina;
        injuryProne = stamina - physicality + 100;

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
            {"physicality", physicality},
            {"work_rate", workRate}
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
}

// displayPlayerData()
// Purpose:
// Reads and organizes values from "player_data.json".
// Input:
// None
// Output:
// Contents of "player_data.json" in a set order by the script.
// Example Output:
// Player ID: 1
// Player Name : "Player A"
// Player Position : "ST"
// Player Overall Rating : 100
// Player Pace Rating : 100
// Player Dribbling Rating : 100
// Player Passing Rating : 100
// Player Shooting Rating : 100
// Player Defending Rating : 100
// Player Physicality Rating : 100
// Player Number : 15
void displayPlayerData() {
    std::ifstream file("player_data.json"); // Get player data.
    if (!file.is_open()) {
        std::cerr << "Error opening the JSON file!" << std::endl;
        return;
    } // If player data wasn't saved then the function process will end.

    json playerDataArray; // Defining the array.
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
    } // Reading player data.
}
