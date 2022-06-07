#include "EditEmployeeForm.h"
#include "ui_EditEmployeeForm.h"

extern Database* globaldb; //holds the database object

EditEmployeeForm::EditEmployeeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployeeForm)
{
    ui->setupUi(this);

    connect(ui->addEmployeeButton, SIGNAL(clicked()), parent, SLOT(showCreateAccountForm()));
    connect(ui->deleteEmployeeButton, SIGNAL(clicked()), this, SLOT(deleteEmployee()));
    connect(ui->updateDetailsButton, SIGNAL(clicked()), this, SLOT(updateEmployee()));
    connect(ui->refreshTableButton, SIGNAL(clicked()), this, SLOT(refreshTable()));

    updateTableData();
}

EditEmployeeForm::~EditEmployeeForm()
{
    delete ui;
}

void EditEmployeeForm::updateTableData()
{
    if(globaldb->get_databaseStatus()){ //if the database is connected
        ui->tableView->setModel(globaldb->getEmployeeListModel()); //sets the table view data with users/employees
        qDebug()<<"loaded employeelist in table";
    }else{
        QMessageBox::critical(this, tr("Cannot Open Form"), tr("Database connection was lost"));
        this->close();
    }
}

void EditEmployeeForm::on_tableView_activated(const QModelIndex &index)
{
    int val = ui->tableView->model()->data(index).toInt();
    if(globaldb->get_databaseStatus()){
        QSqlQuery getUserDetails;
        getUserDetails.prepare("SELECT * FROM user WHERE userid = :val");
        getUserDetails.bindValue(":val", val);
        if(getUserDetails.exec()){
            while(getUserDetails.next()){
                ui->userid->setText(getUserDetails.value(0).toString());
                ui->userlevelid->setText(getUserDetails.value(1).toString());
                ui->username->setText(getUserDetails.value(3).toString());
                ui->firstname->setText(getUserDetails.value(4).toString());
                ui->lastname->setText(getUserDetails.value(5).toString());
                ui->age->setText(getUserDetails.value(6).toString());
                ui->email->setText(getUserDetails.value(7).toString());
                ui->status->setText(getUserDetails.value(9).toString());
            }
        }
    }else{
        QMessageBox::critical(this, tr("Could not load user information"), tr("Database connection was lost"));
        return;
    }
}

void EditEmployeeForm::deleteEmployee()
{
    if(!ui->userid->text().isEmpty()){
        if(globaldb->get_databaseStatus()){
            if(globaldb->deleteUser(ui->userid->text().toInt())){
                QMessageBox::information(this, tr("Success"), tr("User has been deleted"));
            }
            ui->userid->setText("");
            ui->userlevelid->setText("");
            ui->username->setText("");
            ui->firstname->setText("");
            ui->lastname->setText("");
            ui->age->setText("");
            ui->email->setText("");
            ui->status->setText("");
        }else{
            QMessageBox::critical(this, tr("Could not delete this user"), tr("Database connection was lost"));
        }
    }else{
        QMessageBox::critical(this, tr("Could not delete this user"), tr("No user selected"));
        return;
    }
    updateTableData();
}

void EditEmployeeForm::updateEmployee()
{
    if(!ui->userid->text().isEmpty()){
        int userid = ui->userid->text().toInt();

        if(ui->userlevelid->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Could not edit user"), tr("No user level given"));
            return;
        }else if(ui->userlevelid->text().trimmed().toInt() < 0 || ui->userlevelid->text().trimmed().toInt() > 2){
            QMessageBox::warning(this, tr("Could not edit user"), tr("User level id is not valid"));
            return;
        }
        int userlevelid = ui->userlevelid->text().trimmed().toInt();

        if(ui->username->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Could not edit user"), tr("No user name given"));
            return;
        }
        QString username = ui->username->text().trimmed();

        if(ui->firstname->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Could not edit user"), tr("No first name given"));
            return;
        }
        QString firstname = ui->firstname->text().trimmed();

        if(ui->lastname->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Could not edit user"), tr("No last name given"));
            return;
        }
        QString lastname = ui->lastname->text().trimmed();

        if(ui->age->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Could not edit user"), tr("No age given"));
            return;
        }else if(ui->age->text().trimmed().toInt() < 12){
            QMessageBox::warning(this, tr("Could not edit user"), tr("Age is not valid. Must be >12"));
            return;
        }
        int age = ui->age->text().trimmed().toInt();

        if(ui->email->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Could not edit user"), tr("No email given"));
            return;
        }
        QString email = ui->email->text().trimmed();

        if(ui->status->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Could not edit user"), tr("No status given"));
            return;
        }else if(ui->status->text().trimmed().toInt() < 0 || ui->status->text().trimmed().toInt() > 1){
            QMessageBox::warning(this, tr("Could not edit user"), tr("Status is not valid"));
            return;
        }
        int status = ui->status->text().trimmed().toInt();

        if(globaldb->get_databaseStatus()){
            qDebug()<<"userid: "<<userid<<" userlevelid: "<<userlevelid<<" username: "<<username <<" firstname: "<<firstname<<" lastname: "<<lastname<<" age: "<<age<<" email: "<<email<<" status: "<<status;
            if(globaldb->updateUser(userid, userlevelid, username, firstname, lastname, age, email, status)){
                QMessageBox::information(this, tr("Success"), tr("User has been edited"));
            }else{
                QMessageBox::warning(this, tr("Could not edit this user"), tr("Internal Query Error"));
            }
            ui->userid->setText("");
            ui->userlevelid->setText("");
            ui->username->setText("");
            ui->firstname->setText("");
            ui->lastname->setText("");
            ui->age->setText("");
            ui->email->setText("");
            ui->status->setText("");
        }else{
            QMessageBox::critical(this, tr("Could not edit this user"), tr("Database connection was lost"));
        }
    }else{
        QMessageBox::critical(this, tr("Could not edit user"), tr("No user selected"));
        return;
    }
    updateTableData();
}

void EditEmployeeForm::refreshTable()
{ updateTableData(); }
