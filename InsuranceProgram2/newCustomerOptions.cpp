#include "newCustomerOptions.h"
#include "ui_newCustomerOptions.h"

newCustomerOptions::newCustomerOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newCustomerOptions)
{
    ui->setupUi(this);

    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));

    parentWidget = parent;
}

newCustomerOptions::~newCustomerOptions()
{
    delete ui;
}

void newCustomerOptions::cancelButtonClicked()
{
    this->close();
}

void newCustomerOptions::okButtonClicked()
{
    if(ui->carInsuranceOption->checkState() == Qt::Unchecked && ui->homeInsuranceOption->checkState() == Qt::Unchecked && ui->lifeInsuranceOption->checkState() == Qt::Unchecked){
        qDebug()<<"no insurance option selected";
        QMessageBox::warning(this, tr("Cannot create customer"), tr("No insurance option selected"));
        return;
    }

    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    //creating options in settings
    settings.setValue("CarInsuranceOption", 0);
    settings.setValue("HomeInsuranceOption", 0);
    settings.setValue("LifeInsuranceOption", 0);


    //changing the insurance options settings if they were selected
    if(ui->carInsuranceOption->checkState() == Qt::Checked){
        settings.setValue("CarInsuranceOption", 1);
    }

    if(ui->homeInsuranceOption->checkState() == Qt::Checked){
        settings.setValue("HomeInsuranceOption", 1);
    }

    if(ui->lifeInsuranceOption->checkState() == Qt::Checked){
        settings.setValue("LifeInsuranceOption", 1);
    }

    this->close();

    CreateCustomerForm* newForm = new CreateCustomerForm(parentWidget);
    newForm->open();


}
