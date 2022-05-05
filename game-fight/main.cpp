
#include <iostream>
#include <vector>
#include "Character.h"
#include <chrono>
struct Point {
    sf::RectangleShape hp;
    Point() {
        hp.setSize(sf::Vector2f(10, 40));
        hp.setFillColor(sf::Color::Green);
        hp.setPosition(sf::Vector2f(50, 50));
    }

};

using namespace std::chrono;

enum Condition {
    STAND,
    HITS,
    RUNRIGHT,
    RUNLEFT,
    JUMP,
    DOWN,
    FIRE
};

struct Size {
    int height;
    int width;
    Size(int x, int y) :height(y), width(x) {}
};

void animate_knight(sf::Sprite &sprite, int &frame, int *coordsX, int *coordsY, Size &size) {
    if (frame < 3)
        sprite.setTextureRect(sf::IntRect(coordsX[frame], coordsY[0], size.width, size.height));
    if (frame >= 3 && frame <= 5)
        sprite.setTextureRect(sf::IntRect(coordsX[frame], coordsY[1], size.width, size.height));
    if (frame >= 6 && frame < 9)
        sprite.setTextureRect(sf::IntRect(coordsX[frame], coordsY[2], size.width, size.height));
    if (frame == 8)
        frame = -1;
 }

void animate_enemy() {

}

struct Fireball {
    sf::RectangleShape rect;
    Fireball() {
        rect.setPosition(650, 400);
        rect.setSize(sf::Vector2f(30, 30));
    }
};

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1071, 600), "MK");
    // Load a sprite to display
    
    Condition condition = STAND;

    sf::Texture texture_stand;
    sf::Texture texture_hits;
    sf::Texture texture_run[2];
    sf::Texture texture_field;
    sf::Texture texture_road;
    sf::Texture texture_fire;
    sf::Texture texture_ghost;

    texture_fire.loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\fireball.png");
    texture_road.loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\road.png");
    texture_field.loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\Filed.png");
    texture_run[0].loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\knight-run.png");
    texture_run[1].loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\knight-run-rev.png");
    texture_stand.loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\knight-stand.png");
    texture_hits.loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\knight-hits.png");
    texture_ghost.loadFromFile("C:\\Users\\boola\\source\\repos\\game-fight\\assets\\enemy.png");

    
    sf::Sprite sprite_stand(texture_stand);
    sf::Sprite sprite_hits(texture_hits);
    sf::Sprite sprite_run[2];
    sf::Sprite sprite_field(texture_field);
    sf::Sprite sprite_road(texture_road);
    sf::Sprite sprite_fire(texture_fire);
    sf::Sprite sprite_ghost(texture_ghost);

    sprite_run[0].setTexture(texture_run[0]);
    sprite_run[1].setTexture(texture_run[1]);
    sprite_stand.setPosition(190, 370);
    sprite_hits.setPosition(217, 360);
    sprite_run[0].setPosition(250, 350);
    sprite_run[1].setPosition(217, 350);

    int coorX[9] = { 8, 511, 1015, 4, 507, 1011, 0, 503, 1007};
    int coorY[3] = { 0, 315, 668 };
    int coor_hitsX[9] = { 0, 505, 978, 0, 476, 940, 40, 505, 970 };
    int coor_hitsY[3] = { 0, 293, 603 };

 
    int coor_run_rightX[9] = { 8, 511, 1015, 4, 507, 1011, 0, 503, 1007 };
    int coor_run_rightY[3] = { 0, 200, 400 };

    int coor_run_leftX[9] = { 8, 498, 973, 4, 500, 975, 0, 513, 991 };
    int coor_run_leftY[3] = { 0, 225, 440 };

    Size size_stand(200, 175);
    Size size_hits(300, 200);
    Size size_run(215, 200);

    Character hero;
    Character enemy;
    enemy.setPos(700, 400);
    enemy.reverse();

    sprite_ghost.setPosition(650, 350);
    
    /*sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(50, 50));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(500, 500);*/

    int startX;
    int startY;
    int endX;
    int endY;
    
    int time = 0;
    const double g = 9.81;
    double v = 1;
    double jump = 2;
  

    bool isonGraund = true;
    bool isPressed = false;
    bool isFire = false;

    int frame = -1;
    int frame_ghost = -1;
    int frame_fire = -1;


    int time_ghost = 0;
    int timer_fire = 0;
    int timer = 0;

    sprite_fire.setPosition(1000, 350);

    std::vector<Fireball> fireballs;
    std::vector<sf::Sprite> sprt_fireballs;

   
    
    

   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        startX = enemy.hit_box.getPosition().x;
        startY = enemy.hit_box.getPosition().y;
        endX = enemy.hit_box.getPosition().x + enemy.hit_box.getSize().x;
        endY = enemy.hit_box.getPosition().y + enemy.hit_box.getSize().y;
      
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isonGraund) {
            condition = RUNRIGHT;
            isPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !isonGraund) {
            hero.move(1, 0);
            sprite_hits.move(1, 0);
            sprite_stand.move(1, 0);
            sprite_run[0].move(1, 0);
            sprite_run[1].move(1, 0);
            isPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !isonGraund) {
            hero.move(-1, 0);
            sprite_hits.move(-1, 0);
            sprite_stand.move(-1, 0);
            sprite_run[0].move(-1, 0);
            sprite_run[1].move(-1, 0);
            isPressed = true;
        }
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && isonGraund) {
             condition = RUNLEFT;
             isPressed = true;
         }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            condition = HITS;
            isPressed = true;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            condition = JUMP;
            isonGraund = false;
        }
        else if (isonGraund && !isPressed)
            condition = STAND;
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && timer >= 300) {

            timer = 0;
            isFire = true;
            fireballs.push_back(Fireball());
            sprt_fireballs.push_back(sprite_fire);
            sprt_fireballs[sprt_fireballs.size() - 1].setTextureRect(sf::IntRect(0, 0, 0, 0));
            hero.getPunched();
        }

        if (time_ghost == 60) {
            frame_ghost++;
            sprite_ghost.setTextureRect(sf::IntRect(frame_ghost * 113 + 16, 0, 129, 148));
            if (frame_ghost == 3)
                frame_ghost = -1;
            time_ghost = 0;
        }
        
        if (isFire && !fireballs.empty() ) {
            for (int i = 0; i < fireballs.size(); i++) {
                if (fireballs[i].rect.getPosition().x > 0) {
                    if (time == 60) {
                        frame_fire++;
                        sprt_fireballs[i].setTextureRect(sf::IntRect(frame_fire * 64, 0, 60, 50));
                        if (frame_fire == 7) {
                            frame_fire = -1; 
                        }
                        /*timer_fire = 0;*/
                    }
                    sprt_fireballs[i].setPosition(fireballs[i].rect.getPosition().x, fireballs[i].rect.getPosition().y);
                    fireballs[i].rect.move(-0.7, 0);
                    sprt_fireballs[i].move(-0.7, 0);
                }
                else {
                    fireballs.erase(fireballs.begin() + i);
                    sprt_fireballs.erase(sprt_fireballs.begin() + i);
                }
            }
           
            
           
        }
        timer++;
        switch (condition)
        {
        case STAND:
            if (time == 60) {
                time = 0;
                frame++;
                hero.return_punch();
                enemy.hit_box.setFillColor(sf::Color::Green);
                animate_knight(sprite_stand, frame, coorX, coorY, size_stand);
            }
            break;
        case HITS:
            if (time == 40) {
                time = 0;
                frame++;
                hero.make_punch();
                animate_knight(sprite_hits, frame, coor_hitsX, coor_hitsY, size_hits);
            }
            isPressed = false;
            break;
        case RUNRIGHT:
            if (time == 50) {
                time = 0;
                frame++;
                animate_knight(sprite_run[0], frame, coor_run_rightX, coor_run_rightY, size_run);
            }
            hero.move(1, 0);
            sprite_stand.move(1, 0);
            sprite_hits.move(1, 0);
            sprite_run[0].move(1, 0);
            sprite_run[1].move(1, 0);
            hero.normal();
            isPressed = false;
            break;
        case RUNLEFT:
            if (time == 50) {
                time = 0;
                frame++;
                animate_knight(sprite_run[1], frame, coor_run_leftX, coor_run_leftY, size_run);
            }
            hero.reverse();
            hero.move(-1, 0);
            sprite_stand.move(-1, 0);
            sprite_hits.move(-1, 0);
            sprite_run[1].move(-1, 0);
            sprite_run[0].move(-1, 0);
            isPressed = false;
            break;
        case JUMP:
            jump += g * 0.0005;
            hero.move(0, -jump);
            if (hero.hit_box.getPosition().y <= 100)
                condition = DOWN;
            isPressed = false;
            break;
        case DOWN:
            v += g * 0.00041;
            hero.move(0, v);
            if (hero.hit_box.getPosition().y >= 400) {
                isonGraund = true;
                condition = STAND;
                v = 1;
                jump = 2;
            }
            isPressed = false;
            break;
        case FIRE:
            
           
            break;
        default:
            break;
        }
         
        time++;
        time_ghost++;
        timer_fire++;
       

     
        window.clear(sf::Color::White);

       

        window.draw(sprite_field);
        window.draw(sprite_road);
  /*      window.draw(hero.hit_box);
        window.draw(hero.punch_box);*/
        if(condition == STAND)
            window.draw(sprite_stand);
        if(condition == HITS)
            window.draw(sprite_hits);
        if(condition == RUNRIGHT)
            window.draw(sprite_run[0]);
        if (condition == RUNLEFT)
            window.draw(sprite_run[1]);
     
            for (int i = 0; i < fireballs.size(); ++i) {
                /*window.draw(fireballs[i].rect);*/
                window.draw(sprt_fireballs[i]);
            }
            for (int i = 0; i < hero.HP.HP.size(); ++i) {
                window.draw(hero.HP.HP[i]);
            }
        window.draw(hero.HP);
        
      /*  window.draw(enemy.hit_box);
        window.draw(enemy.punch_box);*/
        window.draw(sprite_ghost);
       
        window.display();
      
        if (time > 60) {
            time = 0;
        }
      
    }
    return EXIT_SUCCESS;
}