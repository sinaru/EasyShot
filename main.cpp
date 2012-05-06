#include <QtGui/QApplication>
#include "ZException.h"
#include "EasyShot.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("SinaCodes");
    QCoreApplication::setApplicationName("EasyShot");
    EasyShot app;
    app.init();

    return a.exec();
}
