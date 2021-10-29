#ifndef TRAYHANDLER_H
#define TRAYHANDLER_H

#include <QObject>

class QScreen;
class QSystemTrayIcon;
class QActionGroup;
class QMenu;
class QAction;
class QLabel;

class TrayHandler : public QObject
{
    Q_OBJECT
public:
    explicit TrayHandler(QObject * = nullptr);
    ~TrayHandler();

    QScreen *screenshotScreen();
    QScreen *displayScreen();

private:
    static QMenu* updateMonitors(QMenu *, QActionGroup * = nullptr, unsigned int = 0);

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

signals:
    void setHotkeyClicked();
};

#endif // TRAYHANDLER_H
