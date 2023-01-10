//Tadeo Bennett
#include "LifeInsurance.h"

LifeInsurance::LifeInsurance()
{

}

LifeInsurance::LifeInsurance(int id, float mpayment, int mpaid, int mlimit):Insurance(id, mpayment, mpaid, mlimit){
    //this is an inherited constructor
}

LifeInsurance::LifeInsurance(float sal, QString occ, QString ben, bool fel, bool mis_charges, bool drug, QString hobbies, QString h, QString w, QString physician, QString diagnoses, int id, float mpayment, int mpaid, int mlimit):Insurance(id, mpayment, mpaid, mlimit){
    salary = sal;
    occupation = occ;
    beneficiaries = ben;
    feloncharges = fel;
    misdemeanorcharges = mis_charges;
    druguser = drug;
    highriskhobbies = hobbies;
    height = h;
    weight = w;
    physiciandetails = physician;
    seriousdiagnoses = diagnoses;

    //this constructor adds life insurance information, as well as initialize the base insurance information
}

void LifeInsurance::set_salary(float amount)
{ salary = amount; }

void LifeInsurance::set_occupation(QString text)
{ occupation = text; }

void LifeInsurance::set_beneficiaries(QString text)
{ beneficiaries = text; }

void LifeInsurance::set_feloncharges(bool value)
{ feloncharges = value; }

void LifeInsurance::set_misdemeanorcharges(bool value)
{ misdemeanorcharges = value; }

void LifeInsurance::set_druguser(bool value)
{ druguser = value; }

void LifeInsurance::set_highriskhobbies(QString text)
{ highriskhobbies = text; }

void LifeInsurance::set_height(QString text)
{ height = text; }

void LifeInsurance::set_weight(QString text)
{ weight = text; }

void LifeInsurance::set_physiciandetails(QString text)
{ physiciandetails = text; }

void LifeInsurance::set_seriousdiagnoses(QString text)
{ seriousdiagnoses = text; }

//-----------------------------------------------------------------------------------

float LifeInsurance::get_salary()
{ return salary; }

QString LifeInsurance::get_occupation()
{ return occupation; }

QString LifeInsurance::get_beneficiaries()
{ return beneficiaries; }

bool LifeInsurance::get_feloncharges()
{ return feloncharges; }

bool LifeInsurance::get_misdemeanorcharges()
{ return misdemeanorcharges; }

bool LifeInsurance::get_druguser()
{ return druguser; }

QString LifeInsurance::get_highriskhobbies()
{ return highriskhobbies; }

QString LifeInsurance::get_height()
{ return height; }

QString LifeInsurance::get_weight()
{ return weight; }

QString LifeInsurance::get_physiciandetails()
{ return physiciandetails; }

QString LifeInsurance::get_seriousdiagnoses()
{ return seriousdiagnoses; }
