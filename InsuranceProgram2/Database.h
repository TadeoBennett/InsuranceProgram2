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

    QSqlDatabase get_databaseStatus();

    //returns true if the user has been logged in
    bool loginUser(QString em, QString pwd);

    //returns true if the email provided exists
    bool checkEmail(QString em);

    //returns true if a desk user was successfully added to the database
    bool addDeskUser(QString uname, QString fname, QString lname, int a, QString em, QString pwd);

};

#endif // DATABASE_H