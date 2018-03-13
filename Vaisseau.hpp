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

private:
  vec2 position;
  vec2 speed;
};



#endif
