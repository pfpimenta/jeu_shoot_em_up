// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Navette.hpp"



Navette::Navette()
{
    std::cout<<"Constructor of Navette is called"<<std::endl;
    setPosition(0, 0);
}

Navette::~Navette()
{
    std::cout<<"Destructor of Navette is called"<<std::endl;
}
