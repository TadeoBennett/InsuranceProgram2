#ifndef NEWCUSTOMERINSURANCEOPTIONS_H
#define NEWCUSTOMERINSURANCEOPTIONS_H

#include <QDialog>

namespace Ui {
class NewCustomerInsuranceOptions;
}

class NewCustomerInsuranceOptions : public QDialog
{
    Q_OBJECT

public:
    explicit NewCustomerInsuranceOptions(QWidget *parent = nullptr);
    ~NewCustomerInsuranceOptions();

private:
    Ui::NewCustomerInsuranceOptions *ui;
};

#endif // NEWCUSTOMERINSURANCEOPTIONS_H
