# CPE - 4ETI - Maj.Image - Programmation en C++ - 09/03/2018
# CARNEIRO ESTEVES, Sophie
# FOLETTO PIMENTA, Pedro
# TP 2


#base directory of Qt files
QT_DIR_BASE=/usr/include/qt4

#specific include directories for Qt
QT_INCLUDE=-I${QT_DIR_BASE} -I${QT_DIR_BASE}/QtCore -I${QT_DIR_BASE}/QtGui

#specific lib dependecies for Qt
QT_DEPENDENCIES=-lQtCore -lQtGui

#Qt MOC
MOC=moc-qt4

#QT UIC
UIC=uic-qt4

#Compilation flags
CXXFLAGS= -g -O2 -Wall -Wextra -std=c++11 ${QT_INCLUDE}
#Linking flags
LDFLAGS=-pthread ${QT_DEPENDENCIES}
#Compiler
CXX=g++


main: main.o window.o moc_window.o render_area.o moc_render_area.o vec2.o circle.o Objet_bougeant.o Navette.o Vaisseau.o
	${CXX} $^ -o $@ ${LDFLAGS}

main.o: main.cpp window.hpp
window.o: window.cpp window.hpp ui_mainwindow.h
moc_window.o: moc_window.cpp window.hpp
moc_window.cpp: window.hpp
	${MOC} $< -o $@ ${QT_INCLUDE}

render_area.o: render_area.cpp render_area.hpp circle.hpp vec2.hpp
moc_render_area.o: moc_render_area.cpp render_area.hpp
moc_render_area.cpp: render_area.hpp
	${MOC} $< -o $@ ${QT_INCLUDE}

vec2.o: vec2.cpp vec2.hpp
circle.o: circle.cpp circle.hpp vec2.hpp
Objet_bougeant.o: Objet_bougeant.cpp Objet_bougeant.hpp vec2.hpp
Navette.o: Navette.cpp Navette.hpp vec2.hpp
Vaisseau.o: Vaisseau.cpp Vaisseau.hpp vec2.hpp

ui_mainwindow.h: mainwindow.ui
	${UIC} $< -o $@

clean:
	rm -f *~ *.o moc_* ui_* main
