// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#pragma once
#ifndef NAVETTE_HPP
#define NAVETTE_HPP

//includes
#include "Objet_bougeant.hpp"
#include "vec2.hpp"

class Navette : public Objet_bougeant
{
  
public:
    Navette();
    ~Navette();


private:
  int ammunition;
};



#endif
