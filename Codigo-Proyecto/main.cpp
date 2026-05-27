#include "mainwindow.h"
#include "juego.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    juego juego;;
    juego.show();
    return a.exec();
}
