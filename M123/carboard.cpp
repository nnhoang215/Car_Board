/*
    I first attempted to create a functional version of the game to have a general view of the 
    program, see if there are concepts or syntax that I'm not familiar with, my code looked monolithic.
    But then, later in the project, I had to think about programming in object-oriented design, 
    separating classes, functions into smaller modules according to the code template.
    Many functions like the promptMenu(), loadBoard(), or initialisePlayer() run in while loop that 
    only ends when the user has successfully entered the right, valid command or when they want to 
    quit the program, and then I continued building the program according to the sample program. 
    Instead of hard-coding board vectors, I have created for loops to create and 
    display them from the beginning, making it easier to complete M4. I first envisioned the programs 
    recursively, which I let the functions call themselves to create a loop. This led to multiple 
    memory errors and difficulty debugging. After learning about the course convention, I did a 
    full code review and changed functions to single input - single output. I like the template 
    code, it helped me so much and it somewhat shows me the standard way to organize classes, 
    properties, and methods. I would allow more modification of the classes so that I can further
    breakdown the code I write. I know that much of my code is reusable, but I found myself having
    to copy and paste instead of modularizing them.
*/

#include "game.h"
#include "helper.h"
#include "board.h"
#include "player.h"

#define PLAY 1
#define SHOW_INFO 2
#define QUIT 3

void showStudentInformation(std::string name, std::string id, std::string email);
inline void waitEnter();
void promptMenu(bool& shouldExitProgram);
void showPlayInstruction();

int main()
{
    // determines if the program continue running
    bool shouldExitProgram = false;

    while (!shouldExitProgram && !std::cin.eof()) {
        promptMenu(shouldExitProgram);
    }

    std::cout << "Good bye!\n\n";

    return EXIT_SUCCESS;
}

void promptMenu(bool& shouldExitProgram) {
    int choice = 0;
    std::cout << "\n"
        << "Welcome to Car Board\n"
        << "--------------------\n"
        << "1. Play game\n"
        << "2. Show student's information\n"
        << "3. Quit\n\n"
        << "Please enter your choice: ";
    std::string input = Helper::readInput();
    std::cout << "" << std::endl;

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

void showStudentInformation(std::string name, std::string id, std::string email){
    std::cout << "-----------------------------------\n"
        << "Name: "<< name << "\n"
        << "Student ID: " << id << "\n"
        << "Email: " << email << "\n"
        << "-----------------------------------\n";
}

void showPlayInstruction() {
    std::cout << "You can use the following commands to play the game:\n\n"
    << "load <g>\n"
    << "    g: the id of the game board to load\n"
    << "init <x>,<y>,<direction>\n"
    << "    x: horizontal position of the car on the board (between 0 & 9)\n"
    << "    y: vertical position of the car on the board (between 0 & 9)\n"
    << "    direction: direction of the car's movement (north, east, south, west)\n"
    << "forward (or f)\n"
    << "turn_left (or l)\n"
    << "turn_right (or r)\n"
    << "quit\n\n" << std::endl;
    waitEnter();
}

inline void waitEnter() {
    std::cout << "Please enter to continue..." << std::endl;
    while (std::cin.get()!='\n'); 
}