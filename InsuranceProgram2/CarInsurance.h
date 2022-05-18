#ifndef CARINSURANCE_H
#define CARINSURANCE_H

#include "Insurance.h"
#include <QString>

class CarInsurance: public Insurance
{
public:
    CarInsurance();
    CarInsurance(int id, float mpayment, int mpaid, int mlimit);
    CarInsurance(QString mk, QString ml, int license, QString vehicleid, int y, int miles, QString features, QString devices, /**/int id, float mpayment, int mpaid, int mlimit);

private:
    QString make;
    QString model;
    int licensenumber;
    QString vehicleidnumber;
    int year;
    int annualmiles;
    QString safetyfeatures;
    QString antitheftdevices;

public:
    //setters
    void set_make(QString name);
    void set_model(QString name);
    void set_licensenumber(int num);
    void set_vehicleidnumber(QString num);
    void set_year(int num);
    void set_annualmiles(int num);
    void set_safetyfeatures(QString features);
    void set_antitheftdevices(QString devices);

    //getters
    QString get_make();
    QString get_model();
    int get_licensenumber();
    QString get_vehicleidnumber();
    int get_year();
    int get_annualmiles();
    QString get_safetyfeatures();
    QString get_antitheftdevices();

};

#endif // CARINSURANCE_H
