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
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    // transfer ownership
    delete &(this->position);
    this->position = *position;
    this->direction = direction;
}

void Player::turnDirection(TurnDirection turnDirection)
{
    //TODO
}

Position Player::getNextForwardPosition()
{
    //TODO

    return this->position;
}

void Player::updatePosition(Position position)
{
    //TODO
}

void Player::displayDirection()
{
    // change this
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
