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

private slots:
    void createCustomer();

private:
    Ui::CreateCustomerForm *ui;
};

#endif // CREATECUSTOMERFORM_H
