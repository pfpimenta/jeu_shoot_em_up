// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#pragma once
#ifndef ENNEMI_HPP
#define ENNEMI_HPP

//includes
#include "Objet_bougeant.hpp"
#include "vec2.hpp"
#include <random>

class Ennemi : public Objet_bougeant
{
  
public:
    Ennemi();
    ~Ennemi();
    void move();
private:

  
};



#endif
