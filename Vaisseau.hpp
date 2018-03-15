// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#pragma once
#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP

//includes
#include "vec2.hpp"
#include "Navette.hpp"

class Vaisseau : public Navette
{
  
public:

    Vaisseau();
    ~Vaisseau();
    void debugFonction();
    void moveUpToggle(bool move);
    void moveDownToggle(bool move);
    void moveRightToggle(bool move);
    void moveLeftToggle(bool move);

private:
  vec2 position;
  vec2 speed;
  bool moveUp;
  bool moveDown;
  bool moveRight;
  bool moveLeft;
};



#endif
