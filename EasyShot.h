#ifndef EASYSHOT_H
#define EASYSHOT_H

#include <QtGui>
#include <QWidget>
#include <map>
#include "MainWindow.h"
#include "ScreenShotter.h"
#include "AppSettings.h"

class QSystemTrayIcon;

enum ImageType
{
    PNG,
    JPG
};

class EasyShot : public QWidget
{
    Q_OBJECT   
public:
    explicit EasyShot(QWidget *parent = 0);
    void init(bool force = false);
    void playSound();
    static EasyShot* app();
    AppSettings* settings();

signals:
    
public slots:
    void takeScreenshot();

private:
    void createTrayIcon();

    QSystemTrayIcon *_trayIcon;
    MainWindow *_mainWindow;
    ScreenShotter *_screenshooter;
    AppSettings *_settings;
    bool _initialized;
};

#endif // EASYSHOT_H
