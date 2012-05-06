#ifndef QSCREENSHOTTER_H
#define QSCREENSHOTTER_H

#include <QtGui>

class ScreenShotter
{
public:
    enum ShootMode{Fullscreen, MouseSelection};
    ScreenShotter();
    void takeShot(ShootMode mode);
    bool hasScreenshot();
    const QPixmap* getScreenshot();
    void deleteScreenshot();
    void playSound();

private:
    void shootFullScreen();
    void shootMouseSelection();
    QPixmap *_screenshot;
};

#endif // QSCREENSHOTTER_H
