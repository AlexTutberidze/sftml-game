#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "player.hpp"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::CircleShape shape(50.f);
    sf::CircleShape shape1(50.f);
    player::player player;

    player.set_name("player");
    player.set_coordinate(0, 0);

    shape.setFillColor(sf::Color(100, 250, 50));

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
                    int x,y;
                    player.get_coordinate(x, y);
                    player.set_coordinate(x - 10, y);   
                }

                else if(event.key.code == sf::Keyboard::Right)
                {
                    int x, y;
                    player.get_coordinate(x, y);
                    player.set_coordinate(x + 10, y);
                }

                else if(event.key.code == sf::Keyboard::Down)
                {
                    int x, y;
                    player.get_coordinate(x, y);
                    player.set_coordinate(x, y + 10);
                }

                else if (event.key.code == sf::Keyboard::Up)
                {
                    int x, y;
                    player.get_coordinate(x, y);
                    player.set_coordinate(x, y - 10);
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

        sf::TcpSocket socket;
        sf::Socket::Status status = socket.connect("127.0.0.1", 53000);

        if (status != sf::Socket::Done)
        {
            std::cerr << "Error occurred when connecting socket!" << std::endl;
            exit(EXIT_FAILURE);
        }

        int data[2];

        std::size_t received;

        if (socket.receive(data, 2, received) != sf::Socket::Done)
        {
            std::cerr << "Error occurred when receiving data!" << std::endl;
            exit(EXIT_FAILURE);
        }

        player::player player2;

        player2.set_name("player2");
        player2.set_coordinate(data[0], data[1]);

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
            int x, y;
            int x1, y1;

            player.get_coordinate(x, y);

            shape.setPosition(x, y);
            window.draw(shape);

            player2.get_coordinate(x1, y1);

            shape1.setPosition(x1, y1);

            window.draw(shape1);

            // end the current frame
            window.display();
        // }
        

        
    }

    return 0;
}