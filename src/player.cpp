#include "player.hpp"

void player::player::set_coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

void player::player::get_coordinate(int & x, int & y)
{
    x = this->x;
    y = this->y;
}

void player::player::get_name(std::string & name)
{
    name = this->name;
}

void player::player::set_name(std::string name)
{
    this->name = name;
}