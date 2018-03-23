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
#include <QKeyEvent>
class QPixmap;

class Objet_bougeant
{
  
public:

    Objet_bougeant();
    ~Objet_bougeant();
    void setPosition(int x, int y);
    void setPosition(vec2 newPos);
    vec2 getPosition();
    void setSpeed(int x, int y);
    void setSpeed(vec2 newSpeed);
    vec2 getSpeed();
    QPixmap* getPixmap();
    void setPixmap(QPixmap* pixmap);
    void loadImage(const char* imgName);
    void move();
    
protected:
  QPixmap *pixmap; // l'image
  
private:
  vec2 position;
  vec2 speed;
};



#endif
