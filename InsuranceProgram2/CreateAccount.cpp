#include "CreateAccount.h"
#include "ui_CreateAccount.h"

CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_okButton_clicked()
{
    if(ui->firstnameInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot add user"), tr("First name input is empty"));
        return;
    }

    if(ui->lastnameInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot add user"), tr("Last name input is empty"));
        return;
    }

    if(ui->ageInput->value() < 12){
        QMessageBox::warning(this, tr("Cannot add user"), tr("Please input an age greater than 12."));
        return;
    }

    if(ui->passwordInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot add user"), tr("Password input is empty"));
        return;
    }

    if(ui->repeatpasswordInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot add user"), tr("Repeat password input is empty"));
        return;
    }

    if(ui->repeatpasswordInput->text() != ui->repeatpasswordInput->text()){
        QMessageBox::warning(this, tr("Cannot add user"), tr("Passwords do not match"));
        return;
    }

    QString username = ui->firstnameInput->text()[0] + ui->lastnameInput->text(); //username
    int userlevel = 2; //desk user level
    int status = 1; //status value

    //add desk user to database
}

