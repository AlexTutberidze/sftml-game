#pragma once

#include <string>

namespace player
{
    class player
    {
    public:
        void set_coordinate(int, int);
        void get_coordinate(int &, int &);
        void set_name(std::string);
        void get_name(std::string &);

    private:
        std::string name;
        int x;
        int y;
    };
}
