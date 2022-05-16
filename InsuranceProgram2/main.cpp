#include "login.h"

#include <QApplication>

bool loggedIn = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    return a.exec();
}
