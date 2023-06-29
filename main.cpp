#include <iostream>
#include "game/game.h"
#include <SFML/Graphics.hpp>
#include <windows.h>


void c()
{
    std::string path, new_path = "";
    TCHAR buffer[MAX_PATH];
    GetCurrentDirectory(sizeof(buffer), buffer);
    CharToOemA(buffer, buffer);
    path = buffer;
    int k;
    if (path[path.size() - 1] == 'g')
    {
        k = 20;
    }
    else
    {
        k = 21;
    }
    for (int i = 0; i < path.size() - k; i++)
    {
        new_path = new_path + path[i];
    }
    char new_path_char[256];
    strcpy(new_path_char, new_path.c_str());
    SetCurrentDirectory(new_path_char);
}


int main()
{
    c();
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1200, 667), "game");

    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("textures/111.png");
    menuTexture2.loadFromFile("textures/222.png");
    menuTexture3.loadFromFile("textures/333.png");
    aboutTexture.loadFromFile("textures/about.png");
    menuBackground.loadFromFile("textures/BackMenu.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
    

    bool isMenu = 1;
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

        if (sf::IntRect(560, 236, 55, 20).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
        if (sf::IntRect(560, 295, 55, 20).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
        if (sf::IntRect(560, 358, 35, 20).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }
        

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            
            if (menuNum == 1) { game(); } //если нажали первую кнопку, то выходим из меню
            if (menuNum == 2) { window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); return 0;}

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        
        window.display();
    }
    ////////////////////////////////////////////////////
}

