#pragma once

#include <string>

namespace player
{
    struct Position
    {
        int x;
        int y;
    };

    class Player
    {
    public:
        inline void set_coordinate(Position & coordinate) { this->m_coordinate; }
        inline const Position &get_coordinate() const { return this->m_coordinate; }
        inline void set_name(const std::string & name) { this->m_name = name; }
        inline const std::string &get_name() const { return this->m_name; }

    private:
        std::string m_name;
        Position m_coordinate;
    };
}
