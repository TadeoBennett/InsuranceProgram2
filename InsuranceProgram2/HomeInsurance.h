#ifndef HOMEINSURANCE_H
#define HOMEINSURANCE_H

#include "Insurance.h"
#include <QString>

class HomeInsurance: public Insurance
{
public:
    HomeInsurance();
    HomeInsurance(int id, float mpayment, int mpaid, int mlimit);
    HomeInsurance(QString add, QString mar_status, QString home_improv, bool pet, bool entr, QString p_athome, /**/int id, float mpayment, int mpaid, int mlimit);

private:
    QString address;
    QString maritalstatus;
    QString homeimprovements;
    bool petowner;
    bool entrepreneur;
    QString peopleathome;

    //setters
    void set_address(QString add);
    void set_maritalstatus(QString mar_status);
    void set_homeimprovements(QString home_improv);
    void set_petowner(bool pet);
    void set_entrepreneur(bool entr);
    void set_peopleathome(QString p_athome);

    //getters
    QString get_address();
    QString get_maritalstatus();
    QString get_homeimprovements();
    bool get_petowner();
    bool get_entrepreneur();
    QString get_peopleathome();

};

#endif // HOMEINSURANCE_H
