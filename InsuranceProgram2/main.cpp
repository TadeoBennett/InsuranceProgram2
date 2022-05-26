#include "InsuranceProgram.h"
#include "PolicyDetailsView.h"
#include <QApplication>

bool loggedIn = false; //flag to check if a user is logged in
Database* globaldb; //holds the database object

BaseUserInfo * loggedInUser; //holds the values of the logged in user

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InsuranceProgram * ip2 = new InsuranceProgram;
    ip2->execute();
//    PolicyDetailsView * pdv = new PolicyDetailsView();
//    pdv->show();


    return a.exec();
}
