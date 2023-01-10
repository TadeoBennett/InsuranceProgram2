//Tadeo Bennett
#include "renewPolicyOptions.h"
#include "ui_renewPolicyOptions.h"

renewPolicyOptions::renewPolicyOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renewPolicyOptions)
{
    ui->setupUi(this);

    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));

    parentWidget = parent;

    loadForm();
}

renewPolicyOptions::~renewPolicyOptions()
{
    delete ui;
}

void renewPolicyOptions::cancelButtonClicked()
{
    this->close();
}

void renewPolicyOptions::okButtonClicked()
{
    //FIX THE OPTIONS TO MATCH THE SETTINGS

    //If all options are unchecked
    if(ui->carInsuranceOption->isChecked() == Qt::Unchecked && ui->homeInsuranceOption->isChecked() == Qt::Unchecked && ui->lifeInsuranceOption->isChecked() == Qt::Unchecked){
        qDebug()<<"no insurance option selected";
        QMessageBox::warning(this, tr("Cannot renew policy"), tr("No insurance option selected"));
        return;
    }

    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    //creating options in settings
    settings.setValue("RenewCarInsurance", 0);
    settings.setValue("RenewHomeInsurance", 0);
    settings.setValue("RenewLifeInsurance", 0);

    //saving the option of the selected policy to renew
    if(ui->carInsuranceOption->isChecked()){
        settings.setValue("RenewCarInsurance", 1);
    }

    if(ui->homeInsuranceOption->isChecked()){
        settings.setValue("RenewHomeInsurance", 1);
    }

    if(ui->lifeInsuranceOption->isChecked()){
        settings.setValue("RenewLifeInsurance", 1);
    }

    this->close();

    RenewPolicyForm* newForm = new RenewPolicyForm(parentWidget);
    newForm->open();

}

void renewPolicyOptions::loadForm()
{
    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    //showing the insurance options if they exist
    if(settings.value("CarInsuranceExists") != 1){
        ui->carInsuranceOption->setVisible(false);
    }

    if(settings.value("LifeInsuranceExists") != 1){
        ui->lifeInsuranceOption->setVisible(false);
    }

    if(settings.value("HomeInsuranceExists") != 1){
        ui->homeInsuranceOption->setVisible(false);
    }

}
