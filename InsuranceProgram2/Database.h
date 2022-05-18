#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QList>
#include "Customer.h"
#include "Administrator.h"
#include "Desk.h"

class Database
{
public:
    Database();

    QSqlDatabase db;

    QSqlDatabase get_databaseStatus();

    //returns an object on the heap of a certain baseuser type
    BaseUserInfo* loginUser(QString uname, QString pwd);
};

#endif // DATABASE_H
