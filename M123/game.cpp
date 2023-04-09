#include "game.h"
#include "helper.h"
#include "board.h"
#include "player.h"

Game::Game()
{
    this->board = new Board();
    this->player = new Player();
}

Game::~Game()
{
    delete player;
    delete board;
}


void Game::start()
{   
    bool isLoaded = loadBoard();
    if (isLoaded) {
        bool isInitialized = initializePlayer();
        if (isInitialized) {
            play();
        }
    }
}

bool Game::loadBoard()
{   
    bool isSuccessful = false;
    bool shouldRepeat = true;
    
    while (shouldRepeat) {
        (this->board)->display(this->player);

        std::cout << "At this stage of the program, only two commands are acceptable:\n"
            << "load <g>\n"
            << "quit\n\n" << std::endl;

        std::string input = Helper::readInput();
        // verify input
        if (input.length() < 1) {
            Helper::printInvalidInput();
            shouldRepeat = true;
        } else {
            if (input == "quit") {
                shouldRepeat = false;
                isSuccessful = false;
            } else {
                std::vector<std::string>* splitInput = new std::vector<std::string>();
                Helper::splitString(input, *splitInput, " "); 

                if ((*splitInput)[0] == "load") {
                    //board number
                    if (Helper::isNumber((*splitInput)[1])) {
                        int numBoard = std::stoi((*splitInput)[1]);
                        if (numBoard == 1 || numBoard == 2) {
                            board->load(numBoard);
                            shouldRepeat = false;
                            isSuccessful = true;
                        } else {
                            Helper::printInvalidInput();
                            shouldRepeat = true;
                        }
                    }
                } else {
                    Helper::printInvalidInput();
                    shouldRepeat = true;
                }
                delete splitInput;
            }
        }
    }

    return isSuccessful; // feel free to revise this line, depending on your implementation.
}

bool Game::initializePlayer()
{
    bool isSuccessful = false;
    bool shouldRepeat = true;

    while (shouldRepeat) {
        board->display(player);
        std::cout << "At this stage of the program, only three commands are acceptable:\n"
            << "load <g>\n"
            << "init <x>,<y>,<direction>\n"
            << "quit\n\n" << std::endl;

        std::string input = Helper::readInput();
         // check for empty string
        if (input.length() < 1) {
            Helper::printInvalidInput();
            shouldRepeat = true;
        } else {
            std::vector<std::string>* splitInput = new std::vector<std::string>();
            Helper::splitString(input, *splitInput, " "); 
            std::string command = (*splitInput)[0];

            if (command == "quit") {
                shouldRepeat = false;
                isSuccessful = false;
            } else if (command == "init") {
                std::vector<std::string>* detail = new std::vector<std::string>();
                int x = -1;
                int y = -1;

                Helper::splitString((*splitInput)[1], *detail, ",");
                if (Helper::isNumber((*detail)[0]) && Helper::isNumber((*detail)[1])) {
                    x = std::stoi((*detail)[0]);
                    y = std::stoi((*detail)[1]);

                    // check value in range
                    if (x > 9 || y > 9) { // be careful
                        Helper::printInvalidInput();
                        shouldRepeat = true;
                    } else {
                        Position* initPosition = new Position(x,y);
                        Direction direction = NORTH;
                        
                        bool isValidDir = true;
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
                            isValidDir = false;
                            shouldRepeat = true;
                        }

                        if (isValidDir) {
                            bool isPlaced = board->placePlayer(*initPosition);
                            if (isPlaced) {
                                this->player->initialisePlayer(initPosition, direction);
                                shouldRepeat = false;
                                isSuccessful = true;
                            } else {
                                std::cout << "Unable to place player at that position\n" << std::endl;
                                shouldRepeat = true;
                            }
                        }
                    }
                } else {
                    Helper::printInvalidInput();
                    shouldRepeat = true;
                }
                delete detail;
            } else if (command == "load") {
                //board number
                if (Helper::isNumber((*splitInput)[1])) {
                    int numBoard = std::stoi((*splitInput)[1]);
                    if (numBoard == 1 || numBoard == 2) {
                        board->load(numBoard);
                        shouldRepeat = true;
                    } else {
                        Helper::printInvalidInput();
                        shouldRepeat = true;
                    }
                }
            } else {
                Helper::printInvalidInput();
                shouldRepeat = true;
            }
            delete splitInput;
        }
    }

    return isSuccessful; // feel free to revise this line.
}

void Game::play()
{
    bool shouldRepeat = true;
    
    while (shouldRepeat) {
        board->display(this->player);
        std::cout << "At this stage of the program, only four commands are acceptable:\n"
            << "forward (or f)\n"
            << "turn_left (or l)\n"
            << "turn_right (or r)\n"
            << "quit\n\n" << std::endl;

        std::string input = Helper::readInput();

        if (input.length() < 1) {
            Helper::printInvalidInput();
            shouldRepeat = true;
        } else {
            if (input == "quit") {
                std::cout << "Total player moves: " << this->player->moves <<  "\n" << std::endl;
                shouldRepeat = false;
            } else {
                if (input == "forward" || input == "f") {
                    std::cout << "go forward\n" << std::endl;
                    PlayerMove playerMove = board->movePlayerForward(this->player);        
                    
                    if (playerMove == PLAYER_MOVED) {
                        std::cout << "Player moved.\n" << std::endl;
                        shouldRepeat = true;
                    } else if (playerMove == CELL_BLOCKED){
                        std::cout << "Unable to move - cell is blocked\n" << std::endl;
                        shouldRepeat = true; 
                    } else {
                        std::cout << "Unable to move - outside bounds\n" << std::endl;
                        shouldRepeat = true;
                    }
                } else if (input == "turn_left" || input == "l") {
                    this->player->turnDirection(TURN_LEFT);
                    shouldRepeat = true;
                } else if (input == "turn_right" || input == "r") {
                    this->player->turnDirection(TURN_RIGHT);
                    shouldRepeat = true;
                } else {
                    Helper::printInvalidInput();
                    shouldRepeat = true;
                }
            }
        }
    }
}