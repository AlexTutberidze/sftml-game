#pragma once

#include <string>


namespace tuxNetwork
{
    class TuxSocket
    {
    public:
        TuxSocket(const std::string & ip, const std::string & setting);
        void send_request();
        void handle_request();
        void send();
        void receive();
    };



};