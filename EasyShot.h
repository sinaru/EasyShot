#ifndef EASYSHOT_H
#define EASYSHOT_H

#include <QtGui>
#include <QWidget>
#include <map>
#include "MainWindow.h"
#include "ScreenShotter.h"

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

signals:
    
public slots:
    void takeScreenshot();

private:
    void createTrayIcon();

    QSystemTrayIcon *_trayIcon;
    MainWindow *_mainWindow;
    ScreenShotter *_screenshooter;
    bool _initialized;
};

#endif // EASYSHOT_H
