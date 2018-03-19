// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Tire.hpp"


#define WINDOW_WIDTH 852
#define WINDOW_HEIGHT 676

#define TIRE_SPEED 10

Tire::Tire()
{
    std::cout<<"Constructor of Tire is called"<<std::endl;
    pixmap->load("images/tire.png");
    setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    setSpeed(-1, 0);
}
Tire::Tire(int x, int y)
{
    std::cout<<"Constructor of Tire is called"<<std::endl;
    pixmap->load("images/tire.png");
    setPosition(x, y);
    setSpeed(TIRE_SPEED, 0);
}


Tire::~Tire()
{
    std::cout<<"Destructor of Tire is called"<<std::endl;
}

