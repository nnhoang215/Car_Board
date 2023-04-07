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
    this->board = new std::vector<std::vector<Cell>>
    {
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
    };
    // TODO
}

Board::~Board()
{
    delete this->board;
}

void Board::load(int boardId)
{
    // TODO
    if (boardId == 1) {
        *(this->board) = BOARD_1;
    } else if (boardId == 2) {
        *(this->board) = BOARD_2;
    } else {
        std::cout << "need input validation" << std::endl;
    }
}

bool Board::placePlayer(Position position)
{
    bool result = false;
    int playerRowPosition = position.getY();
    int playerColPosition = position.getX();
    
    // check if the position is available
    bool isBlocked = (*board)[position.getY()][position.getX()] == BLOCKED;
    bool isOutBound = playerRowPosition > 9 || playerColPosition > 9; // replace with board size

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
    
    bool isOutBound = nextRowPos < 0 || nextColPos < 0 || nextRowPos > 9 || nextColPos > 9; // replace with size of board
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
    // const int row = 11;
    // const int col = 24;
    
    *board = *(this->board);
    
    int boardWidth = 10;
    int boardHeight = 10;
    // this function prints the matrix 
    for(int i = -1; i < boardHeight; i++) {
        std::cout << LINE_OUTPUT;
        if (i == -1) {
            for (int j = -1; j < boardWidth; j++) {
                if (j == -1) {
                    std::cout << " " << LINE_OUTPUT;
                } else {
                    std::cout << j << LINE_OUTPUT;
                }
            }
        } else {
            for (int j = -1; j < boardWidth; j++) {
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


