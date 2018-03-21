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

#define TAILLE_VAISSEAU_X 100
#define TAILLE_VAISSEAU_Y 60

#define TAILLE_ENNEMI_X 180//80
#define TAILLE_ENNEMI_Y 250//60

#define TAILLE_TIRE_X 24
#define TAILLE_TIRE_Y 16

#define TAILLE_GAME_OVER_TEXT_X 300
#define TAILLE_GAME_OVER_TEXT_Y 200

#define VITESSE_VAISSEAU 5

#define DIST_HIT 30 //''hitbox''

render_area::render_area(QWidget *parent)
          :QWidget(parent),
          isGameStarted(false),
          onPeutTirer(true),
          num_ennemis_echapes(0),
          num_ennemis_tues(0),
          spawn_counter(0),
          game_over_text(),
          fond1(), // fond
          fond2(), // fond
          vaisseau(),
          ennemis(),
          tires(),
          timer(),
          ennemiTimer(),
	        balleTimer(),
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
    //timer calling the function update_timer periodicaly
    connect(&balleTimer, SIGNAL(timeout()), this, SLOT(enable_shot()));



    //game_over_text load image
    game_over_text.pixmap->load("images/game_over.png");
    game_over_text.setPosition((WINDOW_WIDTH- TAILLE_GAME_OVER_TEXT_X)/2, (WINDOW_HEIGHT - TAILLE_GAME_OVER_TEXT_Y)/2);

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

void render_area::start_game(){
  isGameStarted = true;
  this->setFocus();
}

void render_area::setUi(Ui::MainWindow *ui){
  this->ui = ui; //oui
}


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

    vec2 pos;



     // afficher le fond
    pos = fond1.getPosition();
    painter.drawPixmap(pos.x,pos.y,WINDOW_WIDTH,WINDOW_HEIGHT,*fond1.pixmap);
    pos = fond2.getPosition();
    painter.drawPixmap(pos.x,pos.y,WINDOW_WIDTH,WINDOW_HEIGHT,*fond2.pixmap);
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
    // afficher le vaisseau
    pos = vaisseau.getPosition();
    painter.drawPixmap(pos.x,pos.y,TAILLE_VAISSEAU_X,TAILLE_VAISSEAU_Y,*vaisseau.pixmap);
    // afficher le text de game over
    if(isGameOver == true){
        pos = game_over_text.getPosition();
        painter.drawPixmap(pos.x, pos.y, TAILLE_GAME_OVER_TEXT_X, TAILLE_GAME_OVER_TEXT_Y, *game_over_text.pixmap);
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
  for (it = ennemis.begin(); it != ennemis.end();)
  {
    Ennemi* ennemi = *it;
    bool ennemiFrappe = false;
    vec2 pos = ennemi->getPosition();
    float ennemi_x_center = pos.x + (TAILLE_ENNEMI_X/2);
    float ennemi_y_center = pos.y + (TAILLE_ENNEMI_Y/2);

    //ennemis qui ont ete frappe par un tire
    std::vector<Tire*>::iterator itTire;
    for(itTire = tires.begin(); itTire != tires.end();){
        Tire* tire = *itTire;
        vec2 posTire = tire->getPosition();
        float tire_x_center = posTire.x + (TAILLE_TIRE_X/2);
        float tire_y_center = posTire.y + (TAILLE_TIRE_Y/2);
        //calculer la distance entre les 2 centres
        float dist = std::sqrt( std::pow((ennemi_x_center -tire_x_center), 2) + std::pow((ennemi_y_center -tire_y_center), 2));
        if(dist < DIST_HIT){
	  //debug
          //std::cout << "---------\n woooohoooo!!! HIT!!!\n-----------\n\n\n";
          //std::cout << " num_ennemis_tues : "<<num_ennemis_tues << '\n'<< "num_ennemis_echapes : "<<num_ennemis_echapes<<'\n';
          //increment counter
          num_ennemis_tues += 1;
          // destruir ennemi et tire
          delete tire;
          delete ennemi;
          it = ennemis.erase(it);
          itTire = tires.erase(itTire);
	  // actualiser l'ecran
	  std::string numEnnemisTuesString = std::to_string(num_ennemis_tues);
	  ui->label_4->setText(QString::fromStdString(numEnnemisTuesString));
          ennemiFrappe = true;
        }else{
          itTire++;
        }
    }
    vec2 posVaisseau = vaisseau.getPosition();
    float vaisseau_x_center = posVaisseau.x + (TAILLE_VAISSEAU_X/2);
    float vaisseau_y_center = posVaisseau.y + (TAILLE_VAISSEAU_Y/2);
    //calculer la distance entre les 2 centres
    float dist = std::sqrt( std::pow((ennemi_x_center -vaisseau_x_center), 2) + std::pow((ennemi_y_center -vaisseau_y_center), 2));
    if(dist < TAILLE_VAISSEAU_Y/2+TAILLE_ENNEMI_Y/2){
	  //debug
	  //std::cout << "---------\n booooooo!!! mort!!!\n-----------\n\n\n";

          //destruir l'ennemi
	  delete ennemi;
          it = ennemis.erase(it);
          ennemiFrappe = true;
	  // perdre 1 vie
	  vaisseau.perdreUneVie();
	  int numVies = vaisseau.getNumVies();
	  std::string numViesString = std::to_string(numVies);
	  ui->label_2->setText(QString::fromStdString(numViesString));

    }
    if (ennemiFrappe == false) {
	it++;
    }
  }
}

void render_area::keyPressEvent(QKeyEvent *event)
{
  //std::cout<<"keyPressEvent appelle"<<std::endl;
  vec2 vitesse = vaisseau.getSpeed();

  // stop movement if game is over
  if(isGameOver == false){
      //mouvement horizontal
      if(event->key() == Qt::Key_Left) {
         // std::cout<<"left"<<std::endl;
    	vaisseau.setSpeed(-VITESSE_VAISSEAU, vitesse.y);
      }else if(event->key() == Qt::Key_Right) {
          //std::cout<<"right"<<std::endl;
    	vaisseau.setSpeed(VITESSE_VAISSEAU, vitesse.y);
      }
      // mouvement vertical
      if(event->key() == Qt::Key_Down) {
          //std::cout<<"down"<<std::endl;
          vaisseau.setSpeed(vitesse.x, VITESSE_VAISSEAU);
      }else if(event->key() == Qt::Key_Up) {
          //std::cout<<"up"<<std::endl;
    	vaisseau.setSpeed(vitesse.x, -VITESSE_VAISSEAU);
      }
      //tire
      if(event->key() == Qt::Key_Space) {
          //std::cout<<"space"<<std::endl;
          if(onPeutTirer == true){
              vec2 pos = vaisseau.getPosition();
              Tire* tire=new Tire(pos.x + TAILLE_VAISSEAU_X - 30, pos.y + TAILLE_VAISSEAU_Y/2 - 12);
              tires.push_back(tire);
              balleTimer.start(500); // a chaque 0.5sec
              onPeutTirer = false;
          }
      }

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

    //check for death
    if ( vaisseau.getNumVies() == 0){
      //debug
      //std::cout << "\n\n GAME OVER \n\n\n";
      isGameOver = true;
    }
}

void render_area::enable_shot()
{
    //called periodically (every 1s apres)
    onPeutTirer = true;
}

void render_area::spawn_ennemi()
{
    //called periodically (every 5s)
    spawn_counter ++;
    //isGameStarted = true;
    std::cout<<"is game started? "<<isGameStarted<<"\n";
    if(isGameStarted){
      Ennemi* nouveauEnnemi = new Ennemi();
      ennemis.push_back(nouveauEnnemi);

      //debug
      //std::cout<<"spawn ennemi!! \nnum ennemis :"<< ennemis.size() <<std::endl;
      //std::cout<<"num tires :"<< tires.size() <<std::endl;


      std::vector<Ennemi*>::iterator it;
      for (it = ennemis.begin(); it != ennemis.end(); )
  	  {
        Ennemi* ennemi = *it;
        vec2 pos = ennemi->getPosition();
        // ennemis qui ont passe l'ecran
        if(pos.x <= -100){
          //destroy the object
          delete ennemi;
          it = ennemis.erase(it);
          //increment counter
          num_ennemis_echapes += 1;
	        std::string numEnnemisEchapesString = std::to_string(num_ennemis_echapes);
	        ui->label_6->setText(QString::fromStdString(numEnnemisEchapesString));
        }else{
          it++;
        }
      }


      int index = 0;
      std::vector<Tire*>::iterator itTire;
      for (itTire = tires.begin(); itTire != tires.end(); )
  	  {
        Tire* tire = *itTire;
        vec2 pos = tire->getPosition();
        // tires qui ont passe l'ecran
        if(pos.x >= WINDOW_WIDTH + 200){
	        //debug
          //std::cout<<"TIRE LOIN!! \nnum tires :"<< tires.size() <<std::endl;
          //std::cout<<"tire position : "<< tire->getPosition() <<std::endl;
          //destroy the object
          delete tire;
          itTire = tires.erase(itTire);
        }else{
          itTire++;
          index++;
        }
      }
    }else{
      // le jeu n'a pas commence encore
      std::cout << "le jeu n'a pas commence encore" << '\n';
    }
}
