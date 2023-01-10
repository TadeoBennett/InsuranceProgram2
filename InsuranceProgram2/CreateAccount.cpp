//Tadeo Bennett
#include "CreateAccount.h"
#include "ui_CreateAccount.h"

extern bool loggedIn; //flag to check if a user is logged in
extern Database* globaldb; //holds the database object

extern BaseUserInfo* loggedInUser; //holds the values of the logged in user

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

    if(ui->emailInput->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot add user"), tr("Email input is empty"));
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

    if(ui->repeatpasswordInput->text().trimmed() != ui->repeatpasswordInput->text().trimmed()){
        QMessageBox::warning(this, tr("Cannot add user"), tr("Passwords do not match"));
        return;
    }

    if(globaldb->get_databaseStatus()){
        QString email = ui->emailInput->text().trimmed();
        if(globaldb->checkEmail(email)){
            qDebug()<<"email already exists";
            QMessageBox::warning(this, tr("Cannot add user"), tr("User already exists with that email"));
            return;
        }


        QString firstname = ui->firstnameInput->text().trimmed();
        QString lastname = ui->lastnameInput->text().trimmed();
        int age = ui->ageInput->value();
        QString password = ui->passwordInput->text().trimmed();
        QString username = ui->firstnameInput->text()[0] + ui->lastnameInput->text();

        //pass values necessary to create a desk user
        bool adduser_flag = globaldb->addDeskUser(username, firstname, lastname, age, email, password);

        if(adduser_flag){
            //notify user upon successful action
            qDebug()<<"Desk user has been added to the database";

            QMessageBox::information(this, tr("Desk User added"), tr("You can now login as this user"));
            this->close();
        }else{
            QMessageBox::warning(this, tr("Cannot log in"), tr("Insert Query Failed. Try again"));
        }
    }else{
        qDebug()<<"no database connection was set";
        QMessageBox::critical(this, tr("Cannot log in"), tr("Could not connect to database"));
    }


    return;
}


void CreateAccount::on_cancelButton_clicked()
{
    this->close();
}

