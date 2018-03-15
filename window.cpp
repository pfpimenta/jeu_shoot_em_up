// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#include "window.hpp"

#include "render_area.hpp"
#include "ui_mainwindow.h"

#include <iostream>

window::window(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow),render(new render_area)
{
    ui->setupUi(this);
    ui->layout_scene->addWidget(render);
    render->setFocus();

    //Connection with signals
    connect(ui->quit,SIGNAL(clicked()),this,SLOT(action_quit()));
    connect(ui->start,SIGNAL(clicked()),this,SLOT(action_start()));
}


window::~window()
{}

void window::action_quit()
{
    close();
}

void window::action_start()
{
    //render->change_draw_circle_state();
}


