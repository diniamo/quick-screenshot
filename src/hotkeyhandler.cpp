#include "include/hotkeyhandler.h"
#include "include/trayhandler.h"
#include "include/hotkeydialog.h"

#include <QLabel>
#include <QScreen>
#include <QPixmap>

HotkeyHandler::HotkeyHandler(TrayHandler *th, QObject *parent) : QObject(parent),
    d_trayHandler(th)
{
    d_hotkeyDialog = new HotkeyDialog();

    d_displayLabel = new QLabel();
    d_displayLabel->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

HotkeyHandler::~HotkeyHandler()
{
    delete d_hotkeyDialog;
    delete d_displayLabel;
}

void HotkeyHandler::eventDispatch(uiohook_event * const event)

{
    if(event->type == EVENT_KEY_PRESSED && event->data.keyboard.keycode == VC_PRINTSCREEN)
    {
        QScreen *screenshotScreen = d_trayHandler->screenshotScreen();
        QRect const &ssGeom = screenshotScreen->geometry();
        QPixmap screenshot = screenshotScreen->grabWindow(0, ssGeom.x(), ssGeom.y(), ssGeom.width(), ssGeom.height());

        QScreen *displayScreen = d_trayHandler->displayScreen();

        d_displayLabel->setGeometry(displayScreen->geometry());
        d_displayLabel->setPixmap(screenshot);
        d_displayLabel->showFullScreen();
    }
}

void HotkeyHandler::setHotkeyClicked()
{
    //d_hotkey->setRegistered(false);
    //d_hotkey->setShortcut(d_hotkeyDialog->newSequence(), true);
}
