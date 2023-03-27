// tuts_plus_2d_1_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/System/Vector2.hpp>
#include "Character.h"

const int W = 1200;
const int H = 800;

class Game
{
public:
    Character* mPlayer;
    std::vector<bool>* mInputs;
    std::vector<bool>* mPrevInputs;

    void Start()
    {
        sf::RenderWindow window(sf::VideoMode(W, H), "SFML works!");
        window.setFramerateLimit(60);

        mInputs = new std::vector<bool>((int)KeyInput::Count);
        mPrevInputs = new std::vector<bool>((int)KeyInput::Count);

        mPlayer = new Character(window, mInputs, mPrevInputs);
        //mPlayer->CharacterInit(mInputs, mPrevInputs);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();

            this->Update();
            this->FixedUpdate();

            window.display();
        }
    }

    void Update()
    {        
        mInputs->at(KeyInput::GoRight) = Keyboard::isKeyPressed(Keyboard::Right);
        mInputs->at(KeyInput::GoLeft) = Keyboard::isKeyPressed(Keyboard::Left);
        mInputs->at(KeyInput::GoDown) = Keyboard::isKeyPressed(Keyboard::Down);
        mInputs->at(KeyInput::Jump) = Keyboard::isKeyPressed(Keyboard::Space);

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            int ii = 5;
            int ii2 = ii;
        }
    }
    void FixedUpdate()
    {
        mPlayer->CharacterUpdate();
    }
};

int main()
{
    Game *game = new Game;
    game->Start();

    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
