#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "BaseUserInfo.h"
#include "CarInsurance.h"
#include "HomeInsurance.h"
#include "LifeInsurance.h"
#include <vector>
using std::vector;

class Customer: public BaseUserInfo
{
public:
    Customer();
    Customer(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString em, QString pwd);
    Customer(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString em, QString pwd, int cus_id, QString ctz, QString mname, QString phone, int social);

private:
    int customerid;
    QString citizenship;
    QString middlename; //first name and last name variables are in BaseUserInfo(inherited)
    QString phonenumber;
    int socialsecuritynumber;

public:
    //list for insurances; contains the information for any policies had
    QList<Insurance*>insuranceList;

    //points to the next customer node on the linked list
    Customer* next;

public:
    //setters
    void set_customerid(int id);
    void set_citizenship(QString ctz);
    void set_middlename(QString name);
    void set_phonenumber(QString num);
    void set_socialsecuritynumber(int num);


    //getters
    int get_customerid();
    QString get_citizenship();
    QString get_middlename();
    QString get_phonenumber();
    int get_socialsecuritynumber();


};

#endif // CUSTOMER_H
