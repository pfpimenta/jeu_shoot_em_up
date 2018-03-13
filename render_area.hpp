// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#pragma once

#ifndef RENDER_AREA_HPP
#define RENDER_AREA_HPP

#include "circle.hpp"

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <list>

#include "Vaisseau.hpp"


//forward declaration of QLabel
class QLabel;



class render_area : public QWidget
{
    Q_OBJECT
public:

    render_area(QWidget *parent = 0);
    ~render_area();

    /** Draw or not the circle when called */
    void change_draw_circle_state();

protected:
    /** Actual drawing function */
    void paintEvent(QPaintEvent *event);

private slots:

    /** Function called periodically at constant time interval by a timer */
    void update_timer(); 

private: //functions

    /** Insert current position and time inside the recording structures */
    void store_values(vec2 const& click);

    /** Deal with collision */
    vec2 collision_handling(vec2& p);

    /** Move forward in time */
    void numerical_integration();

private: //attributes

    /** The circle */
    circle circ;
    /** The vaisseau */
    Vaisseau vaisseau;
    /** The speed of the circle */
    vec2 speed;
    /** The time integration step */
    float dt;

    /** Timer for periodic time iteration */
    QTimer timer;
    /** Time accessor */
    QTime time;

};

#endif
