// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Ennemi.hpp"


#define WINDOW_WIDTH 852
#define WINDOW_HEIGHT 676

Ennemi::Ennemi()
{
    std::cout<<"Constructor of Ennemi is called"<<std::endl;
    pixmap->load("images/alien.png");
    setPosition(WINDOW_WIDTH, WINDOW_HEIGHT/2);
    setSpeed(-1, 0);
}

Ennemi::~Ennemi()
{
    std::cout<<"Destructor of Ennemi is called"<<std::endl;
}

void Ennemi::move(){
  vec2 pos = this->getPosition();
  vec2 speed = this->getSpeed();
  int x =  pos.x;
  int y =  pos.y; 

  if(x < -10)
    //destruir ennemi !!!!!!!!!!!!!!!!
    setSpeed(-getSpeed().x, speed.y);
  if(y > 440 )
    setSpeed(getSpeed().x,-getSpeed().y);
  if(y < 0)
    setSpeed(getSpeed().x,-getSpeed().y);
  x = (int) pos.x+speed.x;
  y = (int) pos.y+speed.y; 
  
  this->setPosition(x, y);
}