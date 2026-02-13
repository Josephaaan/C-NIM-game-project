#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*
The functions we need:
    - a menu function that display the choices and the current state
    - a menu function that display each difficulty levels
    maybe: an int function that contains the game, returns the number that represent the winner player
        parameters( bool userGoFirst;
                    int totalCoins;
                    int maximumTake;
                    bool userWin;
                    bool lastWin;   )
        REQUIRES:
        - a function that returns the optimal moves from the computer (will influence the original variable)
        - a function that prompts the user to enter the coin he wants to take (will influence the original variable)

    NEW FEATURES:
        - save game functionality
        - load/replay game functionality
        - file name validation

*/

// Structure to store each move in the game
struct Move {
    bool isUser;        // true if user made the move, false if computer
    int coinsTaken;     // number of coins taken
    int coinsRemaining; // coins remaining after this move
};

// Structure to store complete game data
struct GameData {
    int totalCoins;
    int maximumTake;
    bool userGoFirst;
    bool lastWin;
    int difficultyLevel;
    vector<Move> moves;
    bool userWon;
};


//The void function that display the menu
//Should include the characters for different choices
//the current states for different variables
void displayMenu(int totalCoins = 12, int maximumTake = 3, bool userGoFirst = true, bool lastWin = false)
{
    cout << "******************************" << endl;   // 30 *
    cout << "************ Menu ************" << endl;
    cout << "******************************" << endl;   // 30 *
    cout << "W: the one who draw the last coin wins" << endl;
    cout << "L: the one who draw the last coin lose" << endl;
    cout << "--------------------------------------" << endl;
    cout << "C: change the number of coins" << endl;
    cout << "T: change the maximum number of coins player can take" << endl;
    cout << "P: change the player who goes first" << endl;
    cout << "D: change the difficulty level of the computer" << endl;
    cout << "--------------------------------------" << endl;
    cout << "G: start the game!" << endl;
    cout << "R: replay a saved game" << endl;
    cout << "Q: quit" << endl;
    cout << "--------------------------------------" << endl;
    cout << "total coins: " << totalCoins << endl;
    cout << "maximum take: " << maximumTake << endl;
    //See if the user is going first or not
    if (userGoFirst)
        cout << "the player go first" << endl;
    else
        cout << "the computer go first" << endl;
    if (lastWin)
        cout << "the player drawing the last coin wins" << endl;
    else
        cout << "the player drawing the last coin loses" << endl;
}


//The menu that display each difficulty level
//The user could change each difficulty level through input
void difficultyMenu(int difficultyLevel)
{
    cout << "******************************" << endl;
    cout << "****** Difficulty Level ******" << endl;
    cout << "******************************" << endl;
    if (difficultyLevel == 1)
        cout << "1. Naive Version - current one" << endl;
    else
        cout << "1. Naive Version" << endl;
    if (difficultyLevel == 2)
        cout << "2. Smart Version - current one" << endl;
    else
        cout << "2. Smart Version" << endl;
    if (difficultyLevel == 3)
        cout << "3. Coach Version - current one" << endl;
    else
        cout << "3. Coach Version" << endl;

}

//Given the number of coins, maximum take, and whether the last one take the coin win or not
//This function is going to return whether an optimal move exist or not
bool checkOptimalExist(int coins, int take, bool lastWin)
{
    if ((coins % (take + 1) != 0 && lastWin)
        ||
        ((coins - 1) % (take + 1) != 0 && !lastWin)
        )
        return true;
    else
    {
        return false;
    }
}

//Minor function that calculate the optimal move for
//Return the optimal move as an integer
//WARNING: BEFORE USING THIS, MUST CHECK WHETHER OPTIMAL MOVE EXIST OR NOT!!!
int calculateOptimalMove(int coinsLeft, int maximumTake, bool lastWin)
{
    /*
    * IF TAKING THE LAST COIN MEANS WINNING
    * First, we need to test if there's any optimal move possible
    * if totalLeft % (maximumTake + 1) = 0, there's no optimal move
    * OR
    * The optimal move = take totalLeft % (maximumTake + 1)
    */


    /*
    * IF TAKING THE LAST COIN MEANS LOSING
    * First, we still need to test if there's any optimal move possible
    * if (totalLeft - 1) % (maximumTake + 1) = 0, there's no optimal move
    * OR
    * The optimal move = take (totalLeft - 1) % (maximumTake + 1)
    *
    */

    //if the last one draw the coin wins
    if (lastWin)
        return coinsLeft % (maximumTake + 1);
    //if the last one draw the coin loses
    else
        return (coinsLeft - 1) % (maximumTake + 1);
}


//We might add different difficulty levels for computer
//The current one is a naive one
//the int function that calculate the naive move for the computer
//return the coins computer took
int computerRandomMove(int coinsLeft, int maximumTake) {

    //In the naive version, the computer would drew random amount of coins
    //We need to make sure that the computer do not return coins that are larger than the total coins remain
    int randomTake = (rand() % (maximumTake)) + 1;

    //If the random generated number is larger than the total coins left, return the total coins
    if (randomTake > coinsLeft)
        return coinsLeft;
    //else, just return the random generated number
    return randomTake;
}


//The function that calculate the optimal move of the computer
//Created for the smart version
//The first two varables are crucial for the game play
//The third is used for the computer to determin the winning strategy
//The fourth coach boolean varable is used to decide whether the computer would display its decision making process
//The coach variable is initialized to false, so that coach version would not be triggered, unless specifically required
int computerOptimalMove(int coinsLeft, int maximumTake, bool lastWin, bool coach = false)
{
    //First ,we should check whether the optimal move exist or not
    //If it does, return the optimal move
    if (checkOptimalExist(coinsLeft, maximumTake, lastWin))
    {
        int computerTake = calculateOptimalMove(coinsLeft, maximumTake, lastWin);

        //Make sure that the coins returned is smaller or equal to total coins
        if (computerTake <= coinsLeft && computerTake <= maximumTake)
            return computerTake;
        //Else
        return coinsLeft;
    }
    //If no optimal move exist
    else
        return computerRandomMove(coinsLeft, maximumTake);
}



//The function for the coach move of the computer
//The user could choose to let the computer to do an optimal move
//Or to do a random move
int computerCoachMove(int coinsLeft, int maximumTake, bool lastWin)
{
    //an integer that stores the result the user want
    int userChoice;

    //A while loop that would not stop until the user input the right number
    //The loop would not be triggered, if there's no optimal move
    //If there's no optimal move, the computer would just do a random move
    while (checkOptimalExist(coinsLeft, maximumTake, lastWin)) {     //Use the function that check whether the optimal move exist


        cout << "Would you want the computer to do a optimal move or a random move?" << endl;
        cout << "1. optimal\t2. random" << endl;
        cin >> userChoice;

        //check if the result is valid
        //If not, make the user enter again
        if (userChoice != 1 && userChoice != 2)
        {
            cout << "Invalid choice! Please enter again!" << endl;
        }
        //If it is valid
        else {
            //If the user choose one, do the optimal move
            if (userChoice == 1)
                return computerOptimalMove(coinsLeft, maximumTake, lastWin, true);
            //else, do the random one
            else
                return computerRandomMove(coinsLeft, maximumTake);

        }
    }

    cout << "Since there's no optimal move, the computer would automatically do a random move." << endl;
    return computerRandomMove(coinsLeft, maximumTake);

}

//the int function that return the number of coins user decided to input
//IF the coach vesion is on, a different version of this would be triggered
int userMove(int coinsLeft, int maximumTake, bool lastWin, int difficultyLevel)
{

    // The variable that stores the amount of coins user wanna draw, initialized to 0
    int userTake = 0;


    //The userMove would continue, if it is on the coach version, until the user stop retrieving
    do
    {

        cout << "It's your turn! How many coins you wanna draw? " << endl;
        cin >> userTake;

        //Check whether the number of coins the user took is valid or not
        //If it is higher than the maximum take, it's not valid
        //If it is smaller than 1, it is not valid
        while (userTake > maximumTake || userTake < 1)
        {
            if (userTake > maximumTake)
            {
                cout << "You can not take more than " << maximumTake << " coins! Please enter again!" << endl;
            }
            else
            {
                cout << "You must at least take 1 coin! Please enter again!" << endl;
            }
            cin >> userTake;
        }


        /*      ONLY FOR COACH VERSION
        * we will first check if the optimal move exist or not
        * if it does, we will give feedbacks on whether user did an optimal move or not
        * Then the user could choose whether to retrieve his movement or not
        * If he want to retrieve, he enters again, and the while loop would be done once again
        * if he don't want to retrieve, the program would carry on
        */
        if (difficultyLevel == 3 && checkOptimalExist(coinsLeft, maximumTake, lastWin))
        {
            //If the user already input the optimal move, break
            if (userTake == calculateOptimalMove(coinsLeft, maximumTake, lastWin))
            {
                cout << "The optimal move exist, and you had made an optimal move!" << endl;

                //break outside the while loop
                break;
            }
            else
            {
                cout << "The optimal move exist, but you didn't make an optimal move, do you want to retrieve your move?" << endl;
                cout << "1. Retrieve\t2.Just carry on!" << endl;

                //We need another while loop here to make sure that the user is entering the right number
                //The variable for userOption, initialized to 0
                int userOption = 0;
                do
                {

                    cin >> userOption;

                    //If the user entered invalid choice, we will prompt ther user to enter again
                    if (userOption != 1 && userOption != 2)
                        cout << "Invalid choice! Please enter again!" << endl;

                } while (userOption != 1 && userOption != 2);

                //After we made sure that the user entered the right number, we will do different things according to his option
                //1. Retrieve the result
                //We basically do nothing
                //The program would loop by itself

                //2. Carry on
                //We break out the loop, so that the following lines of code would return the proper results
                if (userOption == 2)
                    break;


            }

        }

        //If the optimal move does not exist
        else {
            if (difficultyLevel == 3)
                cout << "Since the optimal move does not exist in the first place, we would just continue..." << endl;
            break;
        }

    } while (difficultyLevel == 3);

    //COACH VERSION PORTION FINISH
    //If the number of coins the user took exceed the number of coins that exceed in the stack
        //the user would take all the coins
    if (coinsLeft < userTake)
    {
        cout << "There's not that many coins left. We would just grab as many as they're left..." << endl;
        return coinsLeft;
    }

    //If not, just return the amount of coins that's taken
    return userTake;
}

// Function to validate file name
// Returns true if valid, false otherwise
bool isValidFileName(const string& filename) {
    // Check if filename is empty
    if (filename.empty()) {
        return false;
    }

    // Check for invalid characters (common across Windows, Linux, Mac)
    string invalidChars = "<>:\"/\\|?*";
    for (char c : filename) {
        if (invalidChars.find(c) != string::npos) {
            return false;
        }
        // Check for control characters
        if (c < 32) {
            return false;
        }
    }

    // Check if filename is too long (most systems support up to 255)
    if (filename.length() > 200) {
        return false;
    }

    return true;
}

// Function to get a valid filename from user
string getValidFileName() {
    string filename;
    bool valid = false;

    while (!valid) {
        cout << "Enter a name for your save file (without extension): ";
        cin.ignore(); // Clear any leftover newline
        getline(cin, filename);

        if (isValidFileName(filename)) {
            valid = true;
        }
        else {
            cout << "Invalid filename! Please avoid special characters like < > : \" / \\ | ? *" << endl;
            cout << "and make sure the name is not empty and less than 200 characters." << endl;
        }
    }

    return filename + ".txt"; // Add .txt extension
}

// Function to save game data to a file
bool saveGame(const GameData& gameData, const string& filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cout << "Error: Unable to create save file!" << endl;
        return false;
    }

    // Write game settings
    outFile << gameData.totalCoins << endl;
    outFile << gameData.maximumTake << endl;
    outFile << gameData.userGoFirst << endl;
    outFile << gameData.lastWin << endl;
    outFile << gameData.difficultyLevel << endl;
    outFile << gameData.userWon << endl;

    // Write number of moves
    outFile << gameData.moves.size() << endl;

    // Write each move
    for (const Move& move : gameData.moves) {
        outFile << move.isUser << " " << move.coinsTaken << " " << move.coinsRemaining << endl;
    }

    outFile.close();
    cout << "Game successfully saved to " << filename << "!" << endl;
    return true;
}

// Function to load game data from a file
bool loadGame(GameData& gameData, const string& filename) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error: Unable to open save file!" << endl;
        return false;
    }

    // Read game settings
    inFile >> gameData.totalCoins;
    inFile >> gameData.maximumTake;
    inFile >> gameData.userGoFirst;
    inFile >> gameData.lastWin;
    inFile >> gameData.difficultyLevel;
    inFile >> gameData.userWon;

    // Read number of moves
    int numMoves;
    inFile >> numMoves;

    // Clear any existing moves
    gameData.moves.clear();

    // Read each move
    for (int i = 0; i < numMoves; i++) {
        Move move;
        inFile >> move.isUser >> move.coinsTaken >> move.coinsRemaining;
        gameData.moves.push_back(move);
    }

    inFile.close();
    return true;
}

// Function to replay a saved game
void replayGame(const GameData& gameData) {
    cout << "\n******************************" << endl;
    cout << "****** Replaying Game ********" << endl;
    cout << "******************************" << endl;
    cout << "Game Settings:" << endl;
    cout << "Total coins: " << gameData.totalCoins << endl;
    cout << "Maximum take: " << gameData.maximumTake << endl;
    cout << "First player: " << (gameData.userGoFirst ? "User" : "Computer") << endl;
    cout << "Win condition: " << (gameData.lastWin ? "Last coin wins" : "Last coin loses") << endl;
    cout << "Difficulty: " << gameData.difficultyLevel << endl;
    cout << "\n--- Game Replay ---\n" << endl;

    int currentCoins = gameData.totalCoins;

    for (size_t i = 0; i < gameData.moves.size(); i++) {
        const Move& move = gameData.moves[i];

        if (move.isUser) {
            cout << "Player took " << move.coinsTaken << " coin(s)." << endl;
        }
        else {
            cout << "Computer took " << move.coinsTaken << " coin(s)." << endl;
        }

        cout << move.coinsRemaining << " coin(s) remaining." << endl;
        cout << endl;
    }

    cout << "--- Game Result ---" << endl;
    if (gameData.userWon) {
        cout << "Player won the game!" << endl;
    }
    else {
        cout << "Computer won the game!" << endl;
    }
    cout << endl;
}


//The int function that run the game
//if the function returns 0, computer won
//if the function returns 1, user won
// Modified to record moves
int gamePlay(int coinsLeft, int maximumTake, bool userGoFirst, bool lastWin, int difficultyLevel, GameData* gameData = nullptr)
{
    // If gameData is provided, initialize it
    if (gameData != nullptr) {
        gameData->totalCoins = coinsLeft;
        gameData->maximumTake = maximumTake;
        gameData->userGoFirst = userGoFirst;
        gameData->lastWin = lastWin;
        gameData->difficultyLevel = difficultyLevel;
        gameData->moves.clear();
    }

    //As long as there are coins left, each player take turns
    while (coinsLeft > 0)
    {
        if (userGoFirst) {

            //The user should move
            //And the number coins left would be displayed
            int userTake = userMove(coinsLeft, maximumTake, lastWin, difficultyLevel);
            coinsLeft -= userTake;

            // Record the move
            if (gameData != nullptr) {
                Move move;
                move.isUser = true;
                move.coinsTaken = userTake;
                move.coinsRemaining = coinsLeft;
                gameData->moves.push_back(move);
            }

            cout << coinsLeft << " left..." << endl;
            cout << "\n";

            //Check the amount of coins left
            //If the coin is 0, winner should be declared

            //If the last one draw the coin win
            //and there's no coin left
            //Then the user win(return 1)
            if (!coinsLeft && lastWin) {
                if (gameData != nullptr) gameData->userWon = true;
                return 1;
            }

            //If the last one draw the coin lose
            //and there's no coin left
            //Then the computer win(return 0)
            if (!coinsLeft && !lastWin) {
                if (gameData != nullptr) gameData->userWon = false;
                return 0;
            }

            //------------------------------------------------------
            //Depending on difficulty levels, different versions of computer would be triggered
            //The variable temporarily storing the number of coins the computer took
            int computerTake = 0;


            switch (difficultyLevel)
            {
            case 1: //difficulty 1, naive computer
            {
                computerTake = computerRandomMove(coinsLeft, maximumTake);
                break;
            }
            case 2: //difficulty 2, smart computer
            {
                computerTake = computerOptimalMove(coinsLeft, maximumTake, lastWin);
                break;
            }
            case 3: //difficulty 3, coach computer
            {
                computerTake = computerCoachMove(coinsLeft, maximumTake, lastWin);
                break;
            }
            }   //switch ends

            //Minus the coin took from the total coins
            coinsLeft -= computerTake;

            // Record the move
            if (gameData != nullptr) {
                Move move;
                move.isUser = false;
                move.coinsTaken = computerTake;
                move.coinsRemaining = coinsLeft;
                gameData->moves.push_back(move);
            }

            //Display the result after each movement
            cout << "The computer took " << computerTake << " coins..." << endl;
            cout << coinsLeft << " left..." << endl;
            cout << "\n";

            //Check the amount of coins left
            //If the coin is 0, winner should be declared

            //If the last one draw the coin win
            //and there's no coin left
            //Then the computer win(return 0)
            if (!coinsLeft && lastWin) {
                if (gameData != nullptr) gameData->userWon = false;
                return 0;
            }

            //If the last one draw the coin lose
            //and there's no coin left
            //Then the computer lose(return 1)
            if (!coinsLeft && !lastWin) {
                if (gameData != nullptr) gameData->userWon = true;
                return 1;
            }
        }
        else {
            //------------------------------------------------------
            //Depending on difficulty levels, different versions of computer would be triggered
            //The variable temporarily storing the number of coins the computer took
            int computerTake = 0;


            switch (difficultyLevel)
            {
            case 1: //difficulty 1, naive computer
            {
                computerTake = computerRandomMove(coinsLeft, maximumTake);
                break;
            }
            case 2: //difficulty 2, smart computer
            {
                computerTake = computerOptimalMove(coinsLeft, maximumTake, lastWin);
                break;
            }
            case 3: //difficulty 3, coach computer
            {
                computerTake = computerCoachMove(coinsLeft, maximumTake, lastWin);
                break;
            }
            }   //switch ends

            //Minus the coin took from the total coins
            coinsLeft -= computerTake;

            // Record the move
            if (gameData != nullptr) {
                Move move;
                move.isUser = false;
                move.coinsTaken = computerTake;
                move.coinsRemaining = coinsLeft;
                gameData->moves.push_back(move);
            }

            //Display the result after each movement
            cout << "The computer took " << computerTake << " coins..." << endl;
            cout << coinsLeft << " left..." << endl;
            cout << "\n";

            //Check the amount of coins left
            //If the coin is 0, winner should be declared

            //If the last one draw the coin win
            //and there's no coin left
            //Then the computer win(return 0)
            if (!coinsLeft && lastWin) {
                if (gameData != nullptr) gameData->userWon = false;
                return 0;
            }

            //If the last one draw the coin lose
            //and there's no coin left
            //Then the computer lose(return 1)
            if (!coinsLeft && !lastWin) {
                if (gameData != nullptr) gameData->userWon = true;
                return 1;
            }


            //-------------------------------------------------
            int userTake = userMove(coinsLeft, maximumTake, lastWin, difficultyLevel);
            coinsLeft -= userTake;

            // Record the move
            if (gameData != nullptr) {
                Move move;
                move.isUser = true;
                move.coinsTaken = userTake;
                move.coinsRemaining = coinsLeft;
                gameData->moves.push_back(move);
            }

            cout << coinsLeft << " left..." << endl;
            cout << "\n";

            //If the last one draw the coin win
            //and there's no coin left
            //Then the user win(return 1)
            if (!coinsLeft && lastWin) {
                if (gameData != nullptr) gameData->userWon = true;
                return 1;
            }

            //If the last one draw the coin lose
            //and there's no coin left
            //Then the user lose(return 0)
            if (!coinsLeft && !lastWin) {
                if (gameData != nullptr) gameData->userWon = false;
                return 0;
            }
        }
    }
    return 0; // Should never reach here
}


int main()
{
    //Initiate all the variables needed to display the menu
    int totalCoins = 12;        //the total coins at the beginning of the game
    int coinLeft;               //set the coinLeft equal to totalCoins before the game start
    int maximumTake = 3;        //The maximum number of coins a player could grab at a single turn
    bool lastWin = false;       //The one who takes the coin last lose
    bool userGoFirst = true;    //By default, the user go first
    int difficultyLevel = 3;    //By default, the difficulty level of the computer is the coach version
    //The variable that stores the user choice
    char userInput;

    //A loop that goes on an on, until the user enters Q
    do
    {
        //display the meny
        displayMenu(totalCoins, maximumTake, userGoFirst, lastWin);
        //read the user input
        cin >> userInput;

        switch (userInput)
        {
            //The last one to draw the coin wins
        case 'w': case 'W':
        {
            lastWin = true;
            break;
        }
        //The last one to draw the coin loses
        case 'l': case 'L':
        {
            lastWin = false;
            break;
        }
        //Change the total number of coins
        case 'c': case 'C':
        {
            //A loop that continues, until the user entered a valid number
            do
            {
                cout << "Please enter the amount of coins you want in the game..." << endl;
                cin >> totalCoins;

                //Check whether the user input is a valid number
                //If not, the while loop would go on and on
                if (totalCoins < 0) {
                    cout << "Invalid number! Please enter again!" << endl;
                }
                //If it is valid, continue
                else
                {
                    //break out the while
                    break;
                }

            } while (true);

            //break out the switch
            break;
        }
        //Change the maximum takes
        case 't': case 'T':
        {

            //A loop that continues, until the user entered a valid number
            do
            {
                cout << "Please enter the maximum take you want in the game" << endl;
                cin >> maximumTake;

                //Check whether the user input is a valid number
                //If not, the while loop would go on and on
                if (maximumTake < 0) {
                    cout << "Invalid number! Please enter again!" << endl;
                }
                //If it is valid, continue
                else
                {
                    //break out the while
                    break;
                }

            } while (true);

            //break out the switch
            break;
        }
        //Change the player that goes first
        case 'p': case 'P':
        {
            userGoFirst = !userGoFirst;
            break;
        }
        case 'd': case'D':
        {
            //Display the difficulty menu
            difficultyMenu(difficultyLevel);
            cout << "Enter any number to change the difficulty level" << endl;

            //The loop would continue until the user entered a valid number
            while (true) {
                cin >> difficultyLevel;
                //The difficulty level must be between 1 and 3 inclusively
                if (difficultyLevel < 1 || difficultyLevel > 3)
                    cout << "Invalid Number! Please enter again!" << endl;
                else
                    break;
            }

            break;
        }
        //Starts the game
        case 'g': case 'G':
        {
            // Create GameData object to record the game
            GameData currentGame;

            //The function for the gameplay
            bool userWin = gamePlay(totalCoins, maximumTake, userGoFirst, lastWin, difficultyLevel, &currentGame);

            //Display the result
            if (userWin)
            {
                cout << "Congratulation! You beat the computer!" << endl;
            }
            else
                cout << "You lost! No worries, let's try again!" << endl;
            cout << "\n";

            // Ask if user wants to save the game
            char saveChoice;
            cout << "Would you like to save this game? (Y/N): ";
            cin >> saveChoice;

            // check if the user entered the option
            if (saveChoice == 'Y' || saveChoice == 'y') {

                // Then ask the file name user wants
                string filename = getValidFileName();
                saveGame(currentGame, filename);        // save the game
                cout << "Game saved!" << endl;          // display the result
            }
            else            // If the user did not enter yes, game would not be saved
            {
                cout << "This game would not be saved" << endl;     // The result would be displayed
            }

            break;
        }
        //Replay a saved game
        case 'r': case 'R':
        {
            string filename;
            cout << "Enter the name of the save file to replay (with .txt extension): ";
            cin.ignore();
            getline(cin, filename);

            // Load the game using the replayGame function
            GameData loadedGame;
            if (loadGame(loadedGame, filename)) {
                replayGame(loadedGame);
            }

            // the user would not proceed to the menu before pressing any character
            cout << "Enter any character to continue" << endl;
            char temp;
            cin >> temp;

            break;
        }
        //quits the game
        case 'q': case 'Q':
        {
            cout << "Thanks for playing! Goodbye!" << endl;
            return 0;
        }
        default:
            cout << "Invalid output! Please enter again" << endl;
            break;
        }

    } while (true);
    return 0;
}
