#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <time.h>

#define N 20

sf::Texture blackTexture;
sf::Image transparentImage;


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




float r=1;

sf::Vector2u sizeOfImage;


class Dot{

public:

    sf::Vector2f position;
    float velocity;
    float angle;
    sf::Vector2f direction;

    void initialize()
    {
        position.x = 400;
        position.y = 400;

        velocity = randomFloat(0.1,0.5);

        angle = randomFloat(2*3.1416);
        direction.x = std::cos(angle);
        direction.y = std::sin(angle);
    }

    void update()
    {


        angle += randomFloat(-0.3,0.3);
        direction.x = std::cos(angle);
        direction.y = std::sin(angle);

        position.x += velocity*direction.x;
        position.y += velocity*direction.y;



        if (position.x <0)
        {
            position.x = sizeOfImage.x;
        }
        if (position.x >sizeOfImage.x)
        {
            position.x = 0;
        }

        if (position.y <0)
        {
            position.y = sizeOfImage.y;
        }
        if (position.y >sizeOfImage.y)
        {
            position.y = 0;
        }



        blackTexture.update(transparentImage, (unsigned int) position.x, (unsigned int) position.y);
    }
};





int main()
{
    srand(time(NULL));


    transparentImage.create((unsigned int) 2*r, (unsigned int) 2*r, sf::Color(0,0,0,0));


    sf::Image canvasImage;
    if(!canvasImage.loadFromFile("bird.jpg"))
        std::cout << "Image Loading Failed" << std::endl;


    sizeOfImage = canvasImage.getSize();

    sf::Texture canvasTexture;
    if(!canvasTexture.loadFromImage(canvasImage))
        std::cout << "canvasTexture Loading Failed" << std::endl;

    sf::Sprite canvasSprite;
    canvasSprite.setTexture(canvasTexture);






    sf::Image blackImage;
    blackImage.create(sizeOfImage.x, sizeOfImage.y, sf::Color(0,0,0));

    blackTexture.loadFromImage(blackImage);

    sf::Sprite blackSprite;
    blackSprite.setTexture(blackTexture);

    Dot dots[N];  for(unsigned short i=0; i<N; i++){dots[i].initialize();} // Array Constructor :)


    sf::RenderWindow window(sf::VideoMode(sizeOfImage.x, sizeOfImage.y), "Painting");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //usleep(400); // microseconds

        window.clear();

        window.draw(canvasSprite);
        for(unsigned short i=0; i<N; i++)
        {
            dots[i].update();
        }
        window.draw(blackSprite);

        window.display();
    }

    return 0;
}
