#include "include/trayhandler.h"
#include "include/hotkeyhandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    TrayHandler th;
    HotkeyHandler hh(&th);

    return a.exec();
}
