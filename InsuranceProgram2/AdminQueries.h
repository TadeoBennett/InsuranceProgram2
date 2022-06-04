#ifndef ADMINQUERIES_H
#define ADMINQUERIES_H

#include "Customer.h"
#include "Administrator.h"
#include "Desk.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

class AdminQueries
{
public:
    AdminQueries();

    //returns true if a user was updated
    bool updateUser(int userid, int userlevelid, QString username, QString firstname, QString lastname, int age, QString email, int status);

    //returns true if a desk user was successfully added to the database
    bool addDeskUser(QString uname, QString fname, QString lname, int a, QString em, QString pwd);

    //returns true if a user was deleted
    bool deleteUser(int userid);

    //return a model of the list of employees and admins in the database
    QSqlQueryModel* getEmployeeListModel();



    void increaseCarInsuranceRevenue(float amount);
    void increaseHomeInsuranceRevenue(float amount);
    void increaseLifeInsuranceRevenue(float amount);

    //reports
    void revenueReport();
    void debtCustomersReport();
    void insuranceDistributionReport();
    void employeeNumbersReport();

};

#endif // ADMINQUERIES_H
