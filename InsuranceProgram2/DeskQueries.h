#ifndef DESKQUERIES_H
#define DESKQUERIES_H

#include "Database.h"


class DeskQueries: public Database
{
public:
    DeskQueries();

    void addCustomer(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd, int cus_id, QString ctz, QString mname, QString phone, int social);
    void addCarInsurance(QString mk, QString ml, int license, QString vehicleid, int y, int miles, QString features, QString devices, /**/int id, float mpayment, int mpaid, int mlimit);
    void addHomeInsurance(QString add, QString mar_status, QString home_improv, bool pet, bool entr, QString p_athome, /**/int id, float mpayment, int mpaid, int mlimit);
    void addLifeInsurance(float sal, QString occ, QString ben, bool fel, bool mis_charges, bool drug, QString hobbies, QString h, QString w, QString physician, QString diagnoses, /**/int id, float mpayment, int mpaid, int mlimit);

    void deleteCustomer(int user_id);
    void deleteCarInsurance(int user_id);
    void deleteHomeInsurance(int user_id);
    void deleteLifeInsurance(int user_id);

    void updateCustomer(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd, int cus_id, QString ctz, QString mname, QString phone, int social);
    void updateCarInsurance(int id, QString mk, QString ml, int license, QString vehicleid, int y, int miles, QString features, QString devices);
    void updateHomeInsurance(int id, QString add, QString mar_status, QString home_improv, bool pet, bool entr, QString p_athome);
    void updateLifeInsurance(int id, float sal, QString occ, QString ben, bool fel, bool mis_charges, bool drug, QString hobbies, QString h, QString w, QString physician, QString diagnoses);

    void renewCarInsurance(int id, float mpayment, int mpaid, int mlimit);
    void renewHomeInsurance(int id, float mpayment, int mpaid, int mlimit);
    void renewLifeInsurance(int id, float mpayment, int mpaid, int mlimit);

    //these QLists do not need to be saved on the heap
    QList<CarInsurance> get_allCarInsurances();
    QList<HomeInsurance> get_allHomeInsurances();
    QList<LifeInsurance> get_allLifeInsurances();

//
//  AdminQueries contains a method to return all customers
//

};

#endif // DESKQUERIES_H
