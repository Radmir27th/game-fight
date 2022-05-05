#include "Character.h"

Character::Character() {
    hit_box.setSize(sf::Vector2f(50, 100));
    hit_box.setFillColor(sf::Color::Green);
    hit_box.setPosition(320, 400);
    punch_box.setSize(sf::Vector2f(75, 40));
    punch_box.setFillColor(sf::Color(255, 0, 0, 100)/*sf::Color::Transparent*/);
    punch_box.setPosition(345, 400);
    HP.setOutlineThickness(10.0f);
    HP.setOutlineColor(sf::Color::Black);
    HP.setFillColor(sf::Color::Transparent);
    HP.setPosition(50, 50);
  

}

void Character::move(int x, int y) {
    hit_box.move(x, y);
    punch_box.move(x, y);
}

void Character::make_punch() {
    if (isReverse)
        punch_box.setSize(sf::Vector2f(-150, 40));
    else
        punch_box.setSize(sf::Vector2f(150, 40));
}
void Character::return_punch() {
    if (isReverse)
        punch_box.setSize(sf::Vector2f(-75, 40));
    else
        punch_box.setSize(sf::Vector2f(75, 40));
}

void Character::jump() {
    int hb_now = hit_box.getPosition().y;
    while (hit_box.getPosition().y >= hb_now - 10){
        hit_box.setPosition(hit_box.getPosition().x, hit_box.getPosition().y - 1);
        punch_box.setPosition(punch_box.getPosition().x, hit_box.getPosition().y - 1);
    }
}

void Character::reverse() {
    punch_box.setSize(sf::Vector2f(-75, 40));
    isReverse = true;
}
void Character::normal() {
    punch_box.setSize(sf::Vector2f(75, 40));
    isReverse = false;
}

void Character::setPos(int x, int y) {
    hit_box.setPosition(x, y);
    punch_box.setPosition(x + 25, y);
}

void Character::getPunched() {
    HP.reduce_hp();
}