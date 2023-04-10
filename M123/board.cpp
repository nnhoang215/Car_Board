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

Board::Board()
{   
    this->board = new std::vector<std::vector<Cell>>{};

    for (int i = 0; i < DEFAULT_BOARD_DIMENSION; i++) {
        (*board).push_back(std::vector<Cell>());
        for (int j = 0; j < DEFAULT_BOARD_DIMENSION; j++) {
            (*board)[i].push_back(EMPTY);
        }
    }
}

Board::~Board()
{   
    delete this->board;
}

void Board::load(int boardId)
{
    if (boardId == 1) {
        *(this->board) = BOARD_1;
    } else if (boardId == 2) {
        *(this->board) = BOARD_2;
    }
}

bool Board::placePlayer(Position position)
{
    bool result = false;
    int playerRowPosition = position.getY();
    int playerColPosition = position.getX();
    bool isBlocked = (*board)[position.getY()][position.getX()] == BLOCKED;
    bool isOutBound = playerRowPosition > MAX_POS || playerColPosition > MAX_POS;

    // check if the position is available
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
    bool isRowOutBound = nextRowPos < MIN_POS || nextRowPos > MAX_POS; 
    bool isColOutBound = nextColPos < MIN_POS || nextColPos > MAX_POS;
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
    int boardSize = DEFAULT_BOARD_DIMENSION;
    for(int i = -1; i < boardSize; i++) {
        std::cout << LINE_OUTPUT;
        if (i == -1) {
            for (int j = -1; j < boardSize; j++) {
                if (j == -1) {
                    std::cout << " " << LINE_OUTPUT;
                } else {
                    std::cout << j << LINE_OUTPUT;
                }
            }
        } else {
            for (int j = -1; j < boardSize; j++) {
                if (j == -1) {
                    std::cout << i << LINE_OUTPUT;
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


