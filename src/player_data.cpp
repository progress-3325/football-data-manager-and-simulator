#include <iostream>
#include <fstream>
#include "json.hpp"
#include "player_data.h"
#include <ctime>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <random>
#include "func.h"

using json = nlohmann::json;

void writePlayerData()
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Declare a JSON object to hold player data
    json playerDataArray;

    // Open the JSON file containing player data
    std::fstream file("../data/player_data.json", std::ios::in | std::ios::out | std::ios::app);

    // Check if the file exists and is not empty
    if (std::filesystem::exists("player_data.json") && file.peek() != std::ifstream::traits_type::eof()) {
        file >> playerDataArray; // Parse existing JSON data into the playerDataArray
    }
    else {
        playerDataArray = json::array(); // Initialize an empty JSON array if the file doesn't exist or is empty
    }
    file.close(); // Close the input file

    // Declare variables to store player information
    std::string playerID, playerName, playerPosition, playerNationality, dateOfBirth, contractExpiryDate, workRate, prefferedRole, teamID;
    int playerNumber, pace, dribbling, passing, shooting, defending, physicality, playerValue, playerWage, composure, vision, positioning, longShots, defWorkRate, offWorkRate, aggression, penaltyShoot, setPiece, ballControl, stamina{}, injuryProne, matchesPlayed, goalsScored, assists, cleanSheets, tacklesWon, shotsOnTarget, specialTraitsNum, trainingWorkRate;
    float playerRating, passingAccuracy, potentialRating, clutchFactor, playerHeight, playerWeight, morale, consistency, teamPlayer;
    bool playerIsCaptain, playerIsAmbidextrous{}, rightFoot, leftFoot;
    std::vector<std::string> specialTraits; // Vector to store special traits of the player
    std::map<std::string, int> positionVersatility; // Map to store versatility scores for different positions
    std::vector<std::string> positions = { "Goalkeeper", "Center Back", "Left Back", "Right Back", "Left Wing-Back", "Right Wing-Back", "Sweeper", "Central Midfielder", "Left Midfielder", "Right Midfielder", "Central Attacking Midfielder", "Attacking Midfielder", "Wide Midfielder", "Left Defensive Midfielder", "Right Defensive Midfielder", "Central Defensive Midfielder", "Center Forward", "Left Winger", "Right Winger", "Striker", "Second Striker" };
    int versatilityScore = 0; // Variable to store versatility score

    // Generate a unique player ID
    playerID = generatePlayerID();

    // Prompt the user to enter the player's name
    std::cout << "Enter player's name: ";
    getline(std::cin, playerName);

    // Prompt the user to enter the player's height in meters
    std::cout << "Enter player's height (meters): ";
    std::cin >> playerHeight;
    std::cin.ignore(); // Ignore the newline character left in the input buffer

    // Prompt the user to enter the player's nationality
    std::cout << "Enter player's nationality: ";
    getline(std::cin, playerNationality);

    // Prompt the user to enter the player's team ID
    std::cout << "Enter ID of player's team: ";
    std::getline(std::cin, teamID);

    // Prompt the user to enter the player's date of birth
    std::cout << "Enter player's date of birth: ";
    getline(std::cin, dateOfBirth);

    // Prompt the user to enter the player's weight in kilograms
    std::cout << "Enter player's weight (kilograms): ";
    std::cin >> playerWeight;
    std::cin.ignore();

    // Prompt the user to enter the player's position
    std::cout << "Enter player's position: ";
    getline(std::cin, playerPosition);

    // Prompt the user to enter the player's jersey number
    std::cout << "Enter player's number: ";
    std::cin >> playerNumber;
    std::cin.ignore();

    // Prompt the user to specify if the player is the captain
    std::string ynChoice;
    std::cout << "Enter if the player is the captain (y/n): ";
    getline(std::cin, ynChoice);
    if (ynChoice == "y" || "Y") {
        playerIsCaptain = true; // Set captain status to true
    }
    else if (ynChoice == "n" || "N") {
        playerIsCaptain = false; // Set captain status to false
    }
    else {
        std::cerr << "Invalid character entered, please try again" << std::endl; // Handle invalid input
    }

    // Prompt the user to specify if the player can play with both feet
    std::cout << "Enter if the player can play with both feet (y/n): ";
    getline(std::cin, ynChoice);
    if (ynChoice == "y" || ynChoice == "Y") {
        playerIsAmbidextrous = true; // Set ambidextrous status to true
    }
    else if (ynChoice == "n" || ynChoice == "N") {
        playerIsAmbidextrous = false; // Set ambidextrous status to false
    }
    else {
        std::cerr << "Invalid character entered, please try again" << std::endl; // Handle invalid input
    }

    // If the player is not ambidextrous, determine their dominant foot
    if (!playerIsAmbidextrous) {
        std::cout << "Is the player right footed (y/n)? ";
        getline(std::cin, ynChoice);
        if (ynChoice == "y" || "Y") {
            rightFoot = true; // Set right footed status to true
            leftFoot = false; // Set left footed status to false
        }
        else if (ynChoice == "n" || "N") {
            rightFoot = false; // Set right footed status to false
            leftFoot = true; // Set left footed status to true
        }
        else {
            std::cerr << "Invalid character entered, please try again" << std::endl; // Handle invalid input
        }
    }

    // Prompt the user to enter the player's pace rating
    std::cout << "Enter how fast the player is (1-100): ";
    std::cin >> pace;
    std::cin.ignore();

    // Prompt the user to enter the player's dribbling rating
    std::cout << "Enter player's on ball skills (1-100): ";
    std::cin >> dribbling;
    std::cin.ignore();

    // Prompt the user to enter the player's passing rating
    std::cout << "Enter player's passing/crossing accuracy (1-100): ";
    std::cin >> passing;
    std::cin.ignore();

    // Prompt the user to enter the player's shooting rating
    std::cout << "Enter player's accuracy and power of a shot (1-100): ";
    std::cin >> shooting;
    std::cin.ignore();

    // Prompt the user to enter the player's defending rating
    std::cout << "Enter player's defending capabilities (1-100): ";
    std::cin >> defending;
    std::cin.ignore();

    // Prompt the user to enter the player's physicality rating
    std::cout << "Enter player's strenght and stamina (1-100): ";
    std::cin >> physicality;
    std::cin.ignore();

    // Prompt the user to enter the player's composure rating
    std::cout << "Enter player's Composure (1-100): ";
    std::cin >> composure;
    std::cin.ignore();

    // Prompt the user to enter the player's vision rating
    std::cout << "Enter player's Vision (1-100): ";
    std::cin >> vision;
    std::cin.ignore();

    // Prompt the user to enter the player's positioning rating
    std::cout << "Enter player's Positioning (1-100): ";
    std::cin >> positioning;
    std::cin.ignore();

    // Prompt the user to enter the player's aggression rating
    std::cout << "Enter player's aggression: ";
    std::cin >> aggression;
    std::cin.ignore();

    // Prompt the user to enter the player's long shots rating
    std::cout << "Enter player's Long Shots (1-100): ";
    std::cin >> longShots;
    std::cin.ignore();

    std::vector<int> attributes = {
        pace, dribbling, passing, defending, shooting, physicality, composure, vision, positioning, aggression, longShots
    };

    // Prompt the user to enter the player's defensive work rate
    std::cout << "Enter player's Defensive Work Rate (1-3): ";
    std::cin >> defWorkRate;
    std::cin.ignore();

    // Prompt the user to enter the player's offensive work rate
    std::cout << "Enter player's Offensive Work Rate (1-3): ";
    std::cin >> offWorkRate;
    std::cin.ignore();

    // Prompt the user to enter the player's training work rate
    std::cout << "Enter player's Training Work Rate (1-3): ";
    std::cin >> trainingWorkRate;
    std::cin.ignore();

    // Determine the player's work rate based on defensive and offensive work rates
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

    // Determine the player's training work rate description
    std::string trainingWR;
    if (trainingWorkRate == 1) {
        trainingWR = "Low";
    }
    else if (trainingWorkRate == 2) {
        trainingWR = "Mid";
    }
    else if (trainingWorkRate == 3) {
        trainingWR = "High";
    }

    // Prompt the user to enter the number of special traits the player has
    std::cout << "Enter how many special traits the player has: ";
    std::cin >> specialTraitsNum;
    std::cin.ignore();

    // Collect the names of the player's special traits
    for (int i = 0; i < specialTraitsNum; i++) {
        std::string specialTraitName;
        std::cout << "Enter special trait name " << i + 1 << ": ";
        getline(std::cin, specialTraitName);
        specialTraits.push_back(specialTraitName);
    }

    // Prompt the user to enter the player's potential rating
    std::cout << "Enter player's Potential Rating: ";
    std::cin >> potentialRating;
    std::cin.ignore();

    // Declare a string variable to store the player's position
    std::string position;

    // Check if the player's position matches "goalkeeper" or its variations
    if (playerPosition == "goalkeeper" || playerPosition == "Goalkeeper" || playerPosition == "GK") {
        position = "GK"; // Assign the position abbreviation
        // Calculate the player's rating based on weighted attributes
        playerRating = (pace * .05) + (dribbling * .05) + (passing * .2) + (shooting * .05) + (defending * .3) + (physicality * .35);
    }
    // Check if the player's position matches "center back" or its variations
    else if (playerPosition == "center back" || playerPosition == "Center Back" || playerPosition == "CB") {
        position = "CB";
        playerRating = (pace * .15) + (dribbling * .1) + (passing * .15) + (shooting * .05) + (defending * .3) + (physicality * .25);
    }
    // Check if the player's position matches "left back" or its variations
    else if (playerPosition == "left back" || playerPosition == "Left Back" || playerPosition == "LB") {
        position = "LB";
        playerRating = (pace * .25) + (dribbling * .15) + (passing * .2) + (shooting * .05) + (defending * .25) + (physicality * .1);
    }
    // Check if the player's position matches "right back" or its variations
    else if (playerPosition == "right back" || playerPosition == "Right Back" || playerPosition == "RB") {
        position = "RB";
        playerRating = (pace * .25) + (dribbling * .15) + (passing * .2) + (shooting * .05) + (defending * .25) + (physicality * .1);
    }
    // Check if the player's position matches "light wing-back" or its variations
    else if (playerPosition == "light wing-back" || playerPosition == "Light Wing-Back" || playerPosition == "LWB") {
        position = "LWB";
        playerRating = (pace * .3) + (dribbling * .2) + (passing * .2) + (shooting * .05) + (defending * .15) + (physicality * .1);
    }
    // Check if the player's position matches "right wing-back" or its variations
    else if (playerPosition == "right wing-back" || playerPosition == "Right Wing-Back" || playerPosition == "RWB") {
        position = "RWB";
        playerRating = (pace * .3) + (dribbling * .2) + (passing * .2) + (shooting * .05) + (defending * .15) + (physicality * .1);
    }
    // Check if the player's position matches "sweeper" or its variations
    else if (playerPosition == "sweeper" || playerPosition == "Sweeper" || playerPosition == "SW") {
        position = "SW";
        playerRating = (pace * .2) + (dribbling * .1) + (passing * .2) + (shooting * .05) + (defending * .35) + (physicality * .1);
    }
    // Check if the player's position matches "defensive midfielder" or its variations
    else if (playerPosition == "defensive midfielder" || playerPosition == "Defensive Midfielder" || playerPosition == "DM") {
        position = "DM";
        playerRating = (pace * .15) + (dribbling * .15) + (passing * .25) + (shooting * .05) + (defending * .3) + (physicality * .1);
    }
    // Check if the player's position matches "left defensive midfielder" or its variations
    else if (playerPosition == "left defensive midfielder" || playerPosition == "Left Defensive Midfielder" || playerPosition == "LDM") {
        position = "LDM";
        playerRating = (pace * .15) + (dribbling * .15) + (passing * .25) + (shooting * .05) + (defending * .3) + (physicality * .1);
    }
    // Check if the player's position matches "right defensive midfielder" or its variations
    else if (playerPosition == "right defensive midfielder" || playerPosition == "Right Defensive Midfielder" || playerPosition == "RDM") {
        position = "RDM";
        playerRating = (pace * .15) + (dribbling * .15) + (passing * .25) + (shooting * .05) + (defending * .3) + (physicality * .1);
    }
    // Check if the player's position matches "central defensive midfielder" or its variations
    else if (playerPosition == "central defensive midfielder" || playerPosition == "Central Defensive Midfielder" || playerPosition == "CDM") {
        position = "CDM";
        playerRating = (pace * .15) + (dribbling * .2) + (passing * .25) + (shooting * .05) + (defending * .25) + (physicality * .1);
    }
    // Check if the player's position matches "central midfielder" or its variations
    else if (playerPosition == "central midfielder" || playerPosition == "Central Midfielder" || playerPosition == "CM") {
        position = "CM";
        playerRating = (pace * 0.15) + (dribbling * 0.2) + (passing * 0.3) + (shooting * 0.15) + (defending * 0.1) + (physicality * 0.1);
    }
    // Check if the player's position matches "left midfielder" or its variations
    else if (playerPosition == "left midfielder" || playerPosition == "Left Midfielder" || playerPosition == "LM") {
        position = "LM";
        playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.15) + (defending * 0.05) + (physicality * 0.1);
    }
    // Check if the player's position matches "right midfielder" or its variations
    else if (playerPosition == "right midfielder" || playerPosition == "Right Midfielder" || playerPosition == "RM") {
        position = "RM";
        playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.15) + (defending * 0.05) + (physicality * 0.1);
    }
    // Check if the player's position matches "central attacking midfielder" or its variations
    else if (playerPosition == "central attacking midfielder" || playerPosition == "Central Attacking Midfielder" || playerPosition == "CAM") {
        position = "CAM";
        playerRating = (dribbling * 0.3) + (passing * 0.3) + (shooting * 0.2) + (pace * 0.1) + (physicality * 0.05) + (defending * 0.05);
    }
    // Check if the player's position matches "attacking midfielder" or its variations
    else if (playerPosition == "attacking midfielder" || playerPosition == "Attacking Midfielder" || playerPosition == "AM") {
        position = "AM";
        playerRating = (dribbling * 0.3) + (passing * 0.3) + (shooting * 0.2) + (pace * 0.1) + (physicality * 0.05) + (defending * 0.05);
    }
    // Check if the player's position matches "wide midfielder" or its variations
    else if (playerPosition == "wide midfielder" || playerPosition == "Wide Midfielder" || playerPosition == "W") {
        position = "W";
        playerRating = (pace * 0.25) + (dribbling * 0.25) + (passing * 0.25) + (shooting * 0.1) + (defending * 0.1) + (physicality * 0.05);
    }
    // Check if the player's position matches "center forward" or its variations
    else if (playerPosition == "center forward" || playerPosition == "Center Forward" || playerPosition == "CF") {
        position = "CF";
        playerRating = (pace * 0.15) + (dribbling * 0.2) + (passing * 0.1) + (shooting * 0.4) + (defending * 0.05) + (physicality * 0.1);
    }
    // Check if the player's position matches "striker" or its variations
    else if (playerPosition == "striker" || playerPosition == "Striker" || playerPosition == "ST") {
        position = "ST";
        playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
    }
    // Check if the player's position matches "left winger" or its variations
    else if (playerPosition == "left winger" || playerPosition == "Left Winger" || playerPosition == "LW") {
        position = "LW";
        playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
    }
    // Check if the player's position matches "right winger" or its variations
    else if (playerPosition == "right winger" || playerPosition == "Right Winger" || playerPosition == "RW") {
        position = "RW";
        playerRating = (pace * 0.2) + (dribbling * 0.15) + (passing * 0.05) + (shooting * 0.5) + (defending * 0.01) + (physicality * 0.09);
    }
    // Check if the player's position matches "second striker" or its variations
    else if (playerPosition == "second striker" || playerPosition == "Second Striker" || playerPosition == "SS") {
        position = "SS";
        playerRating = (pace * 0.15) + (dribbling * 0.25) + (passing * 0.2) + (shooting * 0.3) + (defending * 0.05) + (physicality * 0.05);
    }

    // Iterate through all possible positions to collect versatility scores
    for (const auto& positioni : positions) {
        int versatilityScore; // Variable to store the versatility score
        std::cout << "Enter versatility score for " << positioni << " (1-100): ";

        // Loop to validate the input for versatility score
        while (true) {
            std::cin >> versatilityScore;
            if (std::cin.fail() || versatilityScore < 1 || versatilityScore >= 100) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Invalid input. Enter a number between 1 and 100: ";
            }
            else {
                break; // Valid input
            }
        }

        // Store the valid score in the map with the position as the key
        positionVersatility[positioni] = versatilityScore;
    }

    // Declare a variable to store the player's preferred role
    int prefRole;
    std::cout << "Enter player's preferred role (1-5): ";
    std::cin >> prefRole;
    std::cin.ignore();

    // Assign the preferred role based on the input
    if (prefRole == 1) {
        prefferedRole = "Bench Warmer";
    }
    else if (prefRole == 2) {
        prefferedRole = "Substitute";
    }
    else if (prefRole == 3) {
        prefferedRole = "Rotation";
    }
    else if (prefRole == 4) {
        prefferedRole = "Starter";
    }
    else if (prefRole == 5) {
        prefferedRole = "Crucial";
    }

    // Prompt the user to enter the player's contract expiry date
    std::cout << "Enter player's Contract Expiry Date: ";
    getline(std::cin, contractExpiryDate);

    // Prompt the user to enter the player's estimated market value
    std::cout << "Enter player's Estimated Market Value: ";
    std::cin >> playerValue;
    std::cin.ignore();

    // Prompt the user to enter the player's wage
    std::cout << "Enter player's Wage: ";
    std::cin >> playerWage;
    std::cin.ignore();

    // Prompt the user to enter the number of matches played by the player
    std::cout << "Enter player's matches played number: ";
    std::cin >> matchesPlayed;
    std::cin.ignore();

    // Prompt the user to enter the number of goals scored by the player
    std::cout << "Enter player's goals scored number: ";
    std::cin >> goalsScored;
    std::cin.ignore();

    // Prompt the user to enter the number of assists by the player
    std::cout << "Enter player's assist number: ";
    std::cin >> assists;
    std::cin.ignore();

    // Prompt the user to enter the number of clean sheets by the player
    std::cout << "Enter player's clean sheets number: ";
    std::cin >> cleanSheets;
    std::cin.ignore();

    // Prompt the user to enter the number of tackles won by the player
    std::cout << "Enter player's amount of won tackles: ";
    std::cin >> tacklesWon;
    std::cin.ignore();

    // Prompt the user to enter the player's passing accuracy
    std::cout << "Enter player's passing accuracy: ";
    std::cin >> passingAccuracy;
    std::cin.ignore();

    // Prompt the user to enter the number of shots on target by the player
    std::cout << "Enter player's shots on target amount: ";
    std::cin >> shotsOnTarget;
    std::cin.ignore();

    // Validate that the number of shots on target is not less than the number of goals scored
    if (shotsOnTarget < goalsScored) {
        std::cerr << "There has been an error when counting goals and shots on target!!!";
        return;
    }

    // Prompt the user to enter the player's clutch factor
    std::cout << "Enter how Clutch the player is: ";
    std::cin >> clutchFactor;
    std::cin.ignore();

    // Calculate additional player attributes based on existing ratings
    penaltyShoot = (shooting * .35) + (composure * .65);
    setPiece = (passing * .55) + (composure * .45);
    ballControl = (dribbling * .3) + (composure * .7);

    attributes.push_back(penaltyShoot);
    attributes.push_back(setPiece);
    attributes.push_back(ballControl);

    // Prompt the user to enter the player's morale
    std::cout << "Enter player's morale: ";
    std::cin >> morale;
    std::cin.ignore();

    // Prompt the user to enter the player's consistency
    std::cout << "Enter player's consistency: ";
    std::cin >> consistency;
    std::cin.ignore();

    // Prompt the user to enter the player's unselfishness factor
    std::cout << "Enter the chance of the player to be unselfish in a situation: ";
    std::cin >> teamPlayer;
    std::cin.ignore();

    // Randomly determine the player's stamina based on physicality
    int chance = rand() % 5;
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

    // Calculate the player's injury-prone factor
    injuryProne = stamina - physicality + 100;

    // Create a JSON object to store versatility data
    json versatilityJson;
    for (const auto& [position, score] : positionVersatility) {
        versatilityJson[position] = score;
    }

    // Create a JSON object for the new player with all collected and calculated data
    json newPlayer = {
        {"id", playerID},
        {"name", playerName},
        {"rating", playerRating},
        {"position", position},
        {"number", playerNumber},
        {"is_captain", playerIsCaptain},
        {"is_ambidextrous", playerIsAmbidextrous},
        {"is_rfooted", rightFoot},
        {"pace", pace},
        {"dribbling", dribbling},
        {"passing", passing},
        {"shooting", shooting},
        {"defending", defending},
        {"physicality", physicality},
        {"workrate", workRate},
        {"nationality", playerNationality},
        {"dob", dateOfBirth},
        {"ced", contractExpiryDate},
        {"role", prefferedRole},
        {"value", playerValue},
        {"wage", playerWage},
        {"composure", composure},
        {"vision", vision},
        {"positioning", positioning},
        {"shooting", longShots},
        {"defensive_work_rate", defWorkRate},
        {"offensive_work_rate", offWorkRate},
        {"id", teamID},
        {"aggression", aggression},
        {"penalty", penaltyShoot},
        {"set_pieces", setPiece},
        {"ball_control", ballControl},
        {"stamina", stamina},
        {"injury_prone", injuryProne},
        {"appearances", matchesPlayed},
        {"goals", goalsScored},
        {"assists", assists},
        {"clean_sheets", cleanSheets},
        {"tackles", tacklesWon},
        {"shots_on_target", shotsOnTarget},
        {"passing_accuracy", passingAccuracy},
        {"special_traits_amount", specialTraitsNum},
        {"special_traits", specialTraits},
        {"potential", potentialRating},
        {"training_wr", trainingWorkRate},
        {"clutch", clutchFactor},
        {"height", playerHeight},
        {"weight", playerWeight},
        {"consistency", consistency},
        {"morale", morale},
        {"team_player", teamPlayer},
        {"versatility", versatilityJson}
    };

    exportPlayerData(newPlayer);
}

void displayPlayerData() {
    // Open the JSON file containing player data
    std::ifstream file("player_data.json");
    if (!file.is_open()) {
        // If the file cannot be opened, display an error message and exit the function
        std::cerr << "Error opening the JSON file!" << std::endl;
        return;
    }

    // Define a JSON array to hold the player data
    json playerDataArray;
    file >> playerDataArray; // Read the JSON data from the file
    file.close(); // Close the file after reading

    // Check if the JSON data is an array
    if (!playerDataArray.is_array()) {
        // If the data is not an array, display an error message and exit the function
        std::cerr << "Error: JSON data is not an array!" << std::endl;
        return;
    }

    // Iterate through each player object in the JSON array
    for (const auto& playerData : playerDataArray) {
        // Print a separator for better readability
        std::cout << "---------------------------------" << std::endl;

        // Display basic player information
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

        // Display foot preference and ambidexterity
        if (playerData["ambidextrous"] == true) {
            std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
        } else if (playerData["right_foot"] == true) {
            std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
            std::cout << "Player Is Right Footed" << std::endl;
        } else if (playerData["left_foot"] == true) {
            std::cout << "Player Is Ambidextrous? " << playerData["ambidextrous"] << std::endl;
            std::cout << "Player Is Left Footed" << std::endl;
        }

        // Display player ratings
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
        std::cout << "Player Aggression Rating: " << playerData["aggression"] << std::endl;
        std::cout << "Player Penalty Rating: " << playerData["penalty"] << std::endl;
        std::cout << "Player Set Pieces Rating: " << playerData["set_pieces"] << std::endl;
        std::cout << "Player Ball Control Rating: " << playerData["ball_control"] << std::endl;
        std::cout << "Player Stamina Rating: " << playerData["stamina"] << std::endl;

        // Display special traits
        std::cout << "Player Special Traits: ";
        for (const auto& trait : playerData["special_traits"]) {
            std::cout << trait << " ";
        }
        std::cout << std::endl;

        // Display work rates and potential
        std::cout << "Player Defensive and Offensive Work Rate: " << playerData["work_rate"] << std::endl;
        std::cout << "Player Training Work Rate: " << playerData["training"] << std::endl;
        std::cout << "Player Potential Rating: " << playerData["potential"] << std::endl;

        // Display contract and role information
        std::cout << "Contract Expiry Date: " << playerData["contract_expiry_date"] << std::endl;
        std::cout << "Player Preferred Role: " << playerData["preffered_role"] << std::endl;
        std::cout << "Player Value: " << playerData["value"] << std::endl;
        std::cout << "Player Wage: " << playerData["wage"] << std::endl;

        // Display morale and consistency
        std::cout << "Player Morale: " << playerData["morale"] << std::endl;
        std::cout << "Player Consistency: " << playerData["consistency"] << std::endl;
        std::cout << "Player Unselfishness: " << playerData["team_player"] << std::endl;

        // Display versatility data
        std::cout << "Player Versatility:" << std::endl;
        if (playerData.contains("versatility")) {
            const json& versatility = playerData["versatility"];
            for (const auto& [position, score] : versatility.items()) {
                std::cout << "  Position: " << position << ", Score: " << score << std::endl;
            }
        } else {
            std::cout << "  No versatility data available." << std::endl;
        }
    }
}
