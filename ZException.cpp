#include <QDateTime>
#include <iostream>
using namespace std;

#include "ZException.h"

ZException::ZException(string message)
{
    _message = message;

    cout << "["<<QDateTime::currentDateTime().toString(Qt::TextDate).toUtf8().constData() <<
            "] ZException: "<< message <<endl;
}

string ZException::reason()
{
    return _message;
}

void ZException::echo()
{
    std::cout << _message << endl;
}
