#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random> 
#include <time.h> 
#include<iostream>

using namespace std;
using namespace sf;
int direction = 0;
int numberFox = 3;
int score_Strawberry = 0;
int score_Watermelon = 0;
int score_Grape = 0;
bool dead = false;
bool pause = false;

class Fruit
{
public:
    double x;   // position x
    double y;   // position y
public:
    // Constructor 
    Fruit()
    {
        random_device rd;
        mt19937 nbr(rd());
        uniform_int_distribution<> dis(0, 550);
        x = (dis(nbr) / 2);
        y = (dis(nbr) / 2);
    }
};
class Player
{
public:
    double x;   // position x
    double y;   // position y
public:
    // Constructor
    Player()
    {
        x = 40;
        y = 40;
    }
};
class Fox
{
public:

    double x;   // position x
    double y;   // position y
    double dx;  //deplacement
    double dy;
public:
    // Constructor 
    Fox()
    {
        random_device rd;
        mt19937 nbr(rd());
        uniform_int_distribution<> dis(0, 5);
        x = 300;
        y = 300;
        dx = dis(nbr);
        dy = dis(nbr);
    }
    void move()
    {
        x = x + dx;
        y = y + dy;
        //Hacker sprite dimensions are  33 50
        if (x < 0 || x >(550))
        {
            dx = -dx;
            x += dx;
        }
        if (y < 0 || y >(550))
        {
            dy = -dy;
            y += dy;
        }
    }
};

int main()
{
    Player player;
    Fruit strawberry;
    Fruit watermelon;
    Fruit grape;
    Fox fox[25];

    RenderWindow window(VideoMode(600, 600), "Game");
    window.setFramerateLimit(60); // slow down the speed 
    Texture t0, t1, t2, t3, t4, t5, t6, t7, t8;
    t0.loadFromFile("images/background.png");
    t1.loadFromFile("images/farmer.png");
    t2.loadFromFile("images/fraise.png");
    t3.loadFromFile("images/watermelon.png");
    t4.loadFromFile("images/grape.png");
    t5.loadFromFile("images/fox.png");
    t6.loadFromFile("images/score.png");
    t7.loadFromFile("images/gameover.png");
    t8.loadFromFile("images/pause.png");

    Sprite sBackground(t0);
    Sprite sFarmer(t1);
    Sprite sStrawberry(t2);
    Sprite sWatermelon(t3);
    Sprite sGrape(t4);
    Sprite sFox(t5);
    Sprite sScore(t6);
    Sprite sGameover(t7);
    Sprite sPause(t8);


    sPause.setPosition(250, 250);
    //importing fonts
    Font font;
    font.loadFromFile("font/arial.ttf");
    Text scoreText1, scoreText2, scoreText3, scoreText4;
    scoreText1.setFont(font);
    scoreText2.setFont(font);
    scoreText3.setFont(font);
    scoreText4.setFont(font);

    //music

    Music musicbackground, musicgameover, musiceating;
    musicbackground.openFromFile("sound/background.ogv");
    musicbackground.play();
    musicbackground.setLoop(true);

    musicgameover.openFromFile("sound/gameover.ogv");

    musiceating.openFromFile("sound/eating.ogv");


    while (window.isOpen())
    {

        Event event;
        //les evenements
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)window.close();
            if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
            if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;
            if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
            if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 4;
            if (event.type = sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    pause = true;
                else if (event.mouseButton.button == sf::Mouse::Right)
                    pause = false;
            }

        }
        window.clear();

        window.draw(sBackground);

        if (dead) continue;
        if (!pause) {


            switch (direction)
            {
            case 1: player.x -= 4; break;
            case 2: player.x += 4; break;
            case 3: player.y -= 4; break;
            case 4: player.y += 4; break;
            }

            //borderline 
            if (player.x > 600) player.x = -42;
            if (player.x < -42) player.x = 600;
            if (player.y > 600) player.y = -65;
            if (player.y < -65) player.y = 600;


            for (int i = 0; i < numberFox; i++)
            {
                sFox.setPosition(fox[i].x, fox[i].y);
                window.draw(sFox);
                fox[i].move();


                if (sFarmer.getGlobalBounds().intersects(sFox.getGlobalBounds()))

                {

                    dead = true;
                    musicbackground.pause();
                    musicgameover.play();
                    window.draw(scoreText4);
                }
            }

            sFarmer.setPosition(player.x, player.y);
            sStrawberry.setPosition(strawberry.x, strawberry.y);
            sGrape.setPosition(grape.x, grape.y);
            sWatermelon.setPosition(watermelon.x, watermelon.y);


            if (sFarmer.getGlobalBounds().intersects(sStrawberry.getGlobalBounds()))
            {
                random_device rd;
                mt19937 s(rd());
                uniform_int_distribution<> dis(0, 550);
                strawberry.x = dis(s);
                strawberry.y = dis(s);
                score_Strawberry++;
                musiceating.play();
            }

            if (sFarmer.getGlobalBounds().intersects(sGrape.getGlobalBounds()))
            {
                random_device rd;
                mt19937 g(rd());
                uniform_int_distribution<> dis(0, 550);
                grape.x = dis(g);
                grape.y = dis(g);
                score_Grape++;
                musiceating.play();
            }

            if (sFarmer.getGlobalBounds().intersects(sWatermelon.getGlobalBounds()))
            {
                random_device rd;
                mt19937 w(rd());
                uniform_int_distribution<> dis(0, 550);
                watermelon.x = dis(w);
                watermelon.y = dis(w);
                score_Watermelon++;
                musiceating.play();
            }
        }



        //draw

        window.draw(sFarmer);
        window.draw(sStrawberry);
        window.draw(sGrape);
        window.draw(sWatermelon);

        scoreText1.setCharacterSize(20);
        scoreText2.setCharacterSize(20);
        scoreText3.setCharacterSize(20);
        scoreText4.setCharacterSize(50);

        scoreText1.setPosition(50, 10);
        scoreText2.setPosition(50, 40);
        scoreText3.setPosition(50, 70);
        scoreText4.setPosition(250, 400);


        scoreText1.setString(to_string(score_Strawberry));
        scoreText2.setString(to_string(score_Watermelon));
        scoreText3.setString(to_string(score_Grape));
        scoreText4.setString(to_string(score_Grape + score_Strawberry + score_Watermelon));

        window.draw(scoreText1);
        window.draw(scoreText2);
        window.draw(scoreText3);

        sScore.setPosition(10, 10);
        window.draw(sScore);

        if (dead) {
            window.draw(sGameover);

            window.draw(scoreText4);

        }
        if (pause)
        {
            window.draw(sPause);

        }


        window.display();



    }
    return 0;

}