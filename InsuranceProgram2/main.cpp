#include "login.h"

#include <QApplication>
#include <QIcon>

bool loggedIn = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.setWindowIcon(QIcon(":/images/shield.ico"));
    w.show();
    return a.exec();
}
