#ifndef HOTKEYHANDLER_H
#define HOTKEYHANDLER_H

#include <QObject>

class TrayHandler;
class HotkeyDialog;
class QHotkey;
class QLabel;

class HotkeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit HotkeyHandler(TrayHandler *, QObject * = nullptr);
    ~HotkeyHandler();

private:
    TrayHandler *d_trayHandler;
    HotkeyDialog *d_hotkeyDialog;

    QHotkey *d_hotkey;
    QLabel *d_displayLabel;

private slots:
    void printCaught();
    void setHotkeyClicked();

};

#endif // HOTKEYHANDLER_H
