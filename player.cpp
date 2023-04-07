#include "player.h"

Position::Position()
{
    //TODO
}


Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Position::getX(){
    return this->x;
}

int Position::getY(){
    return this->y;
}

Player::Player()
{
    Position* tempPosition = new Position(-1,-1);
    this->position = *tempPosition;
    this->direction = NORTH;
    delete tempPosition;
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    // transfer ownership
    delete &(this->position);
    this->position = *position;
    this->direction = direction;
    this->moves = 0;
}

void Player::turnDirection(TurnDirection turnDirection)
{
    // converts enum to int for easier operations
    int dirNum = this->direction;
    if (turnDirection == TURN_LEFT) {
        dirNum-=1;
    } 

    if (turnDirection == TURN_RIGHT) {
        dirNum+=1;
    } 

    //wrap around
    dirNum = (dirNum == -1) ? 3 : dirNum;
    dirNum = (dirNum == 4) ? 0 : dirNum;

    //converts int to Direction Enum and update direction
    this->direction = static_cast<Direction>(dirNum);
}

Position Player::getNextForwardPosition()
{
    int x = this->position.getX();
    int y = this->position.getY();

    if (this->direction == NORTH) {
        y--;
    } else if (this->direction == EAST) {
        x++;
    } else if (this->direction == SOUTH) {
        y++;
    } else if (this->direction == WEST) {
        x--;
    }

    Position newPosition(x,y);

    return newPosition;
}

void Player::updatePosition(Position position)
{
    // transfer of ownership 
    // delete &(this->position);
    this->position = position;
    this->moves++;
}

void Player::displayDirection()
{
     if (this->direction == NORTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_NORTH; 
    } else if (this->direction == EAST) {
        std::cout <<  DIRECTION_ARROW_OUTPUT_EAST;
    } else if (this->direction == SOUTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH;
    } else if (this->direction == WEST) {
        std::cout << DIRECTION_ARROW_OUTPUT_WEST;
    }
}
