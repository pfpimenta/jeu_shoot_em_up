// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Vaisseau.hpp"
#include <QKeyEvent>


#define WINDOW_WIDTH 852
#define WINDOW_HEIGHT 676
#define NUM_VIES_INITIAL 3


Vaisseau::Vaisseau()
{
    std::cout<<"Constructor of Vaisseau is called"<<std::endl;
    pixmap->load("images/vaisseau.png");
    this->setPosition(100, 200);
    this->setSpeed(0, 0);
    this->num_vies = NUM_VIES_INITIAL;
}

Vaisseau::~Vaisseau()
{
    std::cout<<"Destructor of Vaisseau is called"<<std::endl;
}

void Vaisseau::debugFonction(){
      std::cout<<"DEBUG VAISSEAU"<<std::endl;

}

void Vaisseau::move(){
 
  int x = (int) this->getPosition().x+this->getSpeed().x;
  int y = (int) this->getPosition().y+this->getSpeed().y; 
  if(x > 645 )
    x = 645;
  if(x < 0)
    x = 0;
  if(y > 440 )
    y = 440;
  if(y < 0)
    y = 0;
  this->setPosition(x, y);
}