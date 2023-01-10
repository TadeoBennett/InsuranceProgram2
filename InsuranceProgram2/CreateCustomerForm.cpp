#include "CreateCustomerForm.h"
#include "ui_CreateCustomerForm.h"

extern Database* globaldb; //holds the database object

extern BaseUserInfo * loggedInUser; //holds the values of the logged in user

CreateCustomerForm::CreateCustomerForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCustomerForm)
{
    ui->setupUi(this);

    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    ui->scrollContents->setLayout(ui->verticalLayout); //add the layout to the scroll area and make it scroll

    connect(ui->finishButton, SIGNAL(clicked()), this, SLOT(createCustomer()));

    loadForm();
}

CreateCustomerForm::~CreateCustomerForm()
{
    delete ui;
}

void CreateCustomerForm::loadForm()
{
    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    //check in the settings which insurance options were selected
    if(settings.value("CarInsuranceOption") == 0){
        qDebug()<<"car insurance was not selected";
        ui->carBox->setTitle("");
        ui->verticalLayout->removeWidget(ui->carBox);
        delete ui->carBox;
    }

    if(settings.value("HomeInsuranceOption") == 0){
        qDebug()<<"home insurance was not selected";
        ui->homeBox->setTitle("");
        ui->verticalLayout->removeWidget(ui->homeBox);
        delete ui->homeBox;
    }

    if(settings.value("LifeInsuranceOption") == 0){
        qDebug()<<"life insurance was not selected";
        ui->lifeBox->setTitle("");
        ui->verticalLayout->removeWidget(ui->lifeBox);
        delete ui->lifeBox;
    }

}

void CreateCustomerForm::addCustomer()
{
    //add basic customer information/all insuranceid values will be set to NULL
    if(!globaldb->get_databaseStatus()){
        qDebug()<<"Database connection lost";
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Database connection lost"));
        return;
    }else{

        customerid = globaldb->addCustomer(username, firstname, lastname, age, password, customerid, citizenship, middlename, phoneNumber, socialsecuritynumber, email, status);
        if(customerid != 0){
            qDebug()<<"Customer added";
        }else{
            QMessageBox::critical(this, tr("Could not add this customer"), tr("Internal error adding customer"));
            return;
        }
    }
}

void CreateCustomerForm::createCustomer()
{
    //checking for valid inputs
    if(ui->firstname->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("First name input must not be empty"));
        return;
    }
    firstname = ui->firstname->text();


    if(ui->middlename->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Middle name input must not be empty"));
        return;
    }
    middlename = ui->middlename->text();

    if(ui->lastname->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Last name input must not be empty"));
        return;
    }
    lastname = ui->lastname->text();

    username = ui->firstname->text()[0] + ui->lastname->text();

    if(ui->age->value() < 18){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Age input must be 18 or greater"));
        return;
    }
    age = ui->age->value();

    if(ui->phoneNumber->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Phone number input must not be empty"));
        return;
    }
    phoneNumber = ui->phoneNumber->text();

    if(ui->socialsecuritynumber->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Social Security number input must not be empty"));
        return;
    }
    socialsecuritynumber = ui->socialsecuritynumber->value();

    if(ui->citizenship->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Citizenship input must not be empty"));
        return;
    }
    citizenship = ui->citizenship->text();

    if(ui->email->text().trimmed().isEmpty()){
        QMessageBox::warning(this, tr("Cannot submit form"), tr("Email input must not be empty"));
        return;
    }
    email = ui->email->text();

    password = "password123";
    status = 1;
    customerid = 0;

    QSettings settings("TadeoBennett Programs", "Tadeo Bennett Insurance Distribution & Login System");

    //checking in the settings which insurance options were selected...
    int lifeinsuranceid; //flag to check if this insuranceExists
    int carinsuranceid; //flag to check if this insuranceExists
    int homeinsuranceid; //flag to check if this insuranceExists

    addCustomer();
    //------------------------------------------------------------------

    if(settings.value("CarInsuranceOption") == 1){
        //check if the most important details were set
        if(ui->car_monthlypayment->value() == 0){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("A monthly payment must be set for the car insurance"));
            return;
        }
        float monthlypayment = ui->car_monthlypayment->value();
        if(ui->car_monthduration->value() == 0){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("A month duration for payment must be set for the car insurance"));
            return;
        }
        int monthduration = ui->car_monthduration->value();

        int monthspaid = ui->car_monthspaid->value();

        //checking for valid inputs
        if(ui->make->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Make input must not be empty"));
            return;
        }
        QString make = ui->make->text();

        if(ui->model->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Model input must not be empty"));
            return;
        }
        QString model = ui->model->text();

        if(ui->licensenumber->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("License number input must not be empty"));
            return;
        }
        int licensenumber = ui->licensenumber->text().toInt();

        if(ui->vehicleidnumber->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Vehicle id number input must not be empty"));
            return;
        }
        QString vehicleidnumber = ui->vehicleidnumber->text();

        if(ui->year->value() < 1950){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Year input is not valid"));
            return;
        }
        int year = ui->year->value();

        int annualmiles = ui->annualmiles->value();

        QString safetyfeatures = ui->safetyfeatures->toPlainText();

        QString antitheftdevices = ui->antitheftdevices->toPlainText();

        if(!globaldb->get_databaseStatus()){
            qDebug()<<"Database connection lost. Ending add-insurance-process.";
            return;
        }else{
            //add basic customer information/all insuranceid values will be set to NULL
//            if(!globaldb->get_databaseStatus()){
//                qDebug()<<"Database connection lost";
//                QMessageBox::warning(this, tr("Cannot submit form"), tr("Database connection lost"));
//                return;
//            }else{
//                //add the customer information
//                customerid = globaldb->addCustomer(username, firstname, lastname, age, password, customerid, citizenship, middlename, phoneNumber, socialsecuritynumber, email, status);
//                if(customerid != 0){
//                    qDebug()<<"Customer added";
//                }else{
//                    QMessageBox::critical(this, tr("Could not add this customer"), tr("Internal error adding customer"));
//                    return;
//                }
//            }

            //add insurance policy for customer-pass the customer id returned
            carinsuranceid = globaldb->addCarInsurance(make, model, licensenumber, vehicleidnumber, year, annualmiles, safetyfeatures, antitheftdevices, customerid, monthlypayment, monthspaid, monthduration);
            if(carinsuranceid != 0){
                qDebug()<<"added new car insurance";
                //add the insurance id to the customer record
                globaldb->combineCarInsuranceWithCustomer(customerid, carinsuranceid);
            }else{
                qDebug()<<"could not add new car insurance";
            }
        }
    }

    //------------------------------------------------------------------

    if(settings.value("HomeInsuranceOption") == 1){
        //check if the most important details were set
        if(ui->home_monthlypayment->value() == 0){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("A monthly payment must be set for the home insurance"));
            return;
        }
        float monthlypayment = ui->home_monthlypayment->value();

        if(ui->home_monthduration->value() == 0){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("A month duration for payment must be set for the home insurance"));
            return;
        }
        int monthduration = ui->home_monthduration->value();

        int monthspaid = ui->home_monthspaid->value();

        //checking for valid inputs
        if(ui->address->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Address input must not be empty"));
            return;
        }
        QString address = ui->address->text();

        int petowner = 0;
        if(ui->petowner->checkState() == Qt::Checked){
            petowner = 1;
        }

        int entrepreneur = 0;
        if(ui->entrepreneur->checkState() == Qt::Checked){
            entrepreneur = 1;
        }

        QString homeimprovements = ui->homeimprovements->toPlainText();

        QString peopleathome = ui->peopleathome->toPlainText();

        QString maritalstatus;
        if(ui->maritalstatus->currentIndex() == 0){
            maritalstatus = "";
        }else if(ui->maritalstatus->currentIndex() == 1){
            maritalstatus = "married";
        }else if(ui->maritalstatus->currentIndex() == 2){
            maritalstatus = "widowed";
        }else if(ui->maritalstatus->currentIndex() == 3){
            maritalstatus = "divorced";
        }else if(ui->maritalstatus->currentIndex() == 4){
            maritalstatus = "separated";
        }else if(ui->maritalstatus->currentIndex() == 5){
            maritalstatus = "never married";
        }

        if(!globaldb->get_databaseStatus()){
            qDebug()<<"Database connection lost. Ending add-insurance-process.";
            return;
        }else{
            //add basic customer information/all insuranceid values will be set to NULL
//            if(!globaldb->get_databaseStatus()){
//                qDebug()<<"Database connection lost";
//                QMessageBox::warning(this, tr("Cannot submit form"), tr("Database connection lost"));
//                return;
//            }else{
//                customerid = globaldb->addCustomer(username, firstname, lastname, age, password, customerid, citizenship, middlename, phoneNumber, socialsecuritynumber, email, status);
//                if(customerid != 0){
//                    qDebug()<<"Customer added";
//                }else{
//                    QMessageBox::critical(this, tr("Could not add this customer"), tr("Internal error adding customer"));
//                    return;
//                }
//            }

            //add insurance policy for customer-pass the customer id returned
            homeinsuranceid = globaldb->addHomeInsurance(address, maritalstatus, homeimprovements, petowner, entrepreneur, peopleathome, /**/customerid, monthlypayment, monthspaid, monthduration);
            if(homeinsuranceid != 0){
                qDebug()<<"added new home insurance";
                //add the insurance id to the customer record
                globaldb->combineHomeInsuranceWithCustomer(customerid, homeinsuranceid);
            }else{
                qDebug()<<"could not add new home insurance";
            }
        }

    }

    //------------------------------------------------------------------

    if(settings.value("LifeInsuranceOption") == 1){
        //check if the most important details were set
        if(ui->life_monthlypayment->value() == 0){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("A monthly payment must be set for the life insurance"));
            return;
        }
        float monthlypayment = ui->life_monthlypayment->value();

        if(ui->life_monthduration->value() == 0){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("A month duration for payment must be set for the life insurance"));
            return;
        }
        float monthduration = ui->life_monthduration->value();

        //checking for valid inputs and just setting values
        int monthspaid = ui->life_monthspaid->value();

        QString beneficiaries = ui->beneficiaries->toPlainText();

        QString highriskhobbies = ui->highriskhobbies->toPlainText();

        QString physiciandetails = ui->physiciandetails->toPlainText();

        QString seriousdiagnoses = ui->seriousdiagnoses->toPlainText();

        int druguser = 0;
        if(ui->druguser->checkState() == Qt::Checked){
            druguser = 1;
        }

        int feloncharges = 0;
        if(ui->feloncharges->checkState() == Qt::Checked){
            feloncharges = 1;
        }

        if(ui->height->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Height input must not be empty"));
            return;
        }
        QString height = ui->height->text();

        if(ui->weight->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Weight input must not be empty"));
            return;
        }
        QString weight = ui->weight->text();

        int misdemeanorcharges = 0;
        if(ui->misdemeanorcharges->checkState() == Qt::Checked){
            misdemeanorcharges = 1;
        }

        if(ui->occupation->text().trimmed().isEmpty()){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Occupation input must not be empty"));
            return;
        }
        QString occupation = ui->occupation->text();

        if(ui->salary->value() == 0){
            QMessageBox::warning(this, tr("Cannot submit form"), tr("Salary input must not be empty"));
            return;
        }
        float salary = ui->salary->value();

        if(!globaldb->get_databaseStatus()){
            qDebug()<<"Database connection lost. Ending add-insurance-process.";
            return;
        }else{
            //add basic customer information/all insuranceid values will be set to NULL
//            if(!globaldb->get_databaseStatus()){
//                qDebug()<<"Database connection lost";
//                QMessageBox::warning(this, tr("Cannot submit form"), tr("Database connection lost"));
//                return;
//            }else{
//                customerid = globaldb->addCustomer(username, firstname, lastname, age, password, customerid, citizenship, middlename, phoneNumber, socialsecuritynumber, email, status);
//                if(customerid != 0){
//                    qDebug()<<"Customer added";
//                }else{
//                    QMessageBox::critical(this, tr("Could not add this customer"), tr("Internal error adding customer"));
//                    return;
//                }
//            }

            //add insurance policy for customer-pass the customer id returned
            lifeinsuranceid = globaldb->addLifeInsurance(salary, occupation, beneficiaries, feloncharges, misdemeanorcharges, druguser, highriskhobbies, height, weight, physiciandetails, seriousdiagnoses, /**/customerid, monthlypayment, monthspaid, monthduration);
            if(lifeinsuranceid != 0){
                qDebug()<<"added new life insurance";
                //add the insurance id to the customer record
                globaldb->combineLifeInsuranceWithCustomer(customerid, lifeinsuranceid);
            }else{
                qDebug()<<"could not add new life insurance";
            }
        }
    }

    //customer/user/insurances added

    //resetting the settings
    settings.setValue("HomeInsuranceOption", 0);
    settings.setValue("CarInsuranceOption", 0);
    settings.setValue("LifeInsuranceOption", 0);


    QMessageBox::warning(this, tr("Customer Created"), tr("Customer and insurance details has been added"));
    this->close();
}
