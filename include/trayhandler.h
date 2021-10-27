#ifndef TRAYHANDLER_H
#define TRAYHANDLER_H

#include "imgdisplay.h"
#include <QObject>

class QSystemTrayIcon;
class QActionGroup;
class QMenu;
class QAction;
class QLabel;

class TrayHandler : public QObject
{
    Q_OBJECT
public:
    TrayHandler(ImgDisplay &, QObject *parent = nullptr);
    ~TrayHandler();

private:
    static inline QMenu* updateMonitors(QMenu *, QActionGroup * = nullptr, unsigned int = 0);

    QSystemTrayIcon *d_tray;

    QMenu *d_screenshotMonitorMenu;
    QMenu *d_displayMonitorMenu;
    QActionGroup *d_screenshotMonitorGroup;
    QActionGroup *d_displayMonitorGroup;
    QAction *d_previewMonitors;


    QLabel *d_screenshotPreview;
    QLabel *d_displayPreview;

private slots:
    void previewMonitorsClicked();
    void hidePreviews();

    void exitClicked();
};

#endif // TRAYHANDLER_H
