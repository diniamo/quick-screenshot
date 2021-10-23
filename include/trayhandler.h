#ifndef TRAYHANDLER_H
#define TRAYHANDLER_H

#include "imgdisplay.h"
#include <QObject>
#include <QSystemTrayIcon>

class TrayHandler : public QObject
{
    Q_OBJECT
public:
    TrayHandler(ImgDisplay &, QObject *parent = nullptr);
    ~TrayHandler();

private:
    static QMenu* updateMonitors(QMenu *);

    QSystemTrayIcon *d_tray;

private slots:
    void exitClicked();
};

#endif // TRAYHANDLER_H
