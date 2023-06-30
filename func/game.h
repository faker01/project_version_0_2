#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <random>

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
                    std::cout << "pipe_up:" << y << "  " << p_y << std::endl;
                    score++;
                }
                else
                {
                    y = window->getSize().y - pipe->getSize().y + 50 - 100 * delta - 35 * p_y;
                    std::cout << "pipe_down:" << y << "  " << p_y << std::endl;
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
        font.loadFromFile("textures/arial.ttf");
        Score.setFont(font);
        Score.setCharacterSize(24);
        Score.setPosition(10, 10);
        Score.setString("Score: 0");
        BestScore.setFont(font);
        BestScore.setCharacterSize(24);
        BestScore.setPosition(10, 40);
        BestScore.setString("Best Score:" + std::to_string(bestScore));
        // создаётся окно
        window = new sf::RenderWindow(sf::VideoMode(400, 700), "game");
        // создаётся птица
        bird = new Bird(t1);
        // создаётся верхняя и нижняя труба 
        pipe_lower = new Pipe(1);
        pipe_upper = new Pipe(0);
        // создаётся фон
        background_texture = new sf::Texture();
        background_texture->loadFromFile("textures/background.jpg");

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


    // прорисовка кадра
    void draw()
    {
        window->clear();

        window->draw(sf::Sprite(*background_texture));

        pipe_upper->draw();
        pipe_lower->draw();

        bird->draw();
        window->draw(Score);
        window->draw(BestScore);
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
    void game(int t = 0)
    {
        std::srand(std::time(nullptr));
        std::ifstream File("textures/best_score.txt");
        if (File.is_open())
        {
            File >> bestScore;
            File.close();
        }
        // вызов функции инициализации графики
        setup(t);
        // создание переменной дельты часов
        sf::Clock delta_clock;
        // старт игры
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
            update();
            draw();
            // вызов функции вывода кадра на экран
            window->display();
            // вызов функции проверки на проигрыш
            if (check_loose())
            {
                std::ofstream File("textures/best_score.txt");
                if (File.is_open())
                {
                    File << bestScore;
                    File.close();
                }
                std::cout << "U loose(" << std::endl;
                break;
            }

        }
        // вызов функции удаления графики
        destroy();

    }
}
