#include "HomeInsurance.h"

HomeInsurance::HomeInsurance()
{

}

HomeInsurance::HomeInsurance(int id, float mpayment, int mpaid, int mlimit):Insurance(id, mpayment, mpaid, mlimit){
    //this is an inherited constructor
}

HomeInsurance::HomeInsurance(QString add, QString mar_status, QString home_improv, bool pet, bool entr, QString p_athome, /**/ int id, float mpayment, int mpaid, int mlimit):Insurance(id, mpayment, mpaid, mlimit){
    address = add;
    maritalstatus = mar_status;
    homeimprovements = home_improv;
    petowner = pet;
    entrepreneur = entr;
    peopleathome = p_athome;
    //this constructor adds home insurance information, as well as initialize the base insurance information
}

void HomeInsurance::set_address(QString add)
{ address = add; }

void HomeInsurance::set_maritalstatus(QString mar_status)
{ maritalstatus = mar_status; }

void HomeInsurance::set_homeimprovements(QString home_improv)
{ homeimprovements = home_improv; }

void HomeInsurance::set_petowner(bool pet)
{ petowner = pet; }

void HomeInsurance::set_entrepreneur(bool entr)
{ entrepreneur = entr; }

void HomeInsurance::set_peopleathome(QString p_athome)
{ peopleathome = p_athome; }

//-----------------------------------------------------------------------------------

QString HomeInsurance::get_address()
{ return address; }

QString HomeInsurance::get_maritalstatus()
{ return maritalstatus; }

QString HomeInsurance::get_homeimprovements()
{ return homeimprovements; }

bool HomeInsurance::get_petowner()
{ return petowner; }

bool HomeInsurance::get_entrepreneur()
{ return entrepreneur; }

QString HomeInsurance::get_peopleathome()
{ return peopleathome; }


