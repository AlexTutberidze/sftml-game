#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main()
{   
    sf::TcpListener listener;

    if (listener.listen(50003) != sf::Socket::Done)
    {
        std::cerr << "Error when handling requests!" << std::endl;
        exit(EXIT_FAILURE);
    }

    sf::TcpSocket client;

    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Error occurred when accepting requests!" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        std::string input;

        std::cin >> input;

        if (client.send(input.c_str(), input.size()) != sf::Socket::Done)
        {
            std::cerr << "Error occurred when sending data!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}