#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color // /home/sandro/MEMES/MANUX.jpg
        window.clear(sf::Color::White);

        // draw everything here...
        // window.draw(...);

        sf::Font font;
        
        if (!font.loadFromFile("../design/OpenSans-BoldItalic.ttf"))
        {
            std::cerr << "Error occurred when laoding font!" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        std::string input;
        std::cout << "Enter server ip address" << std::endl;
        std::cin >> input;

        sf::TcpSocket socket;
        sf::Socket::Status status = socket.connect(input, 53000);

        if (status != sf::Socket::Done)
        {
            std::cerr << "Error occurred when connecting socket!" << std::endl;
            exit(EXIT_FAILURE);
        }

        while (1)
        {
            char data[100];

            std::size_t received;

            if (socket.receive(data, 100, received) != sf::Socket::Done)
            {
                std::cerr << "Error occurred when receiving data!" << std::endl;
                exit(EXIT_FAILURE);
            }

            window.clear(sf::Color::White);

            sf::Text text;

            text.setFont(font);

            text.setString(data);
            text.setCharacterSize(25);
            text.setFillColor(sf::Color::Red);
            text.setStyle(sf::Text::Bold);

            window.draw(text);

            // end the current frame
            window.display();
        }
        

        
    }

    return 0;
}