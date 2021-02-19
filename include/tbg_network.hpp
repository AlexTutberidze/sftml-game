#pragma once

#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string>

namespace tuxNetwork
{
    class TuxTcpSocket
    {
    public:
        TuxTcpSocket();
        ~TuxTcpSocket();
        void connect(const std::string &, const int);
        void send();
        void receive();

    private:
        int sfd;
    };

    class TuxListener
    {
    public:
        TuxListener();
        ~TuxListener();
        TuxTcpSocket & accept(const std::string &, const int);

    private:
        int sfd;
        int cfd;
    };



};
