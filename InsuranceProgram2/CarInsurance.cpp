//Tadeo Bennett
#include "CarInsurance.h"

CarInsurance::CarInsurance()
{

}

CarInsurance::CarInsurance(int id, float mpayment, int mpaid, int mlimit):Insurance(id, mpayment, mpaid, mlimit){
    //this is an inherited constructor
}

CarInsurance::CarInsurance(QString mk, QString ml, int license, QString vehicleid, int y, int miles, QString features, QString devices, int id, float mpayment, int mpaid, int mlimit):Insurance(id, mpayment, mpaid, mlimit){
    make = mk;
    model = ml;
    licensenumber = license;
    vehicleidnumber = vehicleid;
    year = y;
    annualmiles = miles;
    safetyfeatures = features;
    antitheftdevices = devices;
    //this constructor adds car insurance information, as well as initialize the base insurance information
}

void CarInsurance::set_make(QString name)
{ make = name; }

void CarInsurance::set_model(QString name)
{ model = name; }

void CarInsurance::set_licensenumber(int num)
{ licensenumber = num; }

void CarInsurance::set_vehicleidnumber(QString num)
{ vehicleidnumber = num; }

void CarInsurance::set_year(int num)
{ year = num; }

void CarInsurance::set_annualmiles(int num)
{ annualmiles = num; }

void CarInsurance::set_safetyfeatures(QString features)
{ safetyfeatures = features; }

void CarInsurance::set_antitheftdevices(QString devices)
{ antitheftdevices = devices; }

//-----------------------------------------------------------------------------------

QString CarInsurance::get_make()
{ return make; }

QString CarInsurance::get_model()
{ return model; }

int CarInsurance::get_licensenumber()
{ return licensenumber; }

QString CarInsurance::get_vehicleidnumber()
{ return vehicleidnumber; }

int CarInsurance::get_year()
{ return year; }

int CarInsurance::get_annualmiles()
{ return annualmiles; }

QString CarInsurance::get_safetyfeatures()
{ return safetyfeatures; }

QString CarInsurance::get_antitheftdevices()
{ return antitheftdevices; }
