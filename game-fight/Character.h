#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>

struct HealthPoint : public sf::RectangleShape {
    sf::RectangleShape point;
    std::vector<sf::RectangleShape> HP;

    HealthPoint(int x = 200, int y = 20) : RectangleShape(sf::Vector2f(x, y)) {
        point.setSize(sf::Vector2f(10, 19));
        point.setFillColor(sf::Color::Green);
       
        for (int i = 0; i < x / 10; ++i) {
            HP.push_back(point);
            HP[i].setPosition(50 + (i * 10), 50);
        }
    }

    void reduce_hp() {
        HP.resize(HP.size() - 1);
    }
};

class Character
{
public:
    
    HealthPoint HP;
    static bool isPunched;

public:
    sf::RectangleShape hit_box;
    sf::RectangleShape punch_box;
    bool isReverse = false;
    Character();

    void move(int x, int y);
    void make_punch();
    void return_punch();
    void normal();
    void reverse();
    void setPos(int x, int y);
    void jump();
    void getPunched();
};

