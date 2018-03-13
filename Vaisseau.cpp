// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Vaisseau.hpp"



Vaisseau::Vaisseau()
{
    std::cout<<"Constructor of Vaisseau is called"<<std::endl;
    setPosition(0, 0);
}

Vaisseau::~Vaisseau()
{
    std::cout<<"Destructor of Vaisseau is called"<<std::endl;
}

