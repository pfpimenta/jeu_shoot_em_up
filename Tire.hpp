// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#pragma once
#ifndef TIRE_HPP
#define TIRE_HPP

//includes
#include "Objet_bougeant.hpp"
#include "vec2.hpp"

class Tire : public Objet_bougeant
{
  
public:
    Tire();
    Tire(int x, int y);
    ~Tire();
private:
  
};



#endif
