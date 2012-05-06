#include <iostream>
using namespace std;

#include "ZException.h"

ZException::ZException(string message)
{
    _message = message;
}

string ZException::reason()
{
    return _message;
}

void ZException::echo()
{
    std::cout << _message << endl;
}
