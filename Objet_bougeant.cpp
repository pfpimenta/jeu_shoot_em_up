// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Objet_bougeant.hpp"


Objet_bougeant::Objet_bougeant():      pixmap(new QPixmap)
{
    std::cout<<"Constructor of Objet_bougeant is called"<<std::endl;
    setPosition(0, 0);
}

Objet_bougeant::~Objet_bougeant()
{
    std::cout<<"Destructor of Objet_bougeant is called"<<std::endl;
}

void Objet_bougeant::setPosition(int x, int y){
  this->position = vec2(x,y);
}

vec2 	Objet_bougeant::getPosition(){
  return this->position;
}

void Objet_bougeant::setSpeed(int x, int y){
  this->speed = vec2(x,y);
}

vec2 Objet_bougeant::getSpeed(){
  return this->speed;
}


void Objet_bougeant::move(){
  this->position = vec2(this->position.x+this->speed.x, this->position.y+this->speed.y);
}

void loadImage(std::string img_path){
  // loads the sprite of the objet
  //this->pixmap
}

