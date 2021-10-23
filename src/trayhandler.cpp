#include "include/trayhandler.h"
#include <QMenu>
#include <QGuiApplication>
#include <QScreen>
#include <QApplication>

TrayHandler::TrayHandler(ImgDisplay &imd, QObject *parent)
{
    QMenu *trayMenu = new QMenu();

    QMenu *screenshotMonitorMenu = new QMenu();
    screenshotMonitorMenu->setTitle("Screenshot Monitor");
    QMenu *displayMonitorMenu = new QMenu();
    displayMonitorMenu->setTitle("Display Monitor");

    trayMenu->addMenu(updateMonitors(screenshotMonitorMenu));
    trayMenu->addMenu(updateMonitors(displayMonitorMenu));
    trayMenu->addAction("Preview Monitors");

    trayMenu->addSeparator();

    trayMenu->addAction("Exit", this, SLOT(exitClicked()));

    d_tray = new QSystemTrayIcon(QIcon(":/icon.ico"));
    d_tray->setToolTip("Quick screenshot tool with insta-display");
    d_tray->setContextMenu(trayMenu);
    d_tray->show();
}

TrayHandler::~TrayHandler()
{
    delete d_tray;
}

QMenu* TrayHandler::updateMonitors(QMenu *menu)
{
    auto screens = QGuiApplication::screens();
    menu->clear();

    for(QScreen *screen : screens)
    {
        menu->addAction(screen->name());
    }

    return menu;
}

void TrayHandler::exitClicked()
{
    QApplication::exit();
}
