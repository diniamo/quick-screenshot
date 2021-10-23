#include "include/imgdisplay.h"
#include "include/trayhandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImgDisplay w;
    TrayHandler th(w);

    return a.exec();
}
