#ifndef RENEWPOLICYFORM_H
#define RENEWPOLICYFORM_H

#include <QDialog>
#include <QSettings>
#include "Database.h"

namespace Ui {
class RenewPolicyForm;
}

class RenewPolicyForm : public QDialog
{
    Q_OBJECT

public:
    explicit RenewPolicyForm(QWidget *parent = nullptr);
    ~RenewPolicyForm();

    int loadForm();
private slots:
    void okButtonClicked();
    void cancelButtonClicked();

private:
    Ui::RenewPolicyForm *ui;

    int insuranceType;
    float monthlypayment;
    int monthspaid;
    int monthlimit;
    float paymentamount;
};

#endif // RENEWPOLICYFORM_H
