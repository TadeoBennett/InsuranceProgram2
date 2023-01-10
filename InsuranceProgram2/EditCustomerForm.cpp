//Tadeo Bennett
#include "EditCustomerForm.h"
#include "renewPolicyOptions.h"
#include "ui_EditCustomerForm.h"

extern Database* globaldb; //holds the database object

EditCustomerForm::EditCustomerForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCustomerForm)
{
    ui->setupUi(this);

    connect(ui->addCustomerButton, SIGNAL(clicked()), this, SLOT(addCustomer()));
    connect(ui->refreshTableButton, SIGNAL(clicked()), this, SLOT(refreshTable()));
    connect(ui->deleteCustomerButton, SIGNAL(clicked()), this, SLOT(deleteCustomer()));
    connect(ui->seeMoreDetailsButton, SIGNAL(clicked()), this, SLOT(showMoreUpdateDetails()));
    connect(ui->updateDetailsButton, SIGNAL(clicked()), this, SLOT(updateDetails()));
    connect(ui->renewPolicyButton, SIGNAL(clicked()), this, SLOT(renewPolicy()));

    updateTableData();
}

EditCustomerForm::~EditCustomerForm()
{
    delete ui;
}

void EditCustomerForm::updateTableData()
{
    if(globaldb->get_databaseStatus()){ //if the database is connected
        ui->tableView->setModel(globaldb->getCustomerListModel()); //sets the table view data with users/employees
        qDebug()<<"loaded customers in table";
    }else{
        QMessageBox::critical(this, tr("Cannot Open Form"), tr("Database connection was lost"));
        this->close();
    }
}

void EditCustomerForm::on_tableView_activated(const QModelIndex &index)
{
    int val = ui->tableView->model()->data(index).toInt();
    if(globaldb->get_databaseStatus()){
        QSqlQuery getCustomerDetails;
        getCustomerDetails.prepare("SELECT customer.customerid, customer.citizenship, customer.firstname, customer.middlename, customer.lastname, customer.age, customer.phonenumber,  customer.socialsecuritynumber, customer.status AS 'Customer Status', user.userid, user.username, user.email, user.status AS 'User Status' FROM customer INNER JOIN user ON customer.customerid = user.customerid WHERE customer.customerid = :val;");
        getCustomerDetails.bindValue(":val", val);
        if(getCustomerDetails.exec()){
            while(getCustomerDetails.next()){
                ui->customerid->setText(getCustomerDetails.value(0).toString());
                selectedRecord = getCustomerDetails.value(0).toInt(); //saving the id of the customer being highlighted
                ui->citizenship->setText(getCustomerDetails.value(1).toString());
                ui->firstname->setText(getCustomerDetails.value(2).toString());
                ui->middlename->setText(getCustomerDetails.value(3).toString());
                ui->lastname->setText(getCustomerDetails.value(4).toString());
                ui->age->setText(getCustomerDetails.value(5).toString());
                ui->phonenumber->setText(getCustomerDetails.value(6).toString());
                ui->socialsecuritynumber->setText(getCustomerDetails.value(7).toString());
                ui->customerstatus->setText(getCustomerDetails.value(8).toString());
                ui->username->setText(getCustomerDetails.value(10).toString());
                ui->email->setText(getCustomerDetails.value(11).toString());
                ui->userstatus->setText(getCustomerDetails.value(12).toString());
            }
        }
    }else{
        QMessageBox::critical(this, tr("Could not load user information"), tr("Database connection was lost"));
        return;
    }
}

void EditCustomerForm::refreshTable()
{ updateTableData(); }

void EditCustomerForm::addCustomer()
{
    newCustomerOptions* newForm = new newCustomerOptions(this);
    newForm->open();
}

void EditCustomerForm::deleteCustomer()
{
    if(!ui->customerid->text().isEmpty()){
        if(globaldb->get_databaseStatus()){
            if(globaldb->deleteCustomer(ui->customerid->text().toInt())){
                QMessageBox::information(this, tr("Success"), tr("User has been deleted"));
            }
            ui->customerid->setText("");
            ui->citizenship->setText("");
            ui->firstname->setText("");
            ui->middlename->setText("");
            ui->lastname->setText("");
            ui->age->setText("");
            ui->phonenumber->setText("");
            ui->socialsecuritynumber->setText("");
            ui->customerstatus->setText("");
            ui->username->setText("");
            ui->email->setText("");
            ui->userstatus->setText("");
        }else{
            QMessageBox::critical(this, tr("Could not delete this user"), tr("Database connection was lost"));
        }
    }else{
        QMessageBox::critical(this, tr("Could not delete this customer"), tr("No customer selected"));
        return;
    }
    updateTableData();
}

void EditCustomerForm::updateDetails()
{
    if(!ui->customerid->text().isEmpty()){
            int customerid = ui->customerid->text().toInt();

            if(ui->citizenship->text().trimmed().isEmpty()){
                QMessageBox::warning(this, tr("Could not edit user"), tr("Citizenship not given. ex: Belizean"));
                return;
            }
            QString citizenship = ui->citizenship->text().trimmed();

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

            if(ui->middlename->text().trimmed().isEmpty()){
                QMessageBox::warning(this, tr("Could not edit user"), tr("No middle name given"));
                return;
            }
            QString middlename = ui->middlename->text().trimmed();

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

            if(ui->phonenumber->text().trimmed().isEmpty()){
                QMessageBox::warning(this, tr("Could not edit user"), tr("No phone number given"));
                return;
            }
            QString phonenumber = ui->phonenumber->text().trimmed();

            if(ui->socialsecuritynumber->text().trimmed().isEmpty()){
                QMessageBox::warning(this, tr("Cannot submit form"), tr("Social Security number input must not be empty"));
                return;
            }
            int socialsecuritynumber = ui->socialsecuritynumber->text().trimmed().toInt();

            if(ui->email->text().trimmed().isEmpty()){
                QMessageBox::warning(this, tr("Could not edit user"), tr("No email given"));
                return;
            }
            QString email = ui->email->text().trimmed();

            if(ui->customerstatus->text().trimmed().isEmpty()){
                QMessageBox::warning(this, tr("Could not edit user"), tr("No status given"));
                return;
            }else if(ui->customerstatus->text().trimmed().toInt() < 0 || ui->customerstatus->text().trimmed().toInt() > 1){
                QMessageBox::warning(this, tr("Could not edit user"), tr("Customer status is not valid"));
                return;
            }
            int customerstatus = ui->customerstatus->text().trimmed().toInt();

            if(globaldb->get_databaseStatus()){
                int updateCustomerFlag = globaldb->updateBasicCustomerDetails(customerid,  citizenship, firstname, middlename, lastname, age, phonenumber, socialsecuritynumber, customerstatus, username, email);
                if(updateCustomerFlag == 1){
                    QMessageBox::information(this, tr("Success"), tr("Customer has been edited"));
                }else if(updateCustomerFlag == -1){
                    QMessageBox::information(this, tr("Success"), tr("User has been deleted. No details updated."));
                }else if(updateCustomerFlag == 0){
                    QMessageBox::warning(this, tr("Could not edit this customer"), tr("Internal Query Error"));
                    return;
                }else if(updateCustomerFlag == -2){
                    QMessageBox::warning(this, tr("Could not edit customer's user details"), tr("Internal Query Error. Contact the developer about this issue."));
                    return;
                }else{
                    QMessageBox::warning(this, tr("Could not edit this customer"), tr("Internal Query Error unknown. Contact the developer."));
                    return;
                }
                ui->customerid->setText("");
                ui->citizenship->setText("");
                ui->firstname->setText("");
                ui->middlename->setText("");
                ui->lastname->setText("");
                ui->age->setText("");
                ui->phonenumber->setText("");
                ui->socialsecuritynumber->setText("");
                ui->customerstatus->setText("");
                ui->username->setText("");
                ui->email->setText("");
                ui->userstatus->setText("");
            }else{
                QMessageBox::critical(this, tr("Could not edit this customer"), tr("Database connection was lost"));
            }
        }else{
            QMessageBox::critical(this, tr("Could not edit customer"), tr("No customer selected"));
            return;
        }
        updateTableData();


}

void EditCustomerForm::showMoreUpdateDetails()
{
    //open form to show all data for this user
    QMessageBox::critical(this, tr("Sorry :-("), tr("Feature Under Development"));
    return;
}

void EditCustomerForm::renewPolicy()
{
    if(ui->customerid->text().isEmpty()){
        QMessageBox::critical(this, tr("Error"), tr("No customer selected"));
        return;
    }else{
        //find the insurances had for this customer
        if(globaldb->get_databaseStatus()){
            QSqlQuery getInsuranceDetails;
            getInsuranceDetails.prepare("SELECT customer.carinsuranceid, customer.homeinsuranceid, customer.lifeinsuranceid FROM customer INNER JOIN user ON customer.customerid = user.customerid WHERE customer.customerid = :val;");
            getInsuranceDetails.bindValue(":val", selectedRecord);
            qDebug()<<"Selected record id is "<<selectedRecord;
            if(getInsuranceDetails.exec()){
                int carinsuranceid, homeinsuranceid, lifeinsuranceid;
                while(getInsuranceDetails.next()){
                    carinsuranceid = getInsuranceDetails.value(0).toInt();
                    homeinsuranceid = getInsuranceDetails.value(1).toInt();
                    lifeinsuranceid = getInsuranceDetails.value(2).toInt();
                }

                QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");
                //resetting the settings that checks if specific insurances exists for this user
                settings.setValue("CarInsuranceExists", 0);
                settings.setValue("HomeInsuranceExists", 0);
                settings.setValue("LifeInsuranceExists", 0);
                settings.setValue("CustomerId", 0);

                if(carinsuranceid != 0){
                    settings.setValue("CarInsuranceExists", 1);
                }

                if(homeinsuranceid != 0){
                    settings.setValue("HomeInsuranceExists", 1);
                }

                if(lifeinsuranceid != 0){
                    settings.setValue("LifeInsuranceExists", 1);
                }

                settings.setValue("CustomerId", selectedRecord);

                qDebug()<<"car insurance id is "<<carinsuranceid;
                qDebug()<<"home insurance id is "<<homeinsuranceid;
                qDebug()<<"life insurance id is "<<lifeinsuranceid;

                if(homeinsuranceid == 0 && carinsuranceid == 0 && lifeinsuranceid == 0){
                    QMessageBox::warning(this, tr("Cannot renew policy"), tr("No policies found for this customer"));
                    return;
                }

                //create the options dialog to show which policy to renew...
                renewPolicyOptions* newForm = new renewPolicyOptions(this);
                newForm->open();

            }
        }else{
            QMessageBox::critical(this, tr("Could not load customer information"), tr("Database connection was lost"));
            return;
        }
    }
}


void EditCustomerForm::on_searchText_textChanged(const QString &arg1)
{
    if(arg1 == ""){
        updateTableData();
    }else{
        if(globaldb->get_databaseStatus()){
            ui->tableView->setModel(globaldb->getCustomerListModelBySearch(arg1)); //sets the table view data with users/employees
        }
    }
}

