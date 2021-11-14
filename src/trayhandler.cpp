#include "include/trayhandler.h"
#include <QMenu>
#include <QGuiApplication>
#include <QMessageBox>
#include <QScreen>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QActionGroup>
#include <QAction>
#include <QLabel>
#include <QTimer>

TrayHandler::TrayHandler(QObject *parent) : QObject(parent)
{
    QFont font = QApplication::font();
    font.setPixelSize(48);

    d_screenshotPreview = new QLabel("Screenshot\nMonitor");
    d_displayPreview = new QLabel("Display\nMonitor");
    d_screenshotPreview->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    d_displayPreview->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    d_screenshotPreview->setStyleSheet("background-color: rgb(17, 17, 17); color: white");
    d_displayPreview->setStyleSheet("background-color: rgb(17, 17, 17); color: white");
    d_screenshotPreview->setAlignment(Qt::AlignCenter);
    d_displayPreview->setAlignment(Qt::AlignCenter);
    d_screenshotPreview->setFont(font);
    d_displayPreview->setFont(font);

    d_tray = new QSystemTrayIcon(QIcon(":/icon.ico"), this);
    d_tray->setToolTip("Quick screenshot tool with insta-display");
    QMenu *trayMenu = new QMenu;


    //trayMenu->addAction("Set hotkey", this, [this](){ emit setHotkeyClicked(); });

    //trayMenu->addSeparator();

    d_screenshotMonitorMenu = new QMenu("Screenshot Monitor");
    d_displayMonitorMenu = new QMenu("Display Monitor");
    d_screenshotMonitorGroup = new QActionGroup(d_tray);
    d_displayMonitorGroup = new QActionGroup(d_tray);
    d_screenshotMonitorGroup->setExclusive(true);
    d_displayMonitorGroup->setExclusive(true);

    trayMenu->addMenu(updateMonitors(d_screenshotMonitorMenu, d_screenshotMonitorGroup, 0));
    trayMenu->addMenu(updateMonitors(d_displayMonitorMenu, d_displayMonitorGroup, 1));
    d_previewMonitors = trayMenu->addAction("Preview Monitors", this, SLOT(previewMonitorsClicked()));

    trayMenu->addSeparator();

    trayMenu->addAction("Exit", this, SLOT(exitClicked()));


    d_tray->setContextMenu(trayMenu);
    d_tray->show();
}

TrayHandler::~TrayHandler()
{
    delete d_tray;
    delete d_screenshotPreview;
    delete d_displayPreview;
}

void TrayHandler::previewMonitorsClicked()
{
    QList<QScreen *> const &screens = QGuiApplication::screens();

    QAction *ssChecked = d_screenshotMonitorGroup->checkedAction();
    QAction *dpChecked = d_displayMonitorGroup->checkedAction();

    for(QScreen *screen : screens)
    {
        QString const &name = screen->name();
        QRect const &geometry = screen->geometry();
        if(name == ssChecked->text())
        {
            d_screenshotPreview->setGeometry(screen->geometry().topLeft().x() + 50, geometry.bottomLeft().y() - 300 - 50, 300, 300);
            d_screenshotPreview->setScreen(screen);
            d_screenshotPreview->show();
        } else if(name == dpChecked->text())
        {
            d_displayPreview->setGeometry(screen->geometry().topLeft().x() + 50, geometry.bottomLeft().y() - 300 - 50, 300, 300);
            d_displayPreview->setScreen(screen);
            d_displayPreview->show();
        }
    }

    QTimer::singleShot(3000, this, SLOT(hidePreviews()));
}

void TrayHandler::hidePreviews()
{
    d_screenshotPreview->hide();
    d_displayPreview->hide();
}

QMenu* TrayHandler::updateMonitors(QMenu *menu, QActionGroup *group, unsigned int defaultSelect)
{
    QList<QScreen *> const &screens = QGuiApplication::screens();

    if(screens.length() < 2)
    {
        QMessageBox box(QMessageBox::Icon::Critical, "Not enough monitors",
                        "There aren't enough monitors connected to your computer right now. This program requires at least 2 to function correctly.",
                        QMessageBox::Close);

        box.exec();
        QApplication::quit();
    }

    menu->clear();

    for(unsigned int i = 0; i < screens.length(); i++)
    {
        QAction *action = new QAction(screens[i]->name());
        action->setCheckable(true);
        if(i == defaultSelect) action->setChecked(true);

        if(group != nullptr) group->addAction(action);
        menu->addAction(action);
    }

    return menu;
}

QScreen *TrayHandler::screenshotScreen()
{
    QString name = d_screenshotMonitorGroup->checkedAction()->text();
    for(auto screen : QGuiApplication::screens())
    {
        if(name == screen->name()) return screen;
    }

    return nullptr;
}

QScreen *TrayHandler::displayScreen()
{
    QString name = d_displayMonitorGroup->checkedAction()->text();
    for(auto screen : QGuiApplication::screens())
    {
        if(name == screen->name()) return screen;
    }

    return nullptr;
}


void TrayHandler::exitClicked()
{
    QApplication::exit();
}
