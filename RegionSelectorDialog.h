
#ifndef REGIONSELECT_H
#define REGIONSELECT_H

#include <QDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPainter>
//#include <QDebug>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class RegionSelectDialog : public QDialog
{
    Q_OBJECT
public:
    RegionSelectDialog(QWidget *parent = 0);

    QPixmap getSelection();

protected:
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QRect selectRect;
    QSize sizeDesktop;

    QPoint selStartPoint;
    QPoint selEndPoint;

    bool palBackground;

    QPixmap desktopPixmapBkg;
    QPixmap desktopPixmapClr;


    void drawBackGround();
    void drawRectSelection(QPainter &painter);

};

#endif // REGIONSELECT_H
