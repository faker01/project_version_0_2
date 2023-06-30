#include <iostream>
#include "func/game.h"
#include "func/change_directory.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>


int main()
{
    
    try
    {
        cd::change_common_directory();
        sf::RenderWindow window(sf::VideoMode(1200, 667), "game");

        sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
        if (!menuTexture1.loadFromFile("textures/111.png"))
        {
            throw std::runtime_error("Failed to load texture: 111.png");
        }
        if (!menuTexture2.loadFromFile("textures/222.png"))
        {
            throw std::runtime_error("Failed to load texture: 222.png");
        }
        if (!menuTexture3.loadFromFile("textures/333.png"))
        {
            throw std::runtime_error("Failed to load texture: 333.png");
        }
        if (!aboutTexture.loadFromFile("textures/about.png"))
        {
            throw std::runtime_error("Failed to load texture: about.png");
        }
        if (!menuBackground.loadFromFile("textures/BackMenu.jpg"))
        {
            throw std::runtime_error("Failed to load texture: BackMenu.jpg");
        }
        sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);

        sf::SoundBuffer buffer1, buffer2, buffer3;
        if (!buffer1.loadFromFile("Audio/ExitButton.wav"))
        {
            std::cout << "ERROR";
        }
        if (!buffer2.loadFromFile("Audio/StartButton.wav"))
        {
            std::cout << "ERROR";
        }
        if (!buffer3.loadFromFile("Audio/Audio.wav"))
        {
            std::cout << "ERROR";
        }
        sf::Sound ExitSound, StartSound, Audio_ERROR;
        StartSound.setBuffer(buffer2);
        ExitSound.setBuffer(buffer1);
        Audio_ERROR.setBuffer(buffer3);
        ExitSound.setVolume(100);
        StartSound.setVolume(100);
        Audio_ERROR.setVolume(100);

       

        bool isMenu = true;
        int menuNum = 0;

        menu1.setPosition(0, -4);
        menu2.setPosition(-3, -9);
        menu3.setPosition(1, -5);
        menuBg.setPosition(0, 0);

        std::cout << "textures included" << std::endl;

        //////////////////////////////МЕНЮ///////////////////
        while (isMenu)
        {
            menuNum = 0;
            window.clear(sf::Color(129, 181, 221));

            menu1.setColor(sf::Color::White);
            menu2.setColor(sf::Color::White);
            menu3.setColor(sf::Color::White);

            if (sf::IntRect(560, 236, 55, 20).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); StartSound.play(); menuNum = 1; }
            if (sf::IntRect(560, 295, 55, 20).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
            if (sf::IntRect(560, 358, 35, 20).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); ExitSound.play(); menuNum = 3; }
            if (sf::IntRect(560, 660, 5, 5).contains(sf::Mouse::getPosition(window))) { Audio_ERROR.play(); menuNum = 4; }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (menuNum == 1) { gm::game(); } //если нажали первую кнопку, то выходим из меню
                if (menuNum == 2) { window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
                if (menuNum == 3) { window.close(); std::cout << "Thanks for trying our game" << std::endl; }
                if (menuNum == 4) { gm::game(1); }
            }

            window.draw(menuBg);
            window.draw(menu1);
            window.draw(menu2);
            window.draw(menu3);

            window.display();
        }
        ////////////////////////////////////////////////////
    }
    catch (const std::exception& e)
    {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
