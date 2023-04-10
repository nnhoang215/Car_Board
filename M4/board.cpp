#include "board.h"

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

Board::Board() {}

Board::Board(int boardSize)
{   
    this->board = new std::vector<std::vector<Cell>>{};

    for (int i = 0; i < boardSize; i++) {
        (*board).push_back(std::vector<Cell>());
        for (int j = 0; j < boardSize; j++) {
            (*board)[i].push_back(EMPTY);
        }
    }
    this->boardSize = boardSize;
}

Board::~Board()
{   
    delete this->board;
}

void Board::load(int boardId)
{
    if (boardId == 1) {
        *(this->board) = BOARD_1;
    } else {
        *(this->board) = BOARD_2;
    }
}

void Board::loadRandomObstacles(double probability) {

    for (int i = 0; i < this->boardSize; i++) {
        for (int j = 0; j < this->boardSize; j++) {
            if (Helper::probTrue(probability)) {
                (*(this->board))[i][j] = BLOCKED;
            }
        }
    }
}

bool Board::placePlayer(Position position)
{
    bool result = false;
    int playerRowPosition = position.getY();
    int playerColPosition = position.getX();
    
    // check if the position is available
    bool isBlocked = (*board)[position.getY()][position.getX()] == BLOCKED;
    bool isOutBound = playerRowPosition >= boardSize || playerColPosition >= boardSize;

    if (!isBlocked && !isOutBound) {
        (*board)[position.getY()][position.getX()] = PLAYER;
        result = true;
    }

    return result;
}

PlayerMove Board::movePlayerForward(Player* player)
{
    Position nextPosition = player->getNextForwardPosition();
    PlayerMove playerMove = CELL_BLOCKED;
    int nextRowPos = nextPosition.getY();
    int nextColPos = nextPosition.getX();
    bool isRowOutBound = nextRowPos < MIN_POS || nextRowPos >= boardSize;
    bool isColOutBound = nextColPos < MIN_POS ||  nextColPos >= boardSize;
    bool isOutBound = isRowOutBound || isColOutBound;

    if (isOutBound) {
        playerMove = OUTSIDE_BOUNDS;
    } else {
        bool isBlocked = (*board)[nextRowPos][nextColPos] == BLOCKED;
        if (isBlocked) {
            playerMove = CELL_BLOCKED;
        } else {
            int playerRowPosition = (player->position).getY();
            int playerColPosition = (player->position).getX();
            (*board)[playerRowPosition][playerColPosition] = EMPTY;

            player->updatePosition(nextPosition);
            (*board)[nextRowPos][nextColPos] = PLAYER;
            playerMove = PLAYER_MOVED;
        }
    } 

    return playerMove;    
}

void Board::display(Player* player)
{
    for(int i = -1; i < this->boardSize; i++) {
        std::cout << LINE_OUTPUT;
        if (i == -1) {
            for (int j = -1; j < this->boardSize; j++) {
                if (j == -1) {
                    std::cout << " " << LINE_OUTPUT;
                } else {
                    if (j > 9) {
                        std::cout << j-10 << LINE_OUTPUT;
                    } else {
                        std::cout << j << LINE_OUTPUT;
                    }
                }
            }
        } else {
            for (int j = -1; j < this->boardSize; j++) {
                if (j == -1) {
                    if (i > 9) {
                        std::cout << i-10 << LINE_OUTPUT;
                    } else {
                        std::cout << i << LINE_OUTPUT;
                    }
                } else {
                    if ((*board)[i][j] == BLOCKED) {
                        std::cout << BLOCKED_OUTPUT;
                    } else if ((*board)[i][j] == PLAYER) {
                        player->displayDirection();
                    } else {
                        std::cout << EMPTY_OUTPUT;
                    }
                    std::cout << LINE_OUTPUT;
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "" << std::endl;        
}

int Board::getSize() {
    return this->boardSize;
}