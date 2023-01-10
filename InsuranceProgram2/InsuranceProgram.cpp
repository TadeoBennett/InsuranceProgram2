//Tadeo Bennett
#include "InsuranceProgram.h"
#include <iostream>

extern bool loggedIn; //flag to check if a user is logged in
extern Database* globaldb; //holds the database object
extern BaseUserInfo * loggedInUser; //holds the values of the logged in user

InsuranceProgram::InsuranceProgram()
{
    //database connection attempt
//    db = new Database();
    globaldb = new Database();

}

void InsuranceProgram::execute()
{
    qDebug()<<"executing system instance";
    Login * w = new Login;
    w->setWindowIcon(QIcon(":/images/shield.ico"));
    w->show();
}
