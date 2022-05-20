#include "InsuranceProgram.h"
#include <QApplication>

bool loggedIn = false; //flag to check if a user is logged in
Database* globaldb; //holds the database object

Customer * head, temp1, temp2;
//head - the front of the linked list
//temp1 - to loop throught the customers
//temp2 - to create a new customer

BaseUserInfo * loggedInUser; //holds the values of the logged in user

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InsuranceProgram * ip2 = new InsuranceProgram;
    ip2->execute();

    return a.exec();
}
