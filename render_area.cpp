// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#include "render_area.hpp"

#include <QPainter>
#include <QMouseEvent>
#include <QLabel>

#include <iostream>
#include <cassert>

render_area::render_area(QWidget *parent)
    :QWidget(parent),
      circ({200,150},25),
      vaisseau(),
      speed(0.0f,0.0f),
      dt(1/5.0f),
      timer(),
      time()
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //timer calling the function update_timer periodicaly
    connect(&timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    timer.start(30); //every 30ms
    
   std::cout<<"debug1"<<std::endl;
   vaisseau.pixmap->load("/fs03/share/users/p.foletto-pimenta/home/Bureau/Maj_Img/c_plus_plus/tp2/partie_10/images/vaisseau.png");
   std::cout<<"debug2"<<std::endl;


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

    //the actual drawing of the circle
    vec2 const& p=circ.center;
    float const r=circ.radius;
    painter.drawEllipse(p.x-r,p.y-r,2*r,2*r);
}

void render_area::update_timer()
{
    //called periodically
    
    repaint();
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