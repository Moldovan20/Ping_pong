#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    const int width(1200), height(800);
    const int ballSize(20);
    const int barWidth(30);
    const int Speed(10);
    int bordersSize(14);
    int barHeight(height / 4);
    int ballPositionX(width / 2 - ballSize / 2);
    int ballPositionY(height / 2 - ballSize / 2);
    int leftBarPositionX(30), leftBarPositionY((height - barHeight) / 2);
    int rightBarPositionX(width - 200), rightBarPositionY((height - barHeight) / 2);
    int scoreLeft(0), scoreRight(0);

    Text score;
    score.setCharacterSize(30);
    score.setPosition(width / 2-30, 40);
    score.setFillColor(Color::White);

    sf::RenderWindow window(sf::VideoMode(width, height), "Ping pong");

    Texture ballTexture, backgroundTexture, rightRacketTexture, leftRacketTexture;
    ballTexture.loadFromFile("pictures/ball.png");
    backgroundTexture.loadFromFile("pictures/tennisTable.jpg");
    rightRacketTexture.loadFromFile("pictures/rightRacket.png");
    leftRacketTexture.loadFromFile("pictures/leftRacket.png");

    Sprite ball(ballTexture), background(backgroundTexture),
    rightRacket(rightRacketTexture), leftRacket(leftRacketTexture);

    ball.setPosition(ballPositionX, ballPositionY);
    background.setPosition(0, 0);

    Vector2f ballDir = Vector2f(1.5f, -2);

    double delay(0.01), timer(0);

    Clock clock;

    bool onTop = true;
    bool onBottom = false;

    Font font;
    font.loadFromFile("sprites/ARLRDBD.TTF");
    score.setFont(font);

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))(rightBarPositionY > 0) ? rightBarPositionY -= 1*Speed : rightBarPositionY = 0;
        if (Keyboard::isKeyPressed(Keyboard::Left))(rightBarPositionY < height - barHeight) ? rightBarPositionY += 1*Speed : rightBarPositionY = height - barHeight;
        if (Keyboard::isKeyPressed(Keyboard::D))(leftBarPositionY > 0) ? leftBarPositionY -= 1*Speed : leftBarPositionY = 0;
        if (Keyboard::isKeyPressed(Keyboard::A))(leftBarPositionY < height - barHeight) ? leftBarPositionY += 1*Speed : leftBarPositionY = height - barHeight;

        if (timer > delay)
        {

            leftRacket.setPosition(leftBarPositionX, leftBarPositionY);
            rightRacket.setPosition(rightBarPositionX, rightBarPositionY);

            ballPositionX += ballDir.x*Speed;
            ballPositionY += ballDir.y*Speed;

            if (timer > delay)
            {

                if(onBottom)rightBarPositionY += 10;
                if (onTop)rightBarPositionY -= 10;
                if (rightBarPositionY >= 600)onTop = true, onBottom = false;
                if (rightBarPositionY <= 0)onTop = false, onBottom = true;
             
            timer = 0;
            }
                                   
            //top
            if (ballPositionY <= bordersSize)ballDir.y *= -1;
            //bottom
            if (ballPositionY >= height - barWidth * 2)ballDir.y *= -1;

            //left bar
            if (ballPositionX <= barWidth * 2 && ballPositionY <= leftBarPositionY + barHeight && ballPositionY >= leftBarPositionY)ballDir.x *= -1;
            if (ballPositionX <= 0)
            {
                scoreRight++;
                ballPositionX = width / 2 - ballSize / 2; ballPositionY = height / 2 - ballSize / 2;            
            }
            //right bar
            if (ballPositionX >= width - barWidth * 3 && ballPositionY <= rightBarPositionY + barHeight && ballPositionY >= rightBarPositionY)ballDir.x *= -1;
            if (ballPositionX >= width)
            {
 
                scoreLeft++;
                ballPositionX = width / 2 - ballSize / 2; ballPositionY = height / 2 - ballSize / 2;
            }

            score.setString(std::to_string(scoreLeft) + " | " + std::to_string(scoreRight));

            ball.setPosition(ballPositionX, ballPositionY);
            timer = 0;
        }
       
        window.clear();
        window.draw(background);
        window.draw(ball);
        window.draw(leftRacket);
        window.draw(rightRacket);
        window.draw(score);
        window.display();
    }
    return 0;
}