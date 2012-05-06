#ifndef ZEXCEPTION_H
#define ZEXCEPTION_H

#include <iostream>
using namespace std;

class ZException
{
public:
    ZException(string message = "");
    string reason();
    void echo();
 private:
    string _message;
};

#endif // ZEXCEPTION_H
