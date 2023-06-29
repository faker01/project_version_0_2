#include <iostream>
///#include "game/game.h"
#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(400, 700), "game");

    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("textures/111.png");
    menuTexture2.loadFromFile("textures/222.png");
    menuTexture3.loadFromFile("textures/333.png");
    aboutTexture.loadFromFile("textures/about.png");
    menuBackground.loadFromFile("textures/BackMenu.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);


    bool isMenu = 1;
    int menuNum = 0;

    menu1.setPosition(-160, -20);
    menu2.setPosition(-160, 100);
    menu3.setPosition(-160, 200);
    menuBg.setPosition(0, 0);



    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {

        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);

        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(170, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
        if (sf::IntRect(100, 140, 300, 50).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
        if (sf::IntRect(100, 200, 300, 50).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false; //если нажали первую кнопку, то выходим из меню
            if (menuNum == 2) { window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); isMenu = false;}

        }

        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.draw(menuBg);
        window.display();
    }
    ////////////////////////////////////////////////////
}

