#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <pthread.h>
#include <iostream>
#include <vector>

char buff[4];

std::vector<sf::TcpSocket> client(2);

void * threadFunc(void * index)
{
    size_t received;

    if (*(int *)index == 0)
    {
        client[0].send(buff + 2, 2, received);
        client[0].receive(buff, 2, received);
    }

    else if (*(int *)index == 1)
    {
        client[1].send(buff, 2, received);
        client[1].receive(buff + 2, 2, received);
    }

    return NULL;
}

int main()
{   
    sf::TcpListener listener;
    
    int counter = 0;

    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cerr << "Error when handling requests!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // std::vector<sf::TcpSocket> client (2);

    // sf::Thread th([&client](int x) {
    //     size_t received;

    //     if (x == 0)
    //     {
    //         client[0].send(buff + 2, 2, received);
    //         client[0].receive(buff, 2, received);
    //     }

    //     else if (x == 1)
    //     {
    //         client[1].send(buff, 2, received);
    //         client[1].receive(buff + 2, 2, received);
    //     }
    // });

    // sf::Thread *thread = new sf::Thread([&counter](int index) 
    // {
    //     size_t received;

    //     if (*(int *)index == 0)
    //     {
    //         client[0].send(buff + 2, 2, received);
    //         client[0].receive(buff, 2, received);
    //     }

    //     else if (*(int *)index == 1)
    //     {
    //         client[1].send(buff, 2, received);
    //         client[1].receive(buff + 2, 2, received);
    //     }
    // });

    pthread_t tid[2];

    while (counter < 2)
    {
        if (listener.accept(client[counter]) == sf::Socket::Done)
        {
            std::cerr << "Error occurred when accepting requests!" << std::endl;
            exit(EXIT_FAILURE);
        }

        pthread_create((tid + counter), NULL, threadFunc, &counter);

        // th[counter];
        counter ++;
    }

    
    for (int i = 0; i < 2; i++)
    {
        pthread_join(tid[i], NULL);
    }

    // while(1)
    // {
    //     if (client[0].send("something", 10) != sf::Socket::Done)
    //     {
    //         std::cerr << "Error occurred when sending data!" << std::endl;
    //         exit(EXIT_FAILURE);
    //     }
    // }
    
    return 0;
}