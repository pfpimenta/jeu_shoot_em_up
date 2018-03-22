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
#include <vector>

#include "ui_mainwindow.h"
#include "Vaisseau.hpp"
#include "Ennemi.hpp"
#include "Tire.hpp"


//forward declaration of QLabel
class QLabel;



class render_area : public QWidget
{
    Q_OBJECT
public:

    render_area(QWidget *parent = 0);
    ~render_area();

    // start game : start spawning of ennemis
    void start_game();

    void setUi(Ui::MainWindow *ui);


protected:
    /** Actual drawing function */
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


private slots:

    /** Function called periodically at constant time interval by a timer */
    void update_timer();
    void enable_shot();
    void spawn_ennemi();


private: //functions

    // traitement de colisions entre les objects (vaisseau, ennemis, tires,...)
    void collisions();
    //mouvement des objects (vaisseau, ennemis, tires,...)
    void mouvement();

private: //attributes

    // flag for game started
    bool isGameStarted;
    // flag for game over
    bool isGameOver;
    // flag for being able to shot
    bool onPeutTirer;
    //nombre d'ennemis echapes
    int num_ennemis_echapes;
    //nombre d'ennemis tues
    int num_ennemis_tues;
    // compteur pour les nomes de fois que
    // la fonction spawn_ennemi a ete appellee
    int spawn_counter;
    // vitesse des ennemis
    int ennemisSpeed;
    // vitesse des ennemis
    int num_ennemis_par_wave;
    // temps pour entre les spawn des ennemis
    int ennemisSpawnSpeed;

    // game over text
    Objet_bougeant game_over_text;
    // fond
    Objet_bougeant fond1;
    Objet_bougeant fond2;
    /** The vaisseau */
    Vaisseau vaisseau;
    /** The vaisseau */
    std::vector<Ennemi*> ennemis;
    std::vector<Tire*> tires;

    /** Timer for periodic time iteration */
    QTimer timer;
    /** Timer for ennemy spawning */
    QTimer ennemiTimer;

    QTimer balleTimer;
    /** Time accessor */
    QTime time;

    QPixmap *pixmap;

    Ui::MainWindow *ui; // pour actualiser la fenetre

};

#endif
