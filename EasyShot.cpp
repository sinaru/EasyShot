#include <QtGui>
#include <map>
#include <exception>
#include <iostream>

#include "EasyShot.h"
#include "ZException.h"
#include "PreferenceDialog.h"
#include "MainWindow.h"
#include "AppSettings.h"

EasyShot::EasyShot(QWidget *parent) :
    QWidget(parent)
{
    _initialized = false;
}

void EasyShot::init(bool force)
{
    AppSettings settings;

    if(_initialized && !force)
    {
        return;
    }


    _mainWindow = new MainWindow(this);
    bool startMinimized = settings.getSetting(StartMinimized, true).toBool();
    if(startMinimized)
        _mainWindow->hide();
    else
        _mainWindow->show();
    createTrayIcon();

    _screenshooter = new ScreenShotter();

    _initialized = true;
}

void EasyShot::createTrayIcon()
{
    //take shot menu action for the tray icon
    QAction *takeShot = new QAction(tr("Take Shot"), this);
    connect(takeShot,SIGNAL(triggered()),this,SLOT(takeScreenshot()));

    //quite action
    QAction *quitAction = new QAction(tr("&Quit"),this);
    connect(quitAction,SIGNAL(triggered()),qApp, SLOT(quit()));

    //Tray icon menu
    QMenu* menu = new QMenu(this);
    menu->addAction(takeShot);
    menu->addAction(quitAction);    

    //tray icon
    QSystemTrayIcon *icon = new QSystemTrayIcon(_mainWindow);
    icon->setIcon(QIcon(":resources/icons/app_icon.png"));
    icon->setContextMenu(menu);
    icon->show();

    connect(icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            _mainWindow,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void EasyShot::takeScreenshot()
{

    AppSettings settings;
    ScreenShotter::ShootMode mode =
            (ScreenShotter::ShootMode) (settings.getSetting(ShootingMode).toInt());

    bool mainWindowVisible = _mainWindow->isVisible();
    if(mainWindowVisible)
        _mainWindow->hide();

    sleep(1);// Wait till window closes
    _screenshooter->takeShot(mode);

    if(!_screenshooter->hasScreenshot())
      {
          if(mainWindowVisible)
              _mainWindow->show();
          return;
      }

    //Have main window visible before save file dalog. Otherwise the program closes when save dialog is closed.
    _mainWindow->show();

    QString format = "png";

    QString initialPath = tr("/untitled.")+ format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                    .arg(format.toUpper())
                                                    .arg(format));
    if (!fileName.isEmpty())
    {
        bool saved = _screenshooter->getScreenshot()->save(fileName, format.toAscii());

        if(!saved)
        {
            std::cout << "Unable to save screenshot at: " << fileName.toStdString() <<std::endl;
        }
    }

    //If main window was hidden before the screenshot is called, hide the main window again
    if(!mainWindowVisible)
        _mainWindow->hide();
}


