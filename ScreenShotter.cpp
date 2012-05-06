#include "ScreenShotter.h"
#include "RegionSelectorDialog.h"
#include "ZException.h"
#include "AppSettings.h"
/**
  use phonon plugin to play the shutter sound. Also referenced in the qt project file
  */
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

ScreenShotter::ScreenShotter()
{
    _screenshot = NULL;
}

void ScreenShotter::takeShot(ShootMode mode)
{
    //Delete any available screenshot
    deleteScreenshot();

    if(mode == Fullscreen)
        shootFullScreen();
    else if(mode == MouseSelection)
        shootMouseSelection();
    else
        throw new ZException("Invalid ShootMode: "+mode);

    AppSettings settings;
    if(settings.getSetting(PlaySound,false).toBool())
        playSound();
}

void ScreenShotter::deleteScreenshot()
{
    if(hasScreenshot())
    {
        delete _screenshot;
        _screenshot = NULL;
    }
}

void ScreenShotter::shootFullScreen()
{
    _screenshot = new QPixmap(QPixmap::grabWindow(QApplication::desktop()->winId()));
}

void ScreenShotter::shootMouseSelection()
{
    RegionSelectDialog dialog;
    if(dialog.exec())
        _screenshot = new QPixmap(dialog.getSelection());

}

bool ScreenShotter::hasScreenshot()
{
    return (_screenshot != NULL);
}

const QPixmap* ScreenShotter::getScreenshot()
{
    return _screenshot;
}

void ScreenShotter::playSound()
{
    if(!QFile::exists("sounds/camerashutter.wav"))
        throw new ZException("Unable to find 'sounds/camerashutter.wav' file.");

    Phonon::MediaObject *music =
            Phonon::createPlayer(Phonon::MusicCategory,
                                 Phonon::MediaSource("sounds/camerashutter.wav"));
    music->play();
}


