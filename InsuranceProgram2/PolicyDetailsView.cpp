#include "PolicyDetailsView.h"
#include "ui_PolicyDetailsView.h"

extern BaseUserInfo * loggedInUser; //holds the values of the logged in user
extern bool loggedIn; //flag to check if a user is logged in

PolicyDetailsView::PolicyDetailsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PolicyDetailsView)
{
    ui->setupUi(this);

    ui->scrollContents->setLayout(ui->verticalLayout); //add the layout to the scroll area and make it scroll

    //use the parent slot to create the insurance report after clicking the print button
    connect(ui->printButton, SIGNAL(clicked()), parent, SLOT(createInsurancesReport()));

    loadPolicyDetails();
}

PolicyDetailsView::~PolicyDetailsView()
{
    delete ui;
}

void PolicyDetailsView::loadPolicyDetails()
{
    Customer* getCustomer = dynamic_cast<Customer*>(loggedInUser);
    //general information
    ui->firstname->setText(getCustomer->get_firstname());
    ui->middlename->setText(getCustomer->get_middlename());
    ui->lastname->setText(getCustomer->get_lastname());
    ui->age->setText(QString::number(getCustomer->get_age()));
    ui->phoneNumber->setText(getCustomer->get_phonenumber());
    ui->socialsecuritynumber->setText(QString::number(getCustomer->get_socialsecuritynumber()));
    ui->citizenship->setText(getCustomer->get_citizenship());


    if(getCustomer->insuranceList[0]->get_enabled()){ //car insurance exists
        //casting to a home insurance pointer to be able to access the insurance details
        CarInsurance* getInsurance = dynamic_cast<CarInsurance*>(getCustomer->insuranceList[0]);

        ui->make->setText(getInsurance->get_make());
        ui->model->setText(getInsurance->get_model());
        ui->licensenumber->setText(QString::number(getInsurance->get_licensenumber()));
        ui->vehicleidnumber->setText(getInsurance->get_vehicleidnumber());
        ui->year->setText(QString::number(getInsurance->get_year()));
        ui->annualmiles->setText(QString::number(getInsurance->get_annualmiles()));
        ui->safetyfeatures->setText(getInsurance->get_safetyfeatures());
        ui->antitheftdevices->setText(getInsurance->get_antitheftdevices());
        ui->car_monthlypayment->setText(QString::number(getInsurance->get_monthlypayment()));
        ui->car_monthspaid->setText(QString::number(getInsurance->get_monthspaid()));
        ui->car_monthduration->setText(QString::number(getInsurance->get_monthlimit()));
    }

    if(getCustomer->insuranceList[1]->get_enabled()){ //home insurance exists
        //casting to a home insurance pointer to be able to access the insurance details
        HomeInsurance* getInsurance = dynamic_cast<HomeInsurance*>(getCustomer->insuranceList[1]);

        ui->address->setText(getInsurance->get_address());
        ui->maritalstatus->setText(getInsurance->get_maritalstatus());
        if(getInsurance->get_petowner() == 1){
            ui->petowner->setText("Yes");
        }else{ui->petowner->setText("No");}
        if(getInsurance->get_entrepreneur() == 1){
            ui->entrepreneur->setText("Yes");
        }else{ui->entrepreneur->setText("No");}
        ui->homeimprovements->setText(getInsurance->get_homeimprovements());
        ui->peopleathome->setText(getInsurance->get_peopleathome());
        ui->home_monthlypayment->setText(QString::number(getInsurance->get_monthlypayment()));
        ui->home_monthspaid->setText(QString::number(getInsurance->get_monthspaid()));
        ui->home_monthduration->setText(QString::number(getInsurance->get_monthlimit()));
    }


    if(getCustomer->insuranceList[2]->get_enabled()){ //life insurance exists
        //casting to a life insurance pointer to be able to access the insurance details
        LifeInsurance* getInsurance = dynamic_cast<LifeInsurance*>(getCustomer->insuranceList[2]);

        ui->salary->setText(QString::number(getInsurance->get_salary()));
        ui->occupation->setText(getInsurance->get_occupation());
        if(getInsurance->get_feloncharges() == 1){
            ui->feloncharges->setText("Yes");
        }else{ui->feloncharges->setText("No");}
        if(getInsurance->get_misdemeanorcharges() == 1){
            ui->misdemeanorcharges->setText("Yes");
        }else{ui->misdemeanorcharges->setText("No");}
        if(getInsurance->get_druguser() == 1){
            ui->druguser->setText("Yes");
        }else{ui->druguser->setText("No");}
        ui->height->setText(getInsurance->get_height());
        ui->weight->setText(getInsurance->get_weight());
        ui->beneficiaries->setText(getInsurance->get_beneficiaries());
        ui->highriskhobbies->setText(getInsurance->get_highriskhobbies());
        ui->physiciandetails->setText(getInsurance->get_physiciandetails());
        ui->seriousdiagnoses->setText(getInsurance->get_seriousdiagnoses());
        ui->life_monthlypayment->setText(QString::number(getInsurance->get_monthlypayment()));
        ui->life_monthspaid->setText(QString::number(getInsurance->get_monthspaid()));
        ui->life_monthduration->setText(QString::number(getInsurance->get_monthlimit()));
    }

}
