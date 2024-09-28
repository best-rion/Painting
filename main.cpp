#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

#define N 30

sf::Image image;



unsigned short randomInt(unsigned short _min, unsigned short _max)
{
    return _min + rand() % (_max - _min + 1 );
}

unsigned short randomInt(unsigned short _max)
{
    return randomInt(0,_max);
}



float randomFloat(float _min, float _max)
{
    return _min + ( (float) rand() / RAND_MAX ) * (_max - _min);
}

float randomFloat(float _max)
{
    return randomFloat(0,_max);
}






float r=2;
class Dot: public sf::CircleShape{

public:

    float velocity;
    sf::Vector2f direction;

    sf::Texture texture;

    void initialize()
    {
        velocity = randomFloat(0.5,1.5);

        float angle = randomFloat(2*3.1416);
        direction.x = std::cos(angle);
        direction.y = std::sin(angle);

        setRadius(r);
        setPosition(400,200);

        texture.loadFromImage( image,sf::IntRect(400,200, 2*r,2*r) );
        setTexture(&texture);
    }

    void update()
    {
        sf::Vector2f position = getPosition();


        std::cout << position.x << "," << position.y << std::endl;

        sf::Vector2f testNewPosition;

        testNewPosition.x = position.x + velocity*direction.x;
        testNewPosition.y = position.y + velocity*direction.y;

        if (testNewPosition.x <=0 || testNewPosition.x >=image.getSize().x)
        {
            direction.x *= -1;
        }
        if (testNewPosition.y <=0 || testNewPosition.y >=image.getSize().y)
        {
            direction.y *= -1;
        }

        position.x = position.x + velocity*direction.x;
        position.y = position.y + velocity*direction.y;

        setPosition(position);


        //// Set Texture ////
        texture.loadFromImage(image,sf::IntRect(position.x,position.y, 2*r,2*r));
    }
};





int main()
{
    srand(0);

    if(!image.loadFromFile("bird.jpg"))
        std::cout << "Image Loading Failed" << std::endl;


    sf::Vector2u sizeOfImage = image.getSize();


    sf::RenderWindow window(sf::VideoMode(sizeOfImage.x, sizeOfImage.y), "SFML works!");


    sf::Texture canvasTexture;
    if(!canvasTexture.create(sizeOfImage.x, sizeOfImage.y))
        std::cout << "canvasTexture Loading Failed" << std::endl;


    sf::Sprite sprite;
    sprite.setTexture(canvasTexture);

    Dot dots[N];  for(unsigned short i=0; i<N; i++){dots[i].initialize();} // Array Constructor :)



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        usleep(4000); // microseconds

        canvasTexture.update(window);

        window.clear(sf::Color(0,0,0));
        window.draw(sprite);

        for(unsigned short i=0; i<N; i++)
        {
            dots[i].update();
            window.draw(dots[i]);
        }
        window.display();
    }

    return 0;
}
