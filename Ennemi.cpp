// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2

//includes

#include "Ennemi.hpp"


#define WINDOW_WIDTH 852
#define WINDOW_HEIGHT 676

Ennemi::Ennemi()
{
    std::cout<<"Constructor of Ennemi is called"<<std::endl;
    pixmap->load("/fs03/share/users/p.foletto-pimenta/home/jeu_shoot_em_up/images/alien.png");
    setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    setSpeed(-1, 0);
}

Ennemi::~Ennemi()
{
    std::cout<<"Destructor of Ennemi is called"<<std::endl;
}
