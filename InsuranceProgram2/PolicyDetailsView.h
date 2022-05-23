#ifndef POLICYDETAILSVIEW_H
#define POLICYDETAILSVIEW_H

#include <QDialog>
#include <QString>
#include "Customer.h"
#include "CarInsurance.h"
#include "HomeInsurance.h"
#include "LifeInsurance.h"


namespace Ui {
class PolicyDetailsView;
}

class PolicyDetailsView : public QDialog
{
    Q_OBJECT

public:
    explicit PolicyDetailsView(QWidget *parent = nullptr);
    ~PolicyDetailsView();

public:
    void loadPolicyDetails();

private:
    Ui::PolicyDetailsView *ui;
};

#endif // POLICYDETAILSVIEW_H
