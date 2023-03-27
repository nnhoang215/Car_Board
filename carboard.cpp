#include "game.h"
#include "helper.h"
#include "board.h"
#include "player.h"


using std::string;
using std::cout;
using std::cin;
using std::endl;

// can we use using namespace std; ? 

#define PLAY 1
#define SHOW_INFO 2
#define QUIT 3

void showStudentInformation(string name, string id, string email);
inline void waitEnter();

void promptMenu(bool* shouldExitProgram);
void showPlayInstruction();
void showInstructionStageOne(bool* shouldExitGame, Board* board, Player* currentPlayer);
void showInstructionStageTwo(bool* shouldExitGame, Board* board, Player* currentPlayer);
void showInstructionStageThree(bool* shouldExitGame, Board* board, Player* currentPlayer);

int main()
{
    // determines if the program continue running 
    bool shouldExitProgram = false;

    while (!shouldExitProgram) {
        promptMenu(&shouldExitProgram);
    }

    std::cout << "Good bye!\n\n";

    return EXIT_SUCCESS;
}

void promptMenu(bool* shouldExitProgram) {
    int choice = 3;
    cout << "\n"
        << "Welcome to Car Board\n"
        << "--------------------\n"
        << "1. Play game\n"
        << "2. Show student's information\n"
        << "3. Quit\n\n"
        << "Please enter your choice: ";
    string input;
    input = Helper::readInput();
    cout << "" << endl;

    // validate float input, instead of using numbers, use string comparison 
    if (input == "1" || input == "2" || input == "3") {
        choice = std::stoi(input);
    } else {
        Helper::printInvalidInput();
        promptMenu(shouldExitProgram);
    }
    
    if (choice == PLAY) {
        showPlayInstruction();
        Board* startBoard = new Board();
        Player* currentPlayer = new Player();
        startBoard->display(currentPlayer);

        // determines if stage one should continue running 
        bool shouldExitGame = false;
        while (!shouldExitGame) {
            showInstructionStageOne(&shouldExitGame, startBoard, currentPlayer);
        }
        // showInstructionStageTwo();
        // showInstructionStageThree();
        // delete startBoard;
    } else if (choice == SHOW_INFO) {
        showStudentInformation("Hoang Nguyen", "s3926555", "s3926555@rmit.edu.vn");
    } else if (choice == QUIT) {
        *shouldExitProgram = true;
    } else {
        Helper::printInvalidInput();
        promptMenu(shouldExitProgram);
    }
}

void showStudentInformation(string name, string id, string email){
    cout << "-----------------------------------\n"
        << "Name: "<< name << "\n"
        << "Student ID: " << id << "\n"
        << "Email: " << email << "\n"
        << "-----------------------------------\n";
}

void showPlayInstruction() {
    cout << "You can use the following commands to play the game:\n\n"
    << "load <g>\n"
    << "    g: the id of the game board to load\n"
    << "init <x>,<y>,<direction>\n"
    << "    x: horizontal position of the car on the board (between 0 & 9)\n"
    << "    y: vertical position of the car on the board (between 0 & 9)\n"
    << "    direction: direction of the car's movement (north, east, south, west)\n"
    << "forward (or f)\n"
    << "turn_left (or l)\n"
    << "turn_right (or r)\n"
    << "quit\n\n" << endl;
    waitEnter();
}

inline void waitEnter() {
    cout << "Please enter to continue..." << endl;
    while (cin.get()!='\n'); 
}

void showInstructionStageOne(bool* shouldExitGame, Board* board, Player* currentPlayer) {
    cout << "At this stage of the program, only two commands are acceptable:\n"
        << "load <g>\n"
        << "quit\n\n" << endl;
        
    string input = Helper::readInput();
    

    if (input.length() < 1) {
        Helper::printInvalidInput();
        showInstructionStageOne(shouldExitGame, board, currentPlayer);
    }

    if (input == "quit") {
        *shouldExitGame = true;
    } else {
        std::vector<string>* splitInput = new std::vector<string>();
        Helper::splitString(input, *splitInput, " "); 

        if ((*splitInput)[0] == "load") {
            //board number
            if (Helper::isNumber((*splitInput)[1])) {
                int numBoard = std::stoi((*splitInput)[1]);
                if (numBoard == 1 || numBoard == 2) {
                    board->load(numBoard);
                } else {
                    Helper::printInvalidInput();
                    showInstructionStageOne(shouldExitGame, board, currentPlayer);
                }
            }
            showInstructionStageTwo(shouldExitGame, board, currentPlayer);
        } else {
            Helper::printInvalidInput();
            showInstructionStageOne(shouldExitGame, board, currentPlayer);
        }
    }
};

void showInstructionStageTwo(bool* shouldExitGame, Board* board, Player* currentPlayer) {
    board->display(currentPlayer);
    cout << "At this stage of the program, only three commands are acceptable:\n"
        << "load <g>\n"
        << "init <x>,<y>,<direction>\n"
        << "quit\n\n" << endl;

    string input = Helper::readInput();

    // check for empty string
    if (input.length() < 1) {
        Helper::printInvalidInput();
        showInstructionStageOne(shouldExitGame, board, currentPlayer);
    }
    
    std::vector<string>* splitInput = new std::vector<string>();
    Helper::splitString(input, *splitInput, " "); 
    string command = (*splitInput)[0];

    if (command == "quit") {
        *shouldExitGame = true;
    } else if (command == "init") {
        std::vector<string>* detail = new std::vector<string>();
        int x = -1;
        int y = -1;

        Helper::splitString((*splitInput)[1], *detail, ",");
        if (Helper::isNumber((*detail)[0]) && Helper::isNumber((*detail)[1])) {
            x = std::stoi((*detail)[0]);
            y = std::stoi((*detail)[1]);

            // check value in range
            if (x > 9 || y > 9) {
                Helper::printInvalidInput();
                showInstructionStageTwo(shouldExitGame, board, currentPlayer);    
            }
        } else {
            Helper::printInvalidInput();
            showInstructionStageTwo(shouldExitGame, board, currentPlayer);
        }
        
        Position* initPosition = new Position(x,y);
        Direction direction = NORTH;

        if ((*detail)[2] == "north") {
            direction = NORTH;
        } else if ((*detail)[2] == "east") {
            direction = EAST;
        } else if ((*detail)[2] == "south") {
            direction = SOUTH;
        } else if ((*detail)[2] == "west") {
            direction = WEST;
        } else {
            Helper::printInvalidInput();
            showInstructionStageTwo(shouldExitGame, board, currentPlayer);
        }

        
        bool isPlaceable = board->placePlayer(*initPosition);
        if (isPlaceable) {
            currentPlayer->initialisePlayer(initPosition, direction);
            showInstructionStageThree(shouldExitGame, board, currentPlayer);
        } else {
            cout << "Unable to place player at that position\n" << endl;
            showInstructionStageTwo(shouldExitGame, board, currentPlayer);
        }

    } else if (command == "load") {
        //board number
        if (Helper::isNumber((*splitInput)[1])) {
            int numBoard = std::stoi((*splitInput)[1]);
            if (numBoard == 1 || numBoard == 2) {
                board->load(numBoard);
            } else {
                Helper::printInvalidInput();
                showInstructionStageTwo(shouldExitGame, board, currentPlayer);
            }
        }
        showInstructionStageTwo(shouldExitGame, board, currentPlayer);
    } else {
        Helper::printInvalidInput();
        showInstructionStageTwo(shouldExitGame, board, currentPlayer);
    }
};

void showInstructionStageThree(bool* shouldExitGame, Board* board, Player* currentPlayer) {
    board->display(currentPlayer);

    cout << "At this stage of the program, only four commands are acceptable:\n"
        << "forward (or f)\n"
        << "turn_left (or l)\n"
        << "turn_right (or r)\n"
        << "quit\n\n" << endl;

    string input = Helper::readInput();

    // check for empty string
    if (input.length() < 1) {
        Helper::printInvalidInput();
        showInstructionStageOne(shouldExitGame, board, currentPlayer);
    }
    
    if (input == "forward" || input == "f") {
        cout << "go forward\n" << endl;
        showInstructionStageThree(shouldExitGame, board, currentPlayer);
    } else if (input == "turn_left" || input == "l") {
        cout << "turn_left\n" << endl;
        showInstructionStageThree(shouldExitGame, board, currentPlayer);
    } else if (input == "turn_right" || input == "r") {
        cout << "turn_right\n" << endl;
        showInstructionStageThree(shouldExitGame, board, currentPlayer);
    } else if (input == "quit") {
        *shouldExitGame = true;
    } else {
        Helper::printInvalidInput();
        showInstructionStageThree(shouldExitGame, board, currentPlayer);
    }
};