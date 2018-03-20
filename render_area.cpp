// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#include "render_area.hpp"

#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>

#include <iostream>
#include <cassert>


#define WINDOW_WIDTH 821
#define WINDOW_HEIGHT 541

#define TAILLE_VAISSEAU_X 180
#define TAILLE_VAISSEAU_Y 100

#define TAILLE_ENNEMI_X 80
#define TAILLE_ENNEMI_Y 60

#define TAILLE_TIRE_X 20
#define TAILLE_TIRE_Y 18

#define DIST_HIT 30 //''hitbox''

render_area::render_area(QWidget *parent)
          :QWidget(parent),
          num_ennemis_echapes(0),
          fond1(), // fond
          fond2(), // fond
          vaisseau(),
          ennemis(),
          tires(),
          speed(0.0f,0.0f),
          dt(1/5.0f),
          timer(),
          ennemiTimer(),
          time()
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //timer calling the function update_timer periodicaly
    connect(&timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    timer.start(30); //every 30ms
    //timer calling the function update_timer periodicaly
    connect(&ennemiTimer, SIGNAL(timeout()), this, SLOT(spawn_ennemi()));
    ennemiTimer.start(5000); //every 5000ms=5s

   //fond loadImage
   fond1.pixmap->load("images/background.png");
   fond2.pixmap->load("images/background.png");

   fond1.setSpeed(-1,0);
   fond2.setSpeed(-1,0);
   fond2.setPosition(WINDOW_WIDTH,0);

   // ennemi
   //Ennemi* testEnnemi = new Ennemi();
   //ennemis.push_back(testEnnemi);

}

render_area::~render_area()
{}



void render_area::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen;
    pen.setWidth(1.0);
    pen.setColor(Qt::blue);
    painter.setPen(pen);

    QBrush brush = painter.brush();
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);



     // afficher le fond
    vec2 pos = fond1.getPosition();
    painter.drawPixmap(pos.x,pos.y,WINDOW_WIDTH,WINDOW_HEIGHT,*fond1.pixmap);
    pos = fond2.getPosition();
    painter.drawPixmap(pos.x,pos.y,WINDOW_WIDTH,WINDOW_HEIGHT,*fond2.pixmap);
     // afficher le vaisseau
    pos = vaisseau.getPosition();
    painter.drawPixmap(pos.x,pos.y,TAILLE_VAISSEAU_X,TAILLE_VAISSEAU_Y,*vaisseau.pixmap);
     // afficher les ennemis
    for(auto& ennemi : ennemis){
        pos = ennemi->getPosition();
	      painter.drawPixmap(pos.x,pos.y,TAILLE_ENNEMI_X,TAILLE_ENNEMI_Y,*ennemi->pixmap);
    }
    //afficher les tirs
    for(auto& tire : tires){
        pos = tire->getPosition();
	      painter.drawPixmap(pos.x,pos.y,TAILLE_TIRE_X,TAILLE_TIRE_Y,*tire->pixmap);
    }

}

void render_area::mouvement(){
  // movement du fond
  fond1.move();
  vec2 pos = fond1.getPosition();
  if(pos.x == -WINDOW_WIDTH)
    fond1.setPosition(WINDOW_WIDTH, pos.y);
  fond2.move();
  pos = fond2.getPosition();
  if(pos.x == -WINDOW_WIDTH)
    fond2.setPosition(WINDOW_WIDTH, pos.y);
  // movement des ennemis
  for(auto& ennemi : ennemis){
        pos = ennemi->getPosition();
        ennemi->move();
  }
  // movement de la vaisseau
  vaisseau.move();
  // movement des tires
  for(auto& tire : tires){
      pos = tire->getPosition();
      tire->move();
  }
}

void render_area::collisions(){
  std::vector<Ennemi*>::iterator it;
  for (it = ennemis.begin(); it != ennemis.end();it++)
  {
    Ennemi* ennemi = *it;
    vec2 pos = ennemi->getPosition();
    float ennemi_x_center = pos.x + (TAILLE_ENNEMI_X/2);
    float ennemi_y_center = pos.y + (TAILLE_ENNEMI_Y/2);

    //ennemis qui ont ete frappe par un tire
    std::vector<Tire*>::iterator itTire;
    for(itTire = tires.begin(); itTire != tires.end(); ){
        Tire* tire = *itTire;
        vec2 posTire = tire->getPosition();
        float tire_x_center = posTire.x + (TAILLE_TIRE_X/2);
        float tire_y_center = posTire.y + (TAILLE_TIRE_Y/2);
        //calculer la distance entre les 2 centres
        float dist = std::sqrt( std::pow((ennemi_x_center -tire_x_center), 2) + std::pow((ennemi_y_center -tire_y_center), 2));
        float dist_x = std::pow((ennemi_x_center -tire_x_center), 2);
        float dist_y = std::pow((ennemi_y_center -tire_y_center), 2);
        if(dist < DIST_HIT){
          //increment counter
          num_ennemis_tues += 1;
          std::cout << "---------\n woooohoooo!!! HIT!!!\n-----------\n\n\n";
          std::cout << "dist:"<<dist<<" dist x: "<<dist_x<<" dist y: "<<dist_y<<"\n";
          //ennemi.~Ennemi();
          //delete *tire;
          //it = ennemis.erase(it);
          itTire = tires.erase(itTire);
          // ne marche pas, je ne sais pas pouquoi
          // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }else{
          itTire++;
        }
    }
  }
}

void render_area::keyPressEvent(QKeyEvent *event)
{
  //std::cout<<"keyPressEvent appelle"<<std::endl;
  vec2 vitesse = vaisseau.getSpeed();

  //mouvement horizontal
  if(event->key() == Qt::Key_Left) {
     // std::cout<<"left"<<std::endl;
	vaisseau.setSpeed(-5, vitesse.y);
  }else if(event->key() == Qt::Key_Right) {
      //std::cout<<"right"<<std::endl;
	vaisseau.setSpeed(5, vitesse.y);
  }

  // mouvement vertical
  if(event->key() == Qt::Key_Down) {
      //std::cout<<"down"<<std::endl;
      vaisseau.setSpeed(vitesse.x, 5);
  }else if(event->key() == Qt::Key_Up) {
      //std::cout<<"up"<<std::endl;
	vaisseau.setSpeed(vitesse.x, -5);
  }

  //tire
   if(event->key() == Qt::Key_Space) {
      //std::cout<<"space"<<std::endl;
      vec2 pos = vaisseau.getPosition();
      Tire* tire=new Tire(pos.x + TAILLE_VAISSEAU_X/2, pos.y + TAILLE_VAISSEAU_Y/2);
      tires.push_back(tire);
  }

}

void render_area::keyReleaseEvent(QKeyEvent *event)
  {
    if(event->isAutoRepeat())
      return;
    if(event->key() == Qt::Key_Left) {
	//std::cout<<"left off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(0, vitesse.y);
    }else if(event->key() == Qt::Key_Right) {
	//std::cout<<"right off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(0, vitesse.y);
    }else if(event->key() == Qt::Key_Down) {
	//std::cout<<"down off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(vitesse.x, 0);
    }else if(event->key() == Qt::Key_Up) {
	//std::cout<<"up off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(vitesse.x, 0);
    }
}


void render_area::update_timer()
{
    //called periodically (every 30ms)
    collisions(); // traiter les colisions
    mouvement(); // mouvement des objects
    repaint(); // affichage des objects
}

void render_area::spawn_ennemi()
{
    //called periodically (every 5s)
    Ennemi* nouveauEnnemi = new Ennemi();
    ennemis.push_back(nouveauEnnemi);
    std::cout<<"spawn ennemi!! \nnum ennemis :"<< ennemis.size() <<std::endl;
    std::cout<<"num tires :"<< tires.size() <<std::endl;


    std::vector<Ennemi*>::iterator it;
    for (it = ennemis.begin(); it != ennemis.end(); )
	  {
      Ennemi* ennemi = *it;
      vec2 pos = ennemi->getPosition();
      // ennemis qui ont passe l'ecran
      if(pos.x <= -100){
        //destroy the object
        it = ennemis.erase(it);
        //increment counter
        num_ennemis_echapes += 1;
      }else{
        it++;
      }
    }


    std::vector<Tire*>::iterator itTire;
    for (itTire = tires.begin(); itTire != tires.end(); )
	  {
      Tire* tire = *itTire;
      vec2 pos = tire->getPosition();
      // ennemis qui ont passe l'ecran
      if(pos.x >= WINDOW_WIDTH + 200){
        //destroy the object
        std::cout<<"TIRE LOIN!! \nnum tires :"<< tires.size() <<std::endl;
        std::cout<<"tire position : "<< tire->getPosition() <<std::endl;
        itTire = tires.erase(itTire);
      }else{
        itTire++;
      }
    }

}
