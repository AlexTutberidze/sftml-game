#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>


int data[2];

sf::Mutex s_mtx, c_mtx;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");
    sf::CircleShape shape(50.f);
    sf::CircleShape shape1(50.f);

    // sf::Texture shape;

    // if (!shape.loadFromFile("tux.png", sf::IntRect(10, 10, 32, 32)))
    // {
    //     // error...
    // }

    player::Position pos{0, 0};

    player::Player player;

    player.set_name("Player");
    player.set_coordinate(pos);

    shape.setFillColor(sf::Color(255, 0, 0));
    shape1.setFillColor(sf::Color(255, 26, 26));

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);

    if (status != sf::Socket::Done)
    {
        std::cerr << "Error occurred when connecting socket!" << std::endl;
        exit(EXIT_FAILURE);
    }

    sf::Thread thread([&socket, &pos]() 
    {
        std::size_t received;

        s_mtx.lock();

        if (socket.receive(data, 2, received) != sf::Socket::Done)
        {
            std::cerr << "Error occurred when receiving data!" << std::endl;
            exit(EXIT_FAILURE);
        }
        s_mtx.unlock();

        c_mtx.lock();

        int buff[2];

        buff[0] = pos.x;
        buff[1] = pos.y;

        if (socket.send(buff, 2, received) != sf::Socket::Done)
        {
            std::cerr << "Error occurred when sending data!" << std::endl;
            exit(EXIT_FAILURE);
        }

        c_mtx.unlock();        
    });

    thread.launch();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    pos = player.get_coordinate();
                    pos.x -= 10;
                    player.set_coordinate(pos);   
                }

                else if(event.key.code == sf::Keyboard::Right)
                {
                    pos = player.get_coordinate();
                    pos.x += 10;
                    player.set_coordinate(pos);
                }

                else if(event.key.code == sf::Keyboard::Down)
                {
                    pos = player.get_coordinate();
                    pos.y += 10;
                    player.set_coordinate(pos);
                }

                else if (event.key.code == sf::Keyboard::Up)
                {
                    pos = player.get_coordinate();
                    pos.y -= 10;
                    player.set_coordinate(pos);
                }
            }
                
        }

        // clear the window with black color // /home/sandro/MEMES/MANUX.jpg
        window.clear(sf::Color::White);


        shape1.setPosition(data[0], data[1]);
        window.draw(shape1);

        shape.setPosition(pos.x, pos.y);
        window.draw(shape);

        window.display();
        // }
        
    }

    return 0;
}