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
    // check if the position is available
    if ((*board)[position.getY()][position.getX()] == BLOCKED) {
        //TODO 
        return false;
    } else {
        //TODO
        return true;
    }
}

PlayerMove Board::movePlayerForward(Player* player)
{
    // TODO
    return PLAYER_MOVED;
}

void Board::display(Player* player)
{
    const int row = 11;
    const int col = 24;
    *board = *(this->board);

    int playerRowPosition = (player->position).getY();
    int playerColPosition = (player->position).getX();

    // check if the position is just a filler or not 
    // if (playerRowPosition != -1 && playerColPosition != -1) {
    //     (*board)[playerRowPosition][playerColPosition] = PLAYER;
    // }

    // if ()
    // Direction playerPosition = player->direction;
    
    // TODO: for loop this
    char tempBoard[row][col] = {
        "| |0|1|2|3|4|5|6|7|8|9|",
        "|0| | | | | | | | | | |",
        "|1| | | | | | | | | | |",
        "|2| | | | | | | | | | |",
        "|3| | | | | | | | | | |",
        "|4| | | | | | | | | | |",
        "|5| | | | | | | | | | |",
        "|6| | | | | | | | | | |",
        "|7| | | | | | | | | | |",
        "|8| | | | | | | | | | |",
        "|9| | | | | | | | | | |"
    };


    // add landscape
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
        {
            int corRow = i + 1;
            int corCol = 3 + (2 * j);
            if ((*board)[i][j] == BLOCKED) {
                tempBoard[corRow][corCol] = *BLOCKED_OUTPUT;
            } else if ((*board)[i][j] == EMPTY)  {
              // TODO
            } 
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int corRow = playerRowPosition + 1;
            int corCol = 3 + (2 * playerColPosition);

            if (i == corRow && j == corCol && playerRowPosition > 0 && playerColPosition > 0){
                player->displayDirection();
            } else {
                std::cout << tempBoard[i][j];
            }
        }
        std::cout << "" << std::endl;        
    }

    std::cout << "" << std::endl;        
 }


