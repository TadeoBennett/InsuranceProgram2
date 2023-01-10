#include "DeskQueries.h"

#include <ctime>
#include <iostream>
    using namespace std;

DeskQueries::DeskQueries()
{

}

QSqlQueryModel* DeskQueries::getCustomerListModel()
{
    QSqlQueryModel* newModel = new QSqlQueryModel();
    newModel->setQuery("SELECT customer.customerid, customer.homeinsuranceid, customer.carinsuranceid, customer.lifeinsuranceid, customer.citizenship, customer.firstname, customer.middlename, customer.lastname, customer.age, customer.phonenumber,  customer.socialsecuritynumber, customer.status AS 'Customer Status', user.userid, user.username, user.email, user.status AS 'User Status' FROM customer INNER JOIN user ON customer.customerid = user.customerid  WHERE customer.status = 1 ORDER BY customer.firstname;");
    return newModel;
}

QSqlQueryModel *DeskQueries::getCustomerListModelBySearch(QString name)
{
    QSqlQueryModel* newModel = new QSqlQueryModel();
    newModel->setQuery(QString("SELECT customer.customerid, customer.homeinsuranceid, customer.carinsuranceid, customer.lifeinsuranceid, customer.citizenship, customer.firstname, customer.middlename, customer.lastname, customer.age, customer.phonenumber,  customer.socialsecuritynumber, customer.status AS 'Customer Status', user.userid, user.username, user.email, user.status AS 'User Status' FROM customer INNER JOIN user ON customer.customerid = user.customerid  WHERE customer.status = 1 && CONCAT(customer.firstname, ' ', customer.lastname) LIKE '%%1%';").arg(name));
    return newModel;
}

int DeskQueries::addCustomer(QString uname, QString fname, QString lname, int a, QString pwd, int cus_id, QString ctz, QString mname, QString phone, int social, QString em, int stat)
{
    //ADDING THE CUSTOMER
    QSqlQuery addCustomer;
    addCustomer.prepare("INSERT INTO `customer` (`customerid`, `homeinsuranceid`, `carinsuranceid`, `lifeinsuranceid`, `citizenship`, `firstname`, `middlename`, `lastname`, `age`, `phonenumber`, `socialsecuritynumber`, `status`) VALUES (DEFAULT, NULL, NULL, NULL, :ctz, :fname, :mname, :lname, :age, :phone, :socialsn, :status);");
    addCustomer.bindValue(":ctz", ctz);
    addCustomer.bindValue(":fname", fname);
    addCustomer.bindValue(":mname", mname);
    addCustomer.bindValue(":lname", lname);
    addCustomer.bindValue(":age", a);
    addCustomer.bindValue(":phone", phone);
    addCustomer.bindValue(":socialsn", social);
    addCustomer.bindValue(":status", stat);

    //check if query worked
    if(addCustomer.exec()){qDebug()<<"add-customer query executed successfully";}else{qDebug()<<"add-customer query failed"; return 0;}


    //GETTING THE ID OF THE CUSTOMER THAT WAS JUST ADDED
    QSqlQuery getRecentCustomerId("SELECT MAX(customerid) AS customerid FROM customer;");
    while (getRecentCustomerId.next()) {
        cus_id = getRecentCustomerId.value(0).toInt();
    }


    //ADDING THE CUSTOMER TO A USER TABLE SO THEY CAN LOGIN
    QSqlQuery addCustomerAsUser;
    addCustomerAsUser.prepare("INSERT INTO `user` (`userid`, `userlevelid`, `customerid`, `username`, `firstname`, `lastname`, `age`, `email`, `password`, `status`) VALUES (DEFAULT, :userlevelid, :customerid, :uname, :fname, :lname, :age, :email, :password, :status);");
    addCustomerAsUser.bindValue(":userlevelid", 3);
    addCustomerAsUser.bindValue(":customerid", cus_id);
    addCustomerAsUser.bindValue(":uname", uname);
    addCustomerAsUser.bindValue(":fname", fname);
    addCustomerAsUser.bindValue(":lname", lname);
    addCustomerAsUser.bindValue(":age", a);
    addCustomerAsUser.bindValue(":email", em);
    addCustomerAsUser.bindValue(":password", pwd);
    addCustomerAsUser.bindValue(":status", stat);

    if(addCustomerAsUser.exec()){
        qDebug()<<"add-customer-as-user query executed successfully";
    }else{ qDebug()<<"add-customer-as-user query failed"; }

    return cus_id;
}

int DeskQueries::updateBasicCustomerDetails(int cus_id, QString ctz, QString fname, QString mname, QString lname, int a, QString phone, int social, int cus_status, QString uname, QString em)
{
    if(cus_status == 0){
        deleteCustomer(cus_id);
        return -1; //a customer was deleted(status set to o)
    }

    QSqlQuery updateCustomerRecord;
    updateCustomerRecord.prepare("UPDATE customer SET citizenship = :ctz, firstname = :fname, middlename = :mname, lastname = :lname, age = :age, phonenumber = :phone, socialsecuritynumber = :social WHERE customerid = :cus_id");
    updateCustomerRecord.bindValue(":ctz", ctz);
    updateCustomerRecord.bindValue(":fname", fname);
    updateCustomerRecord.bindValue(":mname", mname);
    updateCustomerRecord.bindValue(":lname", lname);
    updateCustomerRecord.bindValue(":age", a);
    updateCustomerRecord.bindValue(":phone", phone);
    updateCustomerRecord.bindValue(":social", social);
    updateCustomerRecord.bindValue(":cus_id", cus_id);

    if(!updateCustomerRecord.exec()){
        qDebug()<<"update customer query failed";
        return 0; //end attempt to update this customer
    }else{
        qDebug()<<"update customer query success";
        //continue function
    }

    QSqlQuery updateUserRecord;
    updateUserRecord.prepare("UPDATE user SET username = :uname, firstname = :fname, lastname = :lname, age = :age, email = :email WHERE customerid = :cus_id");
    updateUserRecord.bindValue(":uname", uname);
    updateUserRecord.bindValue(":fname", fname);
    updateUserRecord.bindValue(":lname", lname);
    updateUserRecord.bindValue(":age", a);
    updateUserRecord.bindValue(":email", em);
    updateUserRecord.bindValue(":cus_id", cus_id);

    if(!updateUserRecord.exec()){
        qDebug()<<"update user query failed";
        return -2; //end attempt to update this customer
    }else{
        qDebug()<<"update user query success";
        return 1; //attempt to edit this customer was successful
    }

    return -3;
}

bool DeskQueries::deleteCustomer(int cus_id)
{
    QSqlQuery deleteCustomer;
    deleteCustomer.prepare("UPDATE customer SET status = 0 WHERE customerid = :cus_id");
    deleteCustomer.bindValue(":cus_id", cus_id);
    if(!deleteCustomer.exec()){
        qDebug()<<"delete-customer query failed";
    }else{
        qDebug()<<"delete-customer query success";
        return true;
    }
    return false;
}

bool DeskQueries::deleteUserWithCustomerId(int cus_id)
{
    QSqlQuery deleteUser;
    deleteUser.prepare("UPDATE user SET status = 0 WHERE customerid = :cus_id");
    deleteUser.bindValue(":cus_id", cus_id);

    if(deleteUser.exec()){
        qDebug()<<"delete user/customer query executed successfully";
        return true;
    }else{
        qDebug()<<"delete user/customer query failed";
    }
    return false;
}

int DeskQueries::addCarInsurance(QString mk, QString ml, int license, QString vehicleid, int y, int miles, QString features, QString devices, int cus_id, float mpayment, int mpaid, int mlimit)
{
    int insuranceid = 0;
    QSqlQuery addCarInsurance;
    addCarInsurance.prepare("INSERT INTO `carinsurance` VALUES(DEFAULT, :cus_id, :make, :model, :license, :vid, :year, :ann_miles, :safetyf, :anti_td, :m_payment, :m_paid, :m_duration);");
    addCarInsurance.bindValue(":cus_id", cus_id);
    addCarInsurance.bindValue(":make", mk);
    addCarInsurance.bindValue(":model", ml);
    addCarInsurance.bindValue(":license", license);
    addCarInsurance.bindValue(":vid", vehicleid);
    addCarInsurance.bindValue(":year", y);
    addCarInsurance.bindValue(":ann_miles", miles);
    addCarInsurance.bindValue(":safetyf", features);
    addCarInsurance.bindValue(":anti_td", devices);
    addCarInsurance.bindValue(":m_payment", mpayment);
    addCarInsurance.bindValue(":m_paid", mpaid);
    addCarInsurance.bindValue(":m_duration", mlimit);

    if(addCarInsurance.exec()){
        qDebug()<<"add-car-insurance query executed successfully";
        QSqlQuery getInsuranceId("SELECT MAX(carinsuranceid) AS insuranceid FROM carinsurance;");
        while (getInsuranceId.next()) {
            insuranceid = getInsuranceId.value(0).toInt();
        }
    }else{ qDebug()<<"add-car-insurance query failed";}

    return insuranceid;
}

int DeskQueries::addHomeInsurance(QString add, QString mar_status, QString home_improv, int pet, int entr, QString p_athome, int cus_id, float mpayment, int mpaid, int mlimit)
{
    int insuranceid = 0;
    QSqlQuery addHomeInsurance;
    addHomeInsurance.prepare("INSERT INTO `homeinsurance` VALUES(DEFAULT, :cus_id, :address, :maritalstatus, :homeimprov, :petowner, :entrepreneur, :peopleathome, :m_payment, :m_paid, :m_duration);");
    addHomeInsurance.bindValue(":cus_id", cus_id);
    addHomeInsurance.bindValue(":address", add);
    addHomeInsurance.bindValue(":maritalstatus", mar_status);
    addHomeInsurance.bindValue(":homeimprov", home_improv);
    addHomeInsurance.bindValue(":petowner", pet);
    addHomeInsurance.bindValue(":entrepreneur", entr);
    addHomeInsurance.bindValue(":peopleathome", p_athome);
    addHomeInsurance.bindValue(":m_payment", mpayment);
    addHomeInsurance.bindValue(":m_paid", mpaid);
    addHomeInsurance.bindValue(":m_duration", mlimit);

    if(addHomeInsurance.exec()){
        qDebug()<<"add-home-insurance query executed successfully";
        QSqlQuery getInsuranceId("SELECT MAX(homeinsuranceid) AS insuranceid FROM homeinsurance;");
        while (getInsuranceId.next()) {
            insuranceid = getInsuranceId.value(0).toInt();
        }
    }else{ qDebug()<<"add-home-insurance query failed";}

    return insuranceid;
}

int DeskQueries::addLifeInsurance(float sal, QString occ, QString ben, int fel, int mis_charges,
                                  int drug, QString hobbies, QString h, QString w, QString physician, QString diagnoses, int cus_id, float mpayment, int mpaid, int mlimit)
{
    int insuranceid = 0;
    QSqlQuery addLifeInsurance;
    addLifeInsurance.prepare("INSERT INTO `lifeinsurance` VALUES(DEFAULT, :cus_id, :salary, :occupation, :beneficiaries, :feloncharges, :misdemeanorcharges, :druguser, :highriskhobbies, :height, :weight, :physiciandetails, :srs_diag, :m_payment, :m_paid, :m_duration);");
    addLifeInsurance.bindValue(":cus_id", cus_id);
    addLifeInsurance.bindValue(":salary", sal);
    addLifeInsurance.bindValue(":occupation", occ);
    addLifeInsurance.bindValue(":beneficiaries", ben);
    addLifeInsurance.bindValue(":feloncharges", fel);
    addLifeInsurance.bindValue(":misdemeanorcharges", mis_charges);
    addLifeInsurance.bindValue(":druguser", drug);
    addLifeInsurance.bindValue(":highriskhobbies", hobbies);
    addLifeInsurance.bindValue(":height", h);
    addLifeInsurance.bindValue(":weight", w);
    addLifeInsurance.bindValue(":physiciandetails", physician);
    addLifeInsurance.bindValue(":srs_diag", diagnoses);
    addLifeInsurance.bindValue(":m_payment", mpayment);
    addLifeInsurance.bindValue(":m_paid", mpaid);
    addLifeInsurance.bindValue(":m_duration", mlimit);


    if(addLifeInsurance.exec()){
        qDebug()<<"add-life-insurance query executed successfully";
        QSqlQuery getInsuranceId("SELECT MAX(lifeinsuranceid) AS insuranceid FROM lifeinsurance;");
        while (getInsuranceId.next()) {
            insuranceid = getInsuranceId.value(0).toInt();
        }
    }else{ qDebug()<<"add-life-insurance query failed";}

    return insuranceid;
}

bool DeskQueries::combineCarInsuranceWithCustomer(int cus_id, int insuranceid)
{
    QSqlQuery combineCarInsurance;
    combineCarInsurance.prepare("UPDATE `customer` SET carinsuranceid = :insuranceid WHERE customerid = :cus_id;");
    combineCarInsurance.bindValue(":insuranceid", insuranceid);
    combineCarInsurance.bindValue(":cus_id", cus_id);

    if(combineCarInsurance.exec()){
        qDebug()<<"combine car insurance query successful";
        return true;
    }else{
        qDebug()<<"combine car insurance query failed";
    }

    return false;
}

bool DeskQueries::combineHomeInsuranceWithCustomer(int cus_id, int insuranceid)
{
    QSqlQuery combineHomeInsurance;
    combineHomeInsurance.prepare("UPDATE `customer` SET homeinsuranceid = :insuranceid WHERE customerid = :cus_id;");
    combineHomeInsurance.bindValue(":insuranceid", insuranceid);
    combineHomeInsurance.bindValue(":cus_id", cus_id);

    if(combineHomeInsurance.exec()){
        qDebug()<<"combine home insurance query successful";
        return true;
    }else{
        qDebug()<<"combine home insurance query failed";
    }

    return false;
}

bool DeskQueries::combineLifeInsuranceWithCustomer(int cus_id, int insuranceid)
{
    QSqlQuery combineLifeInsurance;
    combineLifeInsurance.prepare("UPDATE `customer` SET lifeinsuranceid = :insuranceid WHERE customerid = :cus_id;");
    combineLifeInsurance.bindValue(":insuranceid", insuranceid);
    combineLifeInsurance.bindValue(":cus_id", cus_id);

    if(combineLifeInsurance.exec()){
        qDebug()<<"combine life insurance query successful";
        return true;
    }else{
        qDebug()<<"combine life insurance query failed";
    }

    return false;
}

double *DeskQueries::get_policyDetails(int itype, int userid)
{
    QSqlQuery insurancePolicyRenewDetails;
    switch(itype){
        case 1:{
            insurancePolicyRenewDetails.prepare("SELECT carinsurance.monthlypayment, carinsurance.monthspaid, carinsurance.monthlimit FROM carinsurance WHERE carinsurance.customerid = :cus_id;");
            insurancePolicyRenewDetails.bindValue(":cus_id", userid);
            if(insurancePolicyRenewDetails.exec()){
                qDebug()<<"get policy details successful";
            }else{
                qDebug()<<"get policy details failed";
                static double failed = 991; //return this int value if this query had failed
                return &failed;
            }
            qDebug()<< "showing the policy details";
            double monthlypayment;
            int monthspaid, monthlimit;
            while(insurancePolicyRenewDetails.next()){
                qDebug()<< insurancePolicyRenewDetails.value(0).toDouble();
                monthlypayment = insurancePolicyRenewDetails.value(0).toDouble();
                qDebug()<< insurancePolicyRenewDetails.value(1).toInt();
                monthspaid = insurancePolicyRenewDetails.value(1).toInt();
                qDebug()<< insurancePolicyRenewDetails.value(2).toInt();
                monthlimit = insurancePolicyRenewDetails.value(2).toInt();
            }
            static double arr[3];
            arr[0] = monthlypayment;
            arr[1] = monthspaid;
            arr[2] = monthlimit;

            return arr;
        break;}

        case 2:{
            insurancePolicyRenewDetails.prepare("SELECT homeinsurance.monthlypayment, homeinsurance.monthspaid, homeinsurance.monthlimit FROM homeinsurance WHERE homeinsurance.customerid = :cus_id;");
            insurancePolicyRenewDetails.bindValue(":cus_id", userid);
            if(insurancePolicyRenewDetails.exec()){
                qDebug()<<"get policy details successful";
            }else{
                qDebug()<<"get policy details failed";
                static double failed = 992; //return this int value if this query had failed
                return &failed;
            }
            qDebug()<< "showing the policy details";
            double monthlypayment;
            int monthspaid, monthlimit;
            while(insurancePolicyRenewDetails.next()){
                qDebug()<< insurancePolicyRenewDetails.value(0).toDouble();
                monthlypayment = insurancePolicyRenewDetails.value(0).toDouble();
                qDebug()<< insurancePolicyRenewDetails.value(1).toInt();
                monthspaid = insurancePolicyRenewDetails.value(1).toInt();
                qDebug()<< insurancePolicyRenewDetails.value(2).toInt();
                monthlimit = insurancePolicyRenewDetails.value(2).toInt();
            }

            static double arr[3];
            arr[0] = monthlypayment;
            arr[1] = monthspaid;
            arr[2] = monthlimit;

            return arr;

        break;}

        case 3:{
            insurancePolicyRenewDetails.prepare("SELECT lifeinsurance.monthlypayment, lifeinsurance.monthspaid, lifeinsurance.monthlimit FROM lifeinsurance WHERE lifeinsurance.customerid = :cus_id;");
            insurancePolicyRenewDetails.bindValue(":cus_id", userid);
            if(insurancePolicyRenewDetails.exec()){
                qDebug()<<"get policy details successful";
            }else{
                qDebug()<<"get policy details failed";
                static double failed = 993; //return this int value if this query had failed
                return &failed;
            }
            qDebug()<< "showing the policy details";
            double monthlypayment;
            int monthspaid, monthlimit;
            while(insurancePolicyRenewDetails.next()){
                qDebug()<< insurancePolicyRenewDetails.value(0).toDouble();
                monthlypayment = insurancePolicyRenewDetails.value(0).toDouble();
                qDebug()<< insurancePolicyRenewDetails.value(1).toInt();
                monthspaid = insurancePolicyRenewDetails.value(1).toInt();
                qDebug()<< insurancePolicyRenewDetails.value(2).toInt();
                monthlimit = insurancePolicyRenewDetails.value(2).toInt();
            }

            static double arr[3];
            arr[0] = monthlypayment;
            arr[1] = monthspaid;
            arr[2] = monthlimit;

            return arr;

        break;}
    }

    static double failed = 994;
    return &failed;

//    static int  r[10];

//    // set the seed
//    srand( (unsigned)time( NULL ) );

//    for (int i = 0; i < 10; ++i) {
//       r[i] = rand();
//    }

    //    return r;
}

bool DeskQueries::renewInsurance(int id, int itype, int mpaid)
{
    QSqlQuery insuranceRenew;
    if (itype == 1){ //car insurance
        insuranceRenew.prepare("UPDATE carinsurance SET monthspaid = :mpaid WHERE customerid = :cus_id;");
        insuranceRenew.bindValue(":mpaid", mpaid);
        insuranceRenew.bindValue(":cus_id", id);
        if(insuranceRenew.exec()){
            qDebug()<<"renew car insurance details successful";
            return true;
        }else{
            qDebug()<<"renew carinsurance details failed";
            return false;
        }
    }else if(itype == 2){ //home insurance
        insuranceRenew.prepare("UPDATE homeinsurance SET monthspaid = :mpaid WHERE customerid = :cus_id;");
        insuranceRenew.bindValue(":mpaid", mpaid);
        insuranceRenew.bindValue(":cus_id", id);
        if(insuranceRenew.exec()){
            qDebug()<<"renew home insurance details successful";
            return true;
        }else{
            qDebug()<<"renew home insurance details failed";
            return false;
        }
    }else if(itype == 3){ //life insurance
        insuranceRenew.prepare("UPDATE lifeinsurance SET monthspaid = :mpaid WHERE customerid = :cus_id;");
        insuranceRenew.bindValue(":mpaid", mpaid);
        insuranceRenew.bindValue(":cus_id", id);
        if(insuranceRenew.exec()){
            qDebug()<<"renew life insurance details successful";
            return true;
        }else{
            qDebug()<<"renew life insurance details failed";
            return false;
        }
    }

    return false;
}
