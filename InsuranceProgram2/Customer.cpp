#include "Customer.h"

Customer::Customer()
{

}

Customer::Customer(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd):BaseUserInfo(user_id, userlevel_id, uname, fname, lname, a, pwd){
    //this is an inherited constructor
}

Customer::Customer(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd, int cus_id, QString ctz, QString mname, QString phone, int social):BaseUserInfo(user_id, userlevel_id, uname, fname, lname, a, pwd){
    //creating default entries in the insuranceList
    insuranceList.append(new CarInsurance());
    insuranceList.append(new HomeInsurance());
    insuranceList.append(new LifeInsurance());

    customerid = cus_id;
    citizenship = ctz;
    middlename = mname;
    phonenumber = phone;
    socialsecuritynumber = social;
    //this constructor adds customer specific information, as well as initialize the base user information for this customer
}

void Customer::set_customerid(int id)
{ customerid = id; }

void Customer::set_citizenship(QString ctz)
{ citizenship = ctz; }

void Customer::set_middlename(QString name)
{ middlename = name; }

void Customer::set_phonenumber(QString num)
{ phonenumber = num; }

void Customer::set_socialsecuritynumber(int num)
{ socialsecuritynumber = num; }

//-----------------------------------------------------------------------------------

int Customer::get_customerid()
{ return customerid; }

QString Customer::get_citizenship()
{ return citizenship; }

QString Customer::get_middlename()
{ return middlename; }

QString Customer::get_phonenumber()
{ return phonenumber; }

int Customer::get_socialsecuritynumber()
{ return socialsecuritynumber; }
