#ifndef CREATECUSTOMERFORM_H
#define CREATECUSTOMERFORM_H

#include <QDialog>
#include <QSettings>
#include "Database.h"


namespace Ui {
class CreateCustomerForm;
}

class CreateCustomerForm : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCustomerForm(QWidget *parent = nullptr);
    ~CreateCustomerForm();

    void loadForm();
    void addCustomer();

private slots:
    void createCustomer();

private:
    Ui::CreateCustomerForm *ui;

    int customerid, socialsecuritynumber, age, status;
    QString username;
    QString firstname;
    QString middlename;
    QString lastname;
    QString password;
    QString citizenship;
    QString phoneNumber;
    QString email;

};

#endif // CREATECUSTOMERFORM_H
