#ifndef HOTKEYHANDLER_H
#define HOTKEYHANDLER_H

#include <QObject>
#include <uiohook.h>

class TrayHandler;
class HotkeyDialog;
class QLabel;

class HotkeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit HotkeyHandler(TrayHandler *, QObject * = nullptr);
    ~HotkeyHandler();

    void eventDispatch(uiohook_event * const);

private:
    TrayHandler *d_trayHandler;
    HotkeyDialog *d_hotkeyDialog;

    QLabel *d_displayLabel;

private slots:
    void setHotkeyClicked();

};

#endif // HOTKEYHANDLER_H
