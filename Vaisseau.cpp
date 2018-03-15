// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Vaisseau.hpp"
#include <QKeyEvent>


Vaisseau::Vaisseau()
{
    std::cout<<"Constructor of Vaisseau is called"<<std::endl;
    setPosition(100, 200);
}

Vaisseau::~Vaisseau()
{
    std::cout<<"Destructor of Vaisseau is called"<<std::endl;
}
void Vaisseau::debugFonction(){
      std::cout<<"DEBUG VAISSEAU"<<std::endl;

}

void Vaisseau::moveUpToggle(bool move){
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
