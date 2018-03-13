// CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
// CARNEIRO ESTEVES, Sophie
// FOLETTO PIMENTA, Pedro
// TP 2


#include <QApplication>
#include "window.hpp"


int main(int argc,char *argv[])
{
  QApplication app(argc,argv);
  window win;
  win.show();
  return app.exec();
}
