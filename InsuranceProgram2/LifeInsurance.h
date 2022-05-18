#ifndef LIFEINSURANCE_H
#define LIFEINSURANCE_H

#include "Insurance.h"
#include <QString>

class LifeInsurance: public Insurance
{
public:
    LifeInsurance();
    LifeInsurance(int id, float mpayment, int mpaid, int mlimit);
    LifeInsurance(float sal, QString occ, QString ben, bool fel, bool mis_charges, bool drug, QString hobbies, QString h, QString w, QString physician, QString diagnoses, /**/int id, float mpayment, int mpaid, int mlimit);

private:
    float salary;
    QString occupation;
    QString beneficiaries;
    bool feloncharges;
    bool misdemeanorcharges;
    bool druguser;
    QString highriskhobbies;
    QString height;
    QString weight;
    QString physiciandetails;
    QString seriousdiagnoses;

public:
    //setter
    void set_salary(float amount);
    void set_occupation(QString text);
    void set_beneficiaries(QString text);
    void set_feloncharges(bool value);
    void set_misdemeanorcharges(bool value);
    void set_druguser(bool value);
    void set_highriskhobbies(QString text);
    void set_height(QString text);
    void set_weight(QString text);
    void set_physiciandetails(QString text);
    void set_seriousdiagnoses(QString text);

    //getter
    float get_salary();
    QString get_occupation();
    QString get_beneficiaries();
    bool get_feloncharges();
    bool get_misdemeanorcharges();
    bool get_druguser();
    QString get_highriskhobbies();
    QString get_height();
    QString get_weight();
    QString get_physiciandetails();
    QString get_seriousdiagnoses();

};

#endif // LIFEINSURANCE_H
