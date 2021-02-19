#include <tbg_network.hpp>

tuxNetwork::TuxTcpSocket::TuxTcpSocket()
{
    this->sfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sfd == -1)
    {
        std::cerr << "Error caught when creating a socket!" << std::endl;
    }
}

tuxNetwork::TuxTcpSocket::~TuxTcpSocket()
{
    if (close(this->sfd))
    {
        std::cerr << "Error caught when closing the socket!" << std::endl;
    }
}

void tuxNetwork::TuxTcpSocket::connect(const std::string & ip, const int portNum)
{
    struct sockaddr_in * addr = new sockaddr_in;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(portNum);

    inet_aton(ip.c_str(), &addr->sin_addr);

    int status = ::connect(this->sfd, (struct sockaddr *)addr, sizeof(addr));

}