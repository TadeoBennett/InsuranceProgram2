#include "RenewPolicyForm.h"
#include "ui_RenewPolicyForm.h"

extern Database* globaldb; //holds the database object

RenewPolicyForm::RenewPolicyForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenewPolicyForm)
{
    ui->setupUi(this);


//    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

//    //saving the option of the selected policy to renew
//    if(ui->carInsuranceOption->isChecked()){
//        settings.setValue("CustomerId", 1);
//    }

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));

    if (loadForm() == 0){ //close the form if there was an error reading the settings for the selected insurance
        QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection);
    }

}

RenewPolicyForm::~RenewPolicyForm()
{
    delete ui;
}

int RenewPolicyForm::loadForm()
{
    //check what insurance was selected and the userid using the settings;
    //return the monthlypayment, monthduration and months paid for this insurance policy
    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    //insurance types: carInsurance(1), home insurance(2), lifeInsurance(3)
    if(settings.value("RenewCarInsurance") != 0 && settings.value("RenewCarInsurance") == 1){
        ui->insurancetypeLabel->setText("Car Insurance");
        insuranceType = 1;
        double*  policyDetails = globaldb->get_policyDetails(1, settings.value("CustomerId").toInt());

        //possible errors
        if(*(policyDetails) == 991){
            QMessageBox::critical(this, tr("Cannot Open Form"), tr("Internal Error reading the car insurance details."));
            return 0;
        }else if(*(policyDetails) == 994){
            QMessageBox::critical(this, tr("Cannot Open Form"), tr("Internal Error reading the insurance type."));
            return 0;
        }

        qDebug()<<"cross-checking values:";
        for ( int i = 0; i < 3; i++ ) {
           qDebug() << *(policyDetails + i);
        }
        monthlypayment = *(policyDetails + 0);
        monthspaid = *(policyDetails + 1);
        monthlimit = *(policyDetails + 2);
    }
    else if(settings.value("RenewHomeInsurance") != 0 && settings.value("RenewHomeInsurance") == 1){
        ui->insurancetypeLabel->setText("Home Insurance");
        double*  policyDetails = globaldb->get_policyDetails(2, settings.value("CustomerId").toInt());
        insuranceType = 2;
        //possible errors
        if(*(policyDetails) == 992){
            QMessageBox::critical(this, tr("Cannot Open Form"), tr("Internal Error reading the home insurance details."));
            return 0;
        }else if(*(policyDetails) == 994){
            QMessageBox::critical(this, tr("Cannot Open Form"), tr("Internal Error reading the insurance type."));
            return 0;
        }

        qDebug()<<"cross-checking values:";
        for ( int i = 0; i < 3; i++ ) {
           qDebug() << *(policyDetails + i);
        }
        monthlypayment = *(policyDetails + 0);
        monthspaid = *(policyDetails + 1);
        monthlimit = *(policyDetails + 2);
    }
    else if(settings.value("RenewLifeInsurance") != 0 && settings.value("RenewLifeInsurance") == 1){
        ui->insurancetypeLabel->setText("Life Insurance");
        double*  policyDetails = globaldb->get_policyDetails(3, settings.value("CustomerId").toInt());
        insuranceType = 3;
        //possible errors
        if(*(policyDetails) == 993){
            QMessageBox::critical(this, tr("Cannot Open Form"), tr("Internal Error reading the life insurance details."));
            return 0;
        }
        else if(*(policyDetails) == 994){
            QMessageBox::critical(this, tr("Cannot Open Form"), tr("Internal Error reading the insurance type."));
            return 0;
        }

        qDebug()<<"cross-checking values:";
        for ( int i = 0; i < 3; i++ ) {
           qDebug() << *(policyDetails + i);
        }
        monthlypayment = *(policyDetails + 0);
        monthspaid = *(policyDetails + 1);
        monthlimit = *(policyDetails + 2);
    }else{
        QMessageBox::critical(this, tr("Cannot Open Form"), tr("Error reading settings"));
        return 0;
    }

    ui->monthlypaymentLabel->setText(QString::number(monthlypayment));
    ui->monthspaidLabel->setText(QString::number(monthspaid));
    ui->monthlimitLabel->setText(QString::number(monthlimit));
    ui->paymentamountLabel->setValue(0);
    ui->paymentamountLabel->setSingleStep(monthlypayment);

    return 1;
}

void RenewPolicyForm::okButtonClicked()
{
    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");
    //Determine the number of months paid given the input amount
    //if the number of months being paid for exceeds the monthly limit, give change. If is is equal to the limit, reset
    //the months paid to 0. Else just update the months paid count.

    paymentamount = ui->paymentamountLabel->value();
    double newMonthsPaid = paymentamount/monthlypayment + monthspaid;

    if(fmod(paymentamount, monthlypayment) > 0 ){
        QMessageBox::warning(this, tr("Cannot Renew Policy"), tr("Amount being paid must be divisible by the monthlypayment."));
        ui->paymentamountLabel->setValue(0);
        return;
    }else if(paymentamount <= 0){
        QMessageBox::warning(this, tr("Cannot Renew Policy"), tr("Enter a valid payment amount"));
        ui->paymentamountLabel->setValue(0);
        return;
    }else if(((paymentamount/monthlypayment) + monthspaid) > monthlimit){
        QMessageBox::warning(this, tr("Cannot Renew Policy"), tr("Exceed monthlimit"));
        ui->paymentamountLabel->setValue(0);
        return;
    }

    if(newMonthsPaid == monthlimit){
        QMessageBox::information(this, tr("Policy Reset"), tr("This year has been paid in full. Payment has been reset."));
        newMonthsPaid = 0;
    }

    //update months paid
    if(globaldb->renewInsurance(settings.value("CustomerId").toInt(), insuranceType, newMonthsPaid)){
        QMessageBox::information(this, tr("Renewed Policy"), tr("Updated the monthspaid"));
    }else{
        QMessageBox::information(this, tr("Cannot Renew Policy"), tr("Error updating the monthspaid"));
    }

    //reload the window
    qDebug()<<"Ok button clicked";
    if (loadForm() == 0){ //close the form if there was an error reading the settings for the selected insurance
        QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection);
    }
}

void RenewPolicyForm::cancelButtonClicked()
{
    this->close();
}
