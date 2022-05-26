#include "NewCustomerInsuranceOptions.h"
#include "ui_NewCustomerInsuranceOptions.h"

NewCustomerInsuranceOptions::NewCustomerInsuranceOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCustomerInsuranceOptions)
{
    ui->setupUi(this);
}

NewCustomerInsuranceOptions::~NewCustomerInsuranceOptions()
{
    delete ui;
}
