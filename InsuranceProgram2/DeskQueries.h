#ifndef DESKQUERIES_H
#define DESKQUERIES_H

#include "Customer.h"
#include "Administrator.h"
#include "Desk.h"
#include <QSqlQueryModel>
#include <QSqlQuery>

class DeskQueries
{
public:
    DeskQueries();

    //return a model of the list of customers and admins in the database
    QSqlQueryModel* getCustomerListModel();

    //return a model of customers with matching name text
    QSqlQueryModel *getCustomerListModelBySearch(QString name);

    //returns the customer id if the customer was added; returns 0 if it fails
    int addCustomer(QString uname, QString fname, QString lname, int a, QString pwd, int cus_id/*assigned post customer creation*/, QString ctz, QString mname, QString phone, int social, QString em, int stat);

    //returns a specfic int if a customer details was updated or a customer was removed
    int updateBasicCustomerDetails(int cus_id,  QString ctz, QString fname, QString mname , QString lname, int a, QString phone, int social, int cus_status, QString uname, QString em);

    //returns true if a customer was deleted
    bool deleteCustomer(int userid);

    //returns true if a customer was deleted from the user table
    bool deleteUserWithCustomerId(int cus_id);

    //returns the int of insurance id added; returns 0 if it fails
    int addCarInsurance(QString mk, QString ml, int license, QString vehicleid, int y, int miles, QString features, QString devices, int cus_id, float mpayment, int mpaid, int mlimit);
    int addHomeInsurance(QString add, QString mar_status, QString home_improv, int pet, int entr, QString p_athome, /**/int cus_id, float mpayment, int mpaid, int mlimit);
    int addLifeInsurance(float sal, QString occ, QString ben, int fel, int mis_charges, int drug, QString hobbies, QString h, QString w, QString physician, QString diagnoses, /**/int cus_id, float mpayment, int mpaid, int mlimit);

    //returns true if the insurance id was added to the customer record with the specified id
    bool combineCarInsuranceWithCustomer(int cus_id, int insuranceid);
    bool combineHomeInsuranceWithCustomer(int cus_id, int insuranceid);
    bool combineLifeInsuranceWithCustomer(int cus_id, int insuranceid);

    //returns true or an integer if the monthspaid or monthlypayment was read or updated
    double* get_policyDetails(int itype, int userid);
    bool renewInsurance(int id, int itype, int mpaid); //car,home,life



    void deleteCarInsurance(int insuranceid);
    void deleteHomeInsurance(int insuranceid);
    void deleteLifeInsurance(int insuranceid);

    void updateCustomer(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd, int cus_id, QString ctz, QString mname, QString phone, int social);
    void updateCarInsurance(int id, QString mk, QString ml, int license, QString vehicleid, int y, int miles, QString features, QString devices);
    void updateHomeInsurance(int id, QString add, QString mar_status, QString home_improv, bool pet, bool entr, QString p_athome);
    void updateLifeInsurance(int id, float sal, QString occ, QString ben, bool fel, bool mis_charges, bool drug, QString hobbies, QString h, QString w, QString physician, QString diagnoses);


    //these QLists do not need to be saved on the heap
    QList<CarInsurance> get_allCarInsurances();
    QList<HomeInsurance> get_allHomeInsurances();
    QList<LifeInsurance> get_allLifeInsurances();

};

#endif // DESKQUERIES_H
