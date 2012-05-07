#include <QtGui>
#include <map>
#include <exception>
#include <iostream>

#include "EasyShot.h"
#include "ZException.h"
#include "PreferenceDialog.h"
#include "MainWindow.h"
#include "AppSettings.h"

/**
  use phonon plugin to play the shutter sound. Also referenced in the qt project file
  */
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

EasyShot::EasyShot(QWidget *parent) :
    QWidget(parent)
{
    _initialized = false;
}

AppSettings* EasyShot::settings()
{
    return _settings;
}

void EasyShot::init(bool force)
{
    if(_initialized && !force)
    {
        qDebug("EasyShot::init function already called.");
        return;
    }

    _settings = new AppSettings();

    _mainWindow = new MainWindow(this);
    bool startMinimized = _settings->getSetting(StartMinimized, false).toBool();
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
    ScreenShotter::ShootMode mode =
            (ScreenShotter::ShootMode) (_settings->getSetting(ShootingMode).toInt());

    bool mainWindowVisible = _mainWindow->isVisible();
    if(mainWindowVisible)
        _mainWindow->hide();

   usleep(1000000);// Wait till window closes
    _screenshooter->takeShot(mode);

    if(!_screenshooter->hasScreenshot())
      {
          if(mainWindowVisible)
              _mainWindow->show();
          return;
      }

        if(_settings->getSetting(PlaySound,false).toBool())
            playSound();


    //Have main window visible before save file dalog. Otherwise the program closes when save dialog is closed.
    _mainWindow->show();

    QString format = "png";
    QString lastSavedLocation = _settings->getSetting(LastSavedLocation, "").toString();

    QString initialPath = lastSavedLocation+ "/untitled - "+QDateTime::currentDateTime().toString("dd-MM-yyyy hh-mm-ss")+ "."+ format;

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
            return;
        }

        QFileInfo path(fileName);
        _settings->setSetting(LastSavedLocation, path.path());

    }

    //If main window was hidden before the screenshot is called, hide the main window again
    if(!mainWindowVisible)
        _mainWindow->hide();
}

void EasyShot::playSound()
{
    if(!QFile::exists("sounds/camerashutter.wav"))
        throw new ZException("Unable to find 'sounds/camerashutter.wav' file.");

    Phonon::MediaObject *music =
            Phonon::createPlayer(Phonon::MusicCategory,
                                 Phonon::MediaSource("sounds/camerashutter.wav"));
    music->play();
    qDebug("Music played from EasyShot::playSound() function");
}

EasyShot* EasyShot::app()
{
    static EasyShot *app = new EasyShot();
    return app;
}


