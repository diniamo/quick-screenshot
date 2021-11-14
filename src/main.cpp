#include "include/trayhandler.h"
#include "include/hotkeyhandler.h"

#include <QApplication>

HotkeyHandler *g_hh = nullptr;

void dispatch_proc(uiohook_event * const event)
{
    g_hh->eventDispatch(event);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    TrayHandler th;
    HotkeyHandler hh(&th);
    g_hh = &hh;

    hook_set_dispatch_proc(&dispatch_proc);
    hook_run();

    return a.exec();
}
