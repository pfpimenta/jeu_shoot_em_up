// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#pragma once
#ifndef OBJET_BOUGEANT_HPP
#define OBJET_BOUGEANT_HPP

//includes
#include "vec2.hpp"
#include <QPixmap>

class Objet_bougeant
{
  
public:

    Objet_bougeant();
    ~Objet_bougeant();
    void setPosition(int x, int y);
    vec2 getPosition();
    void setSpeed(int x, int y);
    vec2 getSpeed();
    void move();
    
    
    QPixmap *pixmap; // l'image


private:
  vec2 position;
  vec2 speed;
  //QPixmap *pixmap; // l'image

};



#endif
