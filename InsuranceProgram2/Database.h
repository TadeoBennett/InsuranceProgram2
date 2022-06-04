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

    //returns true the password for a current user has been changed
    bool changePassword(int userId, QString password);


};

#endif // DATABASE_H
