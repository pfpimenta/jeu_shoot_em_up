// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Ennemi.hpp"


#define WINDOW_WIDTH 821
#define WINDOW_HEIGHT 541

#define TAILLE_ENNEMI_X 80
#define TAILLE_ENNEMI_Y 60


Ennemi::Ennemi()
{
    //std::cout<<"Constructor of Ennemi is called"<<std::endl;//debug
    pixmap->load("images/alien.png");
    // prendre un nombre aleatoire
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 30);
    int rand_int = uniform_dist(e1);
    float rand_float = ((float)rand_int)/35;
    setPosition(14*WINDOW_WIDTH/15, rand_float*(WINDOW_HEIGHT-TAILLE_ENNEMI_Y-10));
    int speed_y = 1 + (rand_int%3); // entre 1 et 3
    if (rand_int % 2 == 0) //50% de chance de aller par au dessus
    {
      speed_y = -speed_y;
    }
    setSpeed(-1, speed_y);
}

Ennemi::~Ennemi()
{
   //std::cout<<"Destructor of Ennemi is called"<<std::endl;//debug
}

void Ennemi::move(){
  vec2 pos = this->getPosition();
  vec2 speed = this->getSpeed();
  int x = pos.x;
  int y = pos.y;

    // quand il arrive aux bords verticaux, changer de sense
  if((y+TAILLE_ENNEMI_Y) >= (WINDOW_HEIGHT) || y <= 0){
    setSpeed(getSpeed().x,-getSpeed().y);
  }

  speed = this->getSpeed();
  x = (int) pos.x+speed.x;
  y = (int) pos.y+speed.y;

  this->setPosition(x, y);
}
