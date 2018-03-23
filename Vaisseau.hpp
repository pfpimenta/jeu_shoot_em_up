// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#pragma once
#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP

//includes
#include "Objet_bougeant.hpp"
#include "vec2.hpp"


class Vaisseau : public Objet_bougeant
{

public:
    Vaisseau();
    ~Vaisseau();
    void move();
    void perdreUneVie();
    int  getNumVies();
    void setNumVies(int new_num_vies);

private:
  int num_vies;
};



#endif
