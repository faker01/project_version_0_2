#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <random>
#include <SFML/Audio.hpp>
#include "func/logger.h"

namespace gm
{
    // создаются инициализационные переменные
    float delta;
    sf::RenderWindow* window;
    sf::Texture* background_texture;
    sf::Text Score;
    int score;
    sf::Text BestScore;
    int bestScore;
    sf::Font font;
    std::string pipes[2] = { "up", "down" };
    int positions[3] = { 0, 1, 2 };


    // объект птица
    class Bird
    {
    private:
        sf::SoundBuffer JumpButton;
        sf::Sound JumpSound;
        sf::Texture* texture;
        float y, vel;

    public:
        // инициализация птицы
        Bird(int t1)
        {
            texture = new sf::Texture();
            if (t1 == 1)
            {
                texture->loadFromFile("textures/Best.png");
            }
            else
            {
                texture->loadFromFile("textures/bird.png");
            }
            if (!JumpButton.loadFromFile("Audio/JumpSound.wav"))
            {
                throw std::runtime_error("Failed to load sound: Audio/JumpSound.wav");
            }
            JumpSound.setBuffer(JumpButton);
            JumpSound.setVolume(100);
            y = 400;
            vel = 0;
        }

        ~Bird()
        {
            delete texture;
        }
        // прорисовка птицы
        void draw()
        {
            sf::Sprite bird_sprite(*texture);
            bird_sprite.setPosition(50, y);

            window->draw(bird_sprite);
        }
        // обновление позиции птицы
        void update()
        {
            vel += delta * 300;
            y += vel * delta;
            if (y < 0)
            {
                y = 0;
            }
            else
            {
                if (y > window->getSize().y - texture->getSize().y)
                {
                    y = window->getSize().y - texture->getSize().y;
                }
            }
        }
        // полёт птицы (поднимается на 200)
        void flap()
        {
            vel = -200;
            JumpSound.play();
        }
        // получение координаты y птицы
        int get_coordinate_y()
        {
            return y;
        }
    };
    Bird* bird;


    // объект верхняя труба
    class Pipe
    {
    private:
        sf::Texture* pipe;
        float x;
        float y;
        bool type;

    public:
        // инициализация верхней трубы
        Pipe(bool t)
        {
            type = t;
            pipe = new sf::Texture();
            pipe->loadFromFile("textures/pipe_" + pipes[type] + ".png");
            x = window->getSize().x + pipe->getSize().x;
            if (type == 0)
            {
                y = 100 * delta - 70;
            }
            else
            {
                y = window->getSize().y - pipe->getSize().y + 70;
            }

        }
        // прорисовка верхней трубы
        void draw()
        {
            sf::Sprite pipe_sprite(*pipe);
            pipe_sprite.setPosition(x, y);
            window->draw(pipe_sprite);
        }
        // обновление позиции верхней трубы
        void update()
        {
            x -= 100 * delta;
            if (x < 0)
            {
                x = window->getSize().x + pipe->getSize().x;
                int pos_y = std::rand() % 3;
                int p_y = positions[pos_y];
                if (type == 0)
                {
                    y = 100 * delta - 50 - 35 * p_y;
                    score++;
                }
                else
                {
                    y = window->getSize().y - pipe->getSize().y + 50 - 100 * delta - 35 * p_y;
                }

            }
        }
        // получение координаты y верхней трубы
        int get_coordinate_y()
        {
            if (type == 0)
            {
                return y + pipe->getSize().y;
            }
            else
            {
                return y;
            }
        }
        // получение координаты x верхней трубы
        int get_coordinate_x()
        {
            return x;
        }
    };
    Pipe* pipe_upper;
    Pipe* pipe_lower;


    // инициализация графики
    void setup(int t1)
    {
        score = 0;
        try
        {
            font.loadFromFile("textures/arial.ttf");
            Score.setFont(font);
            Score.setCharacterSize(24);
            Score.setPosition(10, 10);
            Score.setString("Score: 0");
            BestScore.setFont(font);
            BestScore.setCharacterSize(24);
            BestScore.setPosition(10, 40);
            BestScore.setString("Best Score:" + std::to_string(bestScore));
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to load font: Arial.ttf");
        }
        // создаётся окно
        try
        {
            window = new sf::RenderWindow(sf::VideoMode(400, 700), "game");
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to create window");
        }
        // создаётся птица
        try
        {
            bird = new Bird(t1);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to create bird");
        }
        // создаётся верхняя и нижняя труба 
        try
        {
            pipe_lower = new Pipe(1);
            pipe_upper = new Pipe(0);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to create pipes");
        }
        // создаётся фон
        try
        {
            background_texture = new sf::Texture();
            background_texture->loadFromFile("textures/background.jpg");
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to create background");
        }


    }


    // удаление всех объектов и графики
    void destroy()
    {
        delete window;
        delete bird;
        delete background_texture;
        delete pipe_lower;
        delete pipe_upper;
    }


    // работа с входящими операциями
    void handle_event(sf::Event& event)
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space) // единственная рабочая кнопка - пробел
            {
                // вызов функции прыжка
                bird->flap();
            }

        }
    }


    // обновление положения всех объектов
    void update()
    {
        try
        {
            bird->update();
            pipe_lower->update();
            pipe_upper->update();
            Score.setString("Score: " + std::to_string(score));
            if (score > bestScore)
            {
                bestScore = score;
                BestScore.setString("Best Score: " + std::to_string(bestScore));
            }
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to update frame");
        }
        
    }


    // прорисовка кадра
    void draw()
    {
        try
        {
            window->clear();

            window->draw(sf::Sprite(*background_texture));

            pipe_upper->draw();
            pipe_lower->draw();

            bird->draw();
            window->draw(Score);
            window->draw(BestScore);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to create a frame");
        }
    }


    // проверка на проигрыш
    bool check_loose()
    {

        int x_pu = pipe_upper->get_coordinate_x();
        int x_pl = pipe_lower->get_coordinate_x();
        int y_b = bird->get_coordinate_y();

        if ((x_pl < 121) || (x_pu < 121))
        {
            if (y_b < pipe_upper->get_coordinate_y())
            {
                return true;
            }
            if (y_b + 52 > pipe_lower->get_coordinate_y())
            {
                return true;
            }
        }
        return false;
    }


    // основная функция
    void game(int t)
    {
        ns_log::Logger log("game_log");
        std::srand(std::time(nullptr));
        try
        { 
            std::ifstream File("textures/best_score.txt");
            if (File.is_open())
            {
                File >> bestScore;
                File.close();
            }
            else
            {
                throw std::runtime_error("Failed to open file: textures/best_score.txt");
            }
        }
        catch(const std::exception& e)
        {
            log.send_message(e.what());
            std::cerr << e.what() << std::endl;
        }
        // вызов функции инициализации графики
        try
        {
            setup(t);
        }
        catch (const std::exception& e)
        {
            log.send_message(e.what());
            std::cerr << e.what() << std::endl;
        }
        // создание переменной дельты часов
        sf::Clock delta_clock;
        // старт игры
        log.send_message("start game");
        while (window->isOpen())
        {
            
            sf::Event event{};

            while (window->pollEvent(event))
            {
                handle_event(event);
            }
            // задание переменной часов
            delta = delta_clock.getElapsedTime().asMicroseconds() / 1000.0f / 1000.0f;
            delta_clock.restart();
            // вызов функции обновления и прорисовки кадра
            try
            {
                update();
            }
            catch (const std::exception& e)
            {
                log.send_message(e.what());
                std::cerr << e.what() << std::endl;
            }
            
            try
            {
                draw();
            }
            catch (const std::exception& e)
            {
                log.send_message(e.what());
                std::cerr << e.what() << std::endl;
            }
            // вызов функции вывода кадра на экран
            window->display();
            // вызов функции проверки на проигрыш
            if (check_loose())
            {
                try
                {
                    std::ofstream File("textures/best_score.txt");
                    if (File.is_open())
                    {
                        File << bestScore;
                        File.close();
                    }
                }
                catch (const std::exception& e)
                {
                    log.send_message("can't save results");
                    std::cout << e.what() << std::endl;
                }
                std::cout << "U loose(" << std::endl;
                log.send_message("end game");
                break;
            }

        }
        // вызов функции удаления графики
        destroy();

    }
}
