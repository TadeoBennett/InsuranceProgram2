#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QList>
#include "CustomerQueries.h"
#include "DeskQueries.h"
#include "AdminQueries.h"

class Database: public CustomerQueries, public DeskQueries, public AdminQueries
{
public:
    Database();

    QSqlDatabase db;

    bool get_databaseStatus();

    //returns true if the user has been logged in
    bool loginUser(QString em, QString pwd);

    //returns true if the email provided exists
    bool checkEmail(QString em);

    //returns true if a desk user was successfully added to the database
    bool addDeskUser(QString uname, QString fname, QString lname, int a, QString em, QString pwd);

    //returns true the password for a current user has been changed
    bool changePassword(int userId, QString password);

    //return a model of the list of employees and admins in the database
    QSqlQueryModel* getEmployeeListModel();

    //return a model of the list of customers and admins in the database
    QSqlQueryModel* getCustomerListModel();

    //returns true if a user was deleted
    bool deleteUser(int userid);

    //returns true if a user was updated
    bool updateUser(int userid, int userlevelid, QString username, QString firstname, QString lastname, int age, QString email, int status);

};

#endif // DATABASE_H
