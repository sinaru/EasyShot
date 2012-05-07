#include "ScreenShotter.h"
#include "RegionSelectorDialog.h"
#include "ZException.h"

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
    {
        _screenshot = new QPixmap(dialog.getSelection());
    }

}

bool ScreenShotter::hasScreenshot()
{
    return (_screenshot != NULL);
}

const QPixmap* ScreenShotter::getScreenshot()
{
    return _screenshot;
}




