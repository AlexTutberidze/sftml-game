#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "player.hpp"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");
    sf::CircleShape shape(50.f);
    sf::CircleShape shape1(50.f);

    player::Position pos1{0, 0}, pos2{0, 0};

    player::Player player1, player2;

    player1.set_name("Player");
    player1.set_coordinate(pos1);

    shape.setFillColor(sf::Color(255, 153, 0));
    shape1.setFillColor(sf::Color(255, 26, 26));

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);

    if (status != sf::Socket::Done)
    {
        std::cerr << "Error occurred when connecting socket!" << std::endl;
        exit(EXIT_FAILURE);
    }

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
                    pos1 = player1.get_coordinate();
                    pos1.x -= 10;
                    player1.set_coordinate(pos1);   
                }

                else if(event.key.code == sf::Keyboard::Right)
                {
                    pos1 = player1.get_coordinate();
                    pos1.x += 10;
                    player1.set_coordinate(pos1);
                }

                else if(event.key.code == sf::Keyboard::Down)
                {
                    pos1 = player1.get_coordinate();
                    pos1.y += 10;
                    player1.set_coordinate(pos1);
                }

                else if (event.key.code == sf::Keyboard::Up)
                {
                    pos1 = player1.get_coordinate();
                    pos1.y -= 10;
                    player1.set_coordinate(pos1);
                }
            }
                
        }

        // clear the window with black color // /home/sandro/MEMES/MANUX.jpg
        window.clear(sf::Color::White);

        // draw everything here...
        // window.draw(...);

        // sf::Font font;
        
        // if (!font.loadFromFile("../design/OpenSans-BoldItalic.ttf"))
        // {
        //     std::cerr << "Error occurred when laoding font!" << std::endl;
        //     exit(EXIT_FAILURE);
        // }
        
        // std::string input;
        // std::cout << "Enter server ip address" << std::endl;
        // std::cin >> input;

        

        int data[2];

        std::size_t received;

        if (socket.receive(data, 2, received) != sf::Socket::Done)
        {
            std::cerr << "Error occurred when receiving data!" << std::endl;
            //exit(EXIT_FAILURE);
        }

        shape1.setPosition(data[0], data[1]);

        window.draw(shape1);

        // end the current frame
        window.display();

        // while (1)
        // {
        //     char data[100];

        //     std::size_t received;

        //     if (socket.receive(data, 100, received) != sf::Socket::Done)
        //     {
        //         std::cerr << "Error occurred when receiving data!" << std::endl;
        //         exit(EXIT_FAILURE);
        //     }

        //     window.clear(sf::Color::White);

        //     sf::Text text;

        //     text.setFont(font);

        //     text.setString(data);
        //     text.setCharacterSize(25);
        //     text.setFillColor(sf::Color::Red);
        //     text.setStyle(sf::Text::Bold);

            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            // {
            //     // left key is pressed: move our character
            //     // text.move(1.f, 0.f);
            //     text.setPosition(10.f, 50.f);
            //     text.move(5.f, 5.f);

            //     sf::Vector2f position = text.getPosition();
            // }
            
            int buff[2];

            pos1 = player1.get_coordinate();

            buff[0] = pos1.x;
            buff[1] = pos1.y;

            if (socket.send(buff, 2, received) != sf::Socket::Done)
            {
                std::cerr << "Error occurred when sending data!" << std::endl;
                exit(EXIT_FAILURE);
            }

            shape.setPosition(pos1.x, pos1.y);
            window.draw(shape);

        // }
        
    }

    return 0;
}