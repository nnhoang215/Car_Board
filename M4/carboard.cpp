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

void promptMenu(bool& shouldExitProgram);
void showPlayInstruction();

int main()
{
    // determines if the program continue running
    bool shouldExitProgram = false;

    while (!shouldExitProgram) {
        promptMenu(shouldExitProgram);
    }

    std::cout << "Good bye!\n\n";

    return EXIT_SUCCESS;
}

void promptMenu(bool& shouldExitProgram) {
    int choice = 0;
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
        if (choice == PLAY) {
            showPlayInstruction();
            Game* game = new Game();
            (*game).start();
            delete game;
            shouldExitProgram = false;
        } else if (choice == SHOW_INFO) {
            showStudentInformation("Hoang Nguyen", "s3926555", "s3926555@rmit.edu.vn");
        } else if (choice == QUIT) {
            shouldExitProgram = true;
        } else {
            Helper::printInvalidInput();
            shouldExitProgram = false;
        }
    } else {
        Helper::printInvalidInput();
        shouldExitProgram = false;
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
    << "generate <d><p>\n"
    << "    d: the dimension of the game board to be generated\n"
    << "    p: the probability of the blocks on board to be generated randomly\n"
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