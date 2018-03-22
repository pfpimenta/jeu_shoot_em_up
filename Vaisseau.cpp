// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Vaisseau.hpp"
#include <QKeyEvent>


#define WINDOW_WIDTH 821
#define WINDOW_HEIGHT 541

#define TAILLE_VAISSEAU_X 100
#define TAILLE_VAISSEAU_Y 60

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

void Vaisseau::perdreUneVie(){
      this->num_vies -= 1;
      std::cout<<"num vies"<<this->num_vies<<std::endl;
}

int Vaisseau::getNumVies(){
  return this->num_vies;
}

void Vaisseau::setNumVies(int new_num_vies){
  this->num_vies = new_num_vies;
}


void Vaisseau::debugFonction(){
      std::cout<<"DEBUG VAISSEAU"<<std::endl;
}

void Vaisseau::move(){

  int x = (int) this->getPosition().x+this->getSpeed().x;
  int y = (int) this->getPosition().y+this->getSpeed().y;
  if(x > WINDOW_WIDTH -TAILLE_VAISSEAU_X)
    x = WINDOW_WIDTH  - TAILLE_VAISSEAU_X;
  if(x < 0)
    x = 0;
  if(y > WINDOW_HEIGHT - TAILLE_VAISSEAU_Y )
    y = WINDOW_HEIGHT - TAILLE_VAISSEAU_Y;
  if(y < 0)
    y = 0;
  this->setPosition(x, y);
}
