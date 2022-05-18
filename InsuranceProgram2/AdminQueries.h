#ifndef ADMINQUERIES_H
#define ADMINQUERIES_H

#include "Database.h"

class AdminQueries: public Database
{
public:
    AdminQueries();

    void updateEmployee(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd);
    void addEmployee(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd);
    void deleteEmployee(int user_id);
    void increaseCarInsuranceRevenue(float amount);
    void increaseHomeInsuranceRevenue(float amount);
    void increaseLifeInsuranceRevenue(float amount);

    //these QLists do not need to be saved on the heap
    QList<Desk> get_allDeskEmployees();
    QList<Administrator> get_allAdministrators();
    QList<Customer> get_allCustomers();

    //reports
    void revenueReport();
    void debtCustomersReport();
    void insuranceDistributionReport();
    void employeeNumbersReport();

};

#endif // ADMINQUERIES_H
