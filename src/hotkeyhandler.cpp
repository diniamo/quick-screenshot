#include "include/hotkeyhandler.h"
#include "include/trayhandler.h"
#include "include/hotkeydialog.h"

#include <QHotkey>
#include <QLabel>
#include <QScreen>
#include <QPixmap>

HotkeyHandler::HotkeyHandler(TrayHandler *th, QObject *parent) : QObject(parent),
    d_trayHandler(th)
{
    d_hotkeyDialog = new HotkeyDialog();

    d_hotkey = new QHotkey(d_hotkeyDialog->newSequence(), true, this);
    qDebug() << "Is registered:" << d_hotkey->isRegistered();
    connect(d_hotkey, &QHotkey::activated, this, &HotkeyHandler::printCaught);

    connect(d_trayHandler, &TrayHandler::setHotkeyClicked, this, &HotkeyHandler::setHotkeyClicked);

    d_displayLabel = new QLabel();
    d_displayLabel->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

HotkeyHandler::~HotkeyHandler()
{
    delete d_hotkey;
    delete d_hotkeyDialog;
}

void HotkeyHandler::printCaught()
{
    qDebug() << "Hotkey caught";

    QScreen *screenshotScreen = d_trayHandler->screenshotScreen();
    QRect const &ssGeom = screenshotScreen->geometry();
    QPixmap screenshot = screenshotScreen->grabWindow(0, ssGeom.x(), ssGeom.y(), ssGeom.width(), ssGeom.height());

    QScreen *displayScreen = d_trayHandler->displayScreen();

    d_displayLabel->setGeometry(displayScreen->geometry());
    d_displayLabel->setPixmap(screenshot);
    d_displayLabel->showFullScreen();
}

void HotkeyHandler::setHotkeyClicked()
{
    d_hotkey->setRegistered(false);
    d_hotkey->setShortcut(d_hotkeyDialog->newSequence(), true);
}
