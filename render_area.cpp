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


#define WINDOW_WIDTH 852
#define WINDOW_HEIGHT 676


render_area::render_area(QWidget *parent)
    :QWidget(parent),
      vaisseau(),
      ennemis(),
      fond1(), // fond
      fond2(), // fond
      speed(0.0f,0.0f),
      dt(1/5.0f),
      timer(),
      //ennemiTimer(),
      time()
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //timer calling the function update_timer periodicaly
    connect(&timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    timer.start(30); //every 30ms
    //timer calling the function update_timer periodicaly
    //connect(&ennemiTimer, SIGNAL(timeout()), this, SLOT(spawn_ennemi()));
    //ennemiTimer.start(5000); //every 5000ms=5s
      
   //fond loadImage
   fond1.pixmap->load("images/background.png");
   fond2.pixmap->load("images/background.png");
   
   fond1.setSpeed(-1,0);
   fond2.setSpeed(-1,0);
   fond2.setPosition(852,0);
   
   // ennemi
   Ennemi* testEnnemi = new Ennemi();
   ennemis.push_back(*testEnnemi);
   
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

    // movement du fond
    fond1.move();
    vec2 pos = fond1.getPosition();
    if(pos.x == -WINDOW_WIDTH)
      fond1.setPosition(WINDOW_WIDTH, pos.y);
    fond2.move();
    pos = fond2.getPosition();
    if(pos.x == -WINDOW_WIDTH)
      fond2.setPosition(WINDOW_WIDTH, pos.y);
    // movement des objets     
    for(auto& ennemi : ennemis){
        pos = ennemi.getPosition();
	ennemi.move();
    }
    // movement de la vaisseau     
    vaisseau.move();

    
     // afficher le fond
    pos = fond1.getPosition();
    painter.drawPixmap(pos.x,pos.y,WINDOW_WIDTH,WINDOW_HEIGHT,*fond1.pixmap);
    pos = fond2.getPosition();
    painter.drawPixmap(pos.x,pos.y,WINDOW_WIDTH,WINDOW_HEIGHT,*fond2.pixmap);
     // afficher le vaisseau
    pos = vaisseau.getPosition();
        std::cout<<"position : " << pos<<std::endl;
    painter.drawPixmap(pos.x,pos.y,180,100,*vaisseau.pixmap);
     // afficher les ennemis
    for(auto& ennemi : ennemis){
        pos = ennemi.getPosition();
	painter.drawPixmap(pos.x,pos.y,100,75,*ennemi.pixmap); 
    }
}

 
void render_area::keyPressEvent(QKeyEvent *event)
{
  //std::cout<<"keyPressEvent appelle"<<std::endl;
  
  if(event->key() == Qt::Key_Left) {
      std::cout<<"left"<<std::endl;
      vec2 vitesse = vaisseau.getSpeed();
      if(vitesse.x <= -5){
	vaisseau.setSpeed(-5, vitesse.y);
      }else{
	vaisseau.setSpeed(vitesse.x-2, vitesse.y);
      }
      
  }else if(event->key() == Qt::Key_Right) {
      std::cout<<"right"<<std::endl;
      vec2 vitesse = vaisseau.getSpeed();
      if(vitesse.x >= 5){
	vaisseau.setSpeed(5, vitesse.y);
      }else{
	vaisseau.setSpeed(vitesse.x+2, vitesse.y);
      }
  }else if(event->key() == Qt::Key_Down) {
      std::cout<<"down"<<std::endl;
      vec2 vitesse = vaisseau.getSpeed();
      if(vitesse.y >= 5){
	vaisseau.setSpeed(vitesse.x, 5);
      }else{
	vaisseau.setSpeed(vitesse.x, vitesse.y+2);
      }
  }else if(event->key() == Qt::Key_Up) {
      std::cout<<"up"<<std::endl;
      vec2 vitesse = vaisseau.getSpeed();
      if(vitesse.y <= -5){
	vaisseau.setSpeed(vitesse.x, -5);
      }else{
	vaisseau.setSpeed(vitesse.x, vitesse.y-2);
      }
  }
}

void render_area::keyReleaseEvent(QKeyEvent *event)
  {
    if(event->isAutoRepeat())
      return;
    if(event->key() == Qt::Key_Left) {
	std::cout<<"left off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(0, vitesse.y);
    }else if(event->key() == Qt::Key_Right) {
	std::cout<<"right off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(0, vitesse.y);
    }else if(event->key() == Qt::Key_Down) {
	std::cout<<"down off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(vitesse.x, 0);
    }else if(event->key() == Qt::Key_Up) {
	std::cout<<"up off"<<std::endl;
	vec2 vitesse = vaisseau.getSpeed();
	vaisseau.setSpeed(vitesse.x, 0);
    }
}
 

void render_area::update_timer()
{
    //called periodically
    repaint();
}

void render_area::spawn_ennemi()
{
    //called periodically
    std::cout<<"spawn ennemi"<<std::endl;
}


vec2 render_area::collision_handling(vec2& p)
{
    vec2 new_speed=speed;

    //size of the window
    float const h=height();
    float const w=width();

    //radius of the sphere
    float const r=circ.radius;

    //special condition in cases of collision
    bool collision=false;
    bool collision_wall=false;

    //collision with the ground
    if(p.y+r>h)
    {
        p.y=h-r;
        new_speed.y *= -1;
        collision=true;
    }
    //collision with the left wall
    if(p.x-r<0)
    {
        p.x=r;
        new_speed.x *= -1;
        collision=true;
        collision_wall=true;
    }
    //collision with the right wall
    if(p.x+r>w)
    {
        p.x=w-r;
        new_speed.x *= -1;
        collision=true;
        collision_wall=true;
    }
    //collision with the top wall
    if(p.y-r<0)
    {
        p.y=r;
        new_speed.y *= -1;
        collision=true;
        collision_wall=true;
    }


    return new_speed;

}