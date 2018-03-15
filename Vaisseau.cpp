// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Vaisseau.hpp"
#include <QKeyEvent>


#define WINDOW_WIDTH 852
#define WINDOW_HEIGHT 676


Vaisseau::Vaisseau()
{
    std::cout<<"Constructor of Vaisseau is called"<<std::endl;
    pixmap->load("/fs03/share/users/p.foletto-pimenta/home/jeu_shoot_em_up/images/vaisseau.png");
    setPosition(100, 200);
}

Vaisseau::~Vaisseau()
{
    std::cout<<"Destructor of Vaisseau is called"<<std::endl;
}
void Vaisseau::debugFonction(){
      std::cout<<"DEBUG VAISSEAU"<<std::endl;

}

void Vaisseau::setPosition(int x, int y){
  if(x > WINDOW_WIDTH )
    x = WINDOW_WIDTH;
  if(x < 0)
    x = 0;
  if(y >WINDOW_HEIGHT )
    y = WINDOW_HEIGHT;
  if(y < 0)
    y = 0;
  this->position = vec2(x,y);
}

void Vaisseau::moveUpToggle(bool move){
  //vec2 currentSpeed = getSpeed();
  moveUp = move;
}
void Vaisseau::moveDownToggle(bool move){
  moveDown = move;
}
void Vaisseau::moveRightToggle(bool move){
  moveRight = move;
}
void Vaisseau::moveLeftToggle(bool move){
  moveLeft = move;
}