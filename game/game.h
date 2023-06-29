#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>


// создаются инициализационные переменные
float delta;
sf::RenderWindow* window;
sf::Texture* background_texture;
sf::Text Score;
int score;
sf::Text BestScore;
int bestScore;
sf::Font font;


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
class Pipe_up
{
private:
    sf::Texture* pipe_up;
    float x;
    float y;

public:
    // инициализация верхней трубы
    Pipe_up()
    {
        pipe_up = new sf::Texture();
        pipe_up->loadFromFile("textures/pipe_up.png");
        x = window->getSize().x + pipe_up->getSize().x;
        y = 100 * delta;
    }
    // прорисовка верхней трубы
    void draw()
    {
        sf::Sprite up_sprite(*pipe_up);
        up_sprite.setPosition(x, y);
        window->draw(up_sprite);
    }
    // обновление позиции верхней трубы
    void update()
    {

        x -= 100 * delta;
        if (x < 0)
        {
            score ++;
            x = window->getSize().x + pipe_up->getSize().x;
        }
    }
    // получение координаты y верхней трубы
    int get_coordinate_y()
    {
        return y + pipe_up->getSize().y;
    }
    // получение координаты x верхней трубы
    int get_coordinate_x()
    {
        return x;
    }
};
Pipe_up* pipe_upper;


// объект нижняя труба
class Pipe_low
{
private:
    float x;
    float y;
    sf::Texture* pipe_low;
public:
    // инициализация нижней трубы
    Pipe_low()
    {
        pipe_low = new sf::Texture();
        pipe_low->loadFromFile("textures/pipe_down.png");
        x = window->getSize().x + pipe_low->getSize().x;
        y = window->getSize().y - pipe_low->getSize().y - 100 * delta;
    }
    // прорисовка нижней трубы
    void draw()
    {
        sf::Sprite up_sprite(*pipe_low);
        up_sprite.setPosition(x, y);
        window->draw(up_sprite);
    }
    // обновление позиции нижней трубы
    void update()
    {
        x -= 100 * delta;
        if (x < 0)
        {
            x = window->getSize().x + pipe_low->getSize().x;
        }
    }
    // получение координаты y нижней трубы
    int get_coordinate_y()
    {
        return y;
    }
    // получение координаты x нижней трубы
    int get_coordinate_x()
    {
        return x;
    }
};
Pipe_low* pipe_lower;


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
    pipe_lower = new Pipe_low();
    pipe_upper = new Pipe_up();
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
                std::cout << "'hahaha'" << std::endl;
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