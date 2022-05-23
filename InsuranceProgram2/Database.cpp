#include "Database.h"

extern BaseUserInfo* loggedInUser; //holds the values of the logged in user

Database::Database()
{
    // start a connection to a MYSQL database suig corresponding driver
    db = QSqlDatabase::addDatabase("QMYSQL");

    //setting connection credentials
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("insuranceprogram2");

    if(db.open()){
        qDebug() << "database connected";
    }else{
         qDebug() << "database not connected";
         QMessageBox msgBox;
         msgBox.setText("Could not connect to database");
         msgBox.exec();
    }
}

bool Database::get_databaseStatus()
{ return db.isOpen(); }

bool Database::loginUser(QString em, QString pwd)
{
    QSqlQuery getUserLoggingIn;
    getUserLoggingIn.prepare("SELECT * FROM user WHERE email = :email && password = :password && status = 1;");
    getUserLoggingIn.bindValue(":email", em);
    getUserLoggingIn.bindValue(":password", pwd);

    if(getUserLoggingIn.exec()){
        qDebug()<<"select query executed successfully";
        if(getUserLoggingIn.size() == 1){
            qDebug()<<"a user with such details exists; attempting log in...";
            int userid, userlevelid, customerid, age;
            QString username, firstname, lastname, email, password;
            while(getUserLoggingIn.next()){
                QSqlRecord rec = getUserLoggingIn.record();
                userid = rec.value("userid").toInt(); // value of the field "userid"
                userlevelid = rec.value("userlevelid").toInt(); // value of the field "userlevelid"
                customerid = rec.value("customerid").toInt(); // value of the field "customerid"
                username = rec.value("username").toString(); // value of the field "username"
                firstname = rec.value("firstname").toString(); // value of the field "firstname"
                lastname = rec.value("lastname").toString(); // value of the field "lastname"
                age = rec.value("age").toInt(); // value of the field "age"
                email = rec.value("email").toString(); // value of the field "email"
                password = rec.value("password").toString(); // value of the field "password"
            }

            //assigning a global object the values necessary to track the details of this logged-in user
            if(userlevelid == 1){
                loggedInUser = new Administrator( userid, userlevelid, username, firstname, lastname, age, email, password);
            }else if(userlevelid == 2){
                loggedInUser = new Desk( userid, userlevelid, username, firstname, lastname, age, email, password);
            }else if(userlevelid == 3){
                //trying to get the insurance information of the customer trying to login
                QSqlQuery getInsuranceIds;
                getInsuranceIds.prepare("SELECT * FROM customer WHERE customerid = :id");
                getInsuranceIds.bindValue(":id", customerid);
                int homeinsuranceid, carinsuranceid, lifeinsuranceid, socialsecuritynumber; //variables for saving the results of the query
                QString citizenship, middlename, phoneNumber;
                if(getInsuranceIds.exec()){
                    while(getInsuranceIds.next()){
                        QSqlRecord rec = getInsuranceIds.record();
                        homeinsuranceid = rec.value("homeinsuranceid").toInt(); // value of the field "homeinsuranceid"
                        carinsuranceid = rec.value("carinsuranceid").toInt(); // value of the field "carinsuranceid"
                        lifeinsuranceid = rec.value("lifeinsuranceid").toInt(); // value of the field "lifeinsuranceid"

                        citizenship = rec.value("citizenship").toString(); // value of the field "citizenship"
                        middlename = rec.value("middlename").toString(); // value of the field "middlename"
                        phoneNumber = rec.value("phonenumber").toString(); // value of the field "phoneNumber"
                        socialsecuritynumber = rec.value("socialsecuritynumber").toInt(); // value of the field "socialsecuritynumber"
                    }

                    loggedInUser = new Customer(userid, userlevelid, username, firstname, lastname, age, email, password, customerid, citizenship, middlename, phoneNumber, socialsecuritynumber);

                    //creating homeinsurance details if any
                    if((homeinsuranceid != 0)){
                        QSqlQuery getHomeInsuranceDetails;
                        getHomeInsuranceDetails.prepare("SELECT * FROM homeinsurance WHERE homeinsuranceid = :id");
                        getHomeInsuranceDetails.bindValue(":id", homeinsuranceid);

                        //variables to save the query values
                        QString address, maritalstatus, homeImprovements, peopleAtHome; bool petOwner, entrepreneur;
                        float monthlypayment; int monthspaid, monthlimit;

                        if(getHomeInsuranceDetails.exec()){
                            while(getHomeInsuranceDetails.next()){
                                QSqlRecord rec = getHomeInsuranceDetails.record();
                                address = rec.value("address").toString(); // value of the field "address"
                                maritalstatus = rec.value("maritalstatus").toString(); // value of the field "maritalstatus"
                                homeImprovements = rec.value("homeimprovements").toString(); // value of the field "homeImprovements"
                                peopleAtHome = rec.value("peopleathome").toString(); // value of the field "peopleAtHome"
                                petOwner = rec.value("petowner").toBool(); // value of the field "petOwner"
                                entrepreneur = rec.value("entrepreneur").toBool(); // value of the field "entrepreneur"
                                monthlypayment = rec.value("monthlypayment").toFloat(); // value of the field "monthlypayment"
                                monthspaid = rec.value("monthspaid").toInt(); // value of the field "monthspaid"
                                monthlimit = rec.value("monthlimit").toInt(); // value of the field "homeinsuranceid"
                            }
                            //create copy of loggedInUser object and cast it to a customer object; then add the insurance details to that object;
                            //then make the loggedInUser object be a copy of the created customer object
                            Customer* newCustomer  = dynamic_cast<Customer*>(loggedInUser);
                            newCustomer->insuranceList[1] = new HomeInsurance(address, maritalstatus, homeImprovements, petOwner, entrepreneur, peopleAtHome, /**/userid, monthlypayment, monthspaid, monthlimit);
                            loggedInUser = newCustomer;
                        }else{
                            qDebug()<<"get home insurance details query failed";
                        }

                    }//end adding home insurance details

                    //creating carinsurance details if any
                    if((carinsuranceid != 0)){
                        QSqlQuery getCarInsuranceDetails;
                        getCarInsuranceDetails.prepare("SELECT * FROM carinsurance WHERE carinsuranceid = :id");
                        getCarInsuranceDetails.bindValue(":id", carinsuranceid);

                        //variables to save the query values
                        QString make, model, vehicleidnumber, safetyfeatures, antitheftdevices;
                        int licensenumber, year, annualmiles, monthspaid, monthlimit;
                        float monthlypayment;

                        if(getCarInsuranceDetails.exec()){
                            while(getCarInsuranceDetails.next()){
                                QSqlRecord rec = getCarInsuranceDetails.record();
                                make = rec.value("make").toString(); // value of the field "make"
                                model = rec.value("model").toString(); // value of the field "model"
                                licensenumber = rec.value("licensenumber").toInt(); // value of the field "licensenumber"
                                vehicleidnumber = rec.value("vehicleidnumber").toString(); // value of the field "vehicleidnumber"
                                year = rec.value("year").toInt(); // value of the field "year"
                                annualmiles = rec.value("annualmiles").toInt(); // value of the field "annualmiles"
                                safetyfeatures = rec.value("safetyfeatures").toString(); // value of the field "safetyfeatures"
                                antitheftdevices = rec.value("antitheftdevices").toString(); // value of the field "antitheftdevices"
                                monthlypayment = rec.value("monthlypayment").toFloat(); // value of the field "monthlypayment"
                                monthspaid = rec.value("monthspaid").toInt(); // value of the field "monthspaid"
                                monthlimit = rec.value("monthlimit").toInt(); // value of the field "homeinsuranceid"
                            }
                            //create copy of loggedInUser object and cast it to a customer object; then add the insurance details to that object;
                            //then make the loggedInUser object be a copy of the created customer object
                            Customer* newCustomer  = dynamic_cast<Customer*>(loggedInUser);
                            newCustomer->insuranceList[0] = new CarInsurance(make, model, licensenumber, vehicleidnumber, year, annualmiles, safetyfeatures, antitheftdevices, /**/userid, monthlypayment, monthspaid, monthlimit);
                            loggedInUser = newCustomer;
                        }else{
                            qDebug()<<"get car insurance details query failed";
                        }

                    }//end adding car insurance details

                    //creating lifeinsurance details if any
                    if((lifeinsuranceid != 0)){
                        QSqlQuery getLifeInsuranceDetails;
                        getLifeInsuranceDetails.prepare("SELECT * FROM lifeinsurance WHERE lifeinsuranceid = :id");
                        getLifeInsuranceDetails.bindValue(":id", lifeinsuranceid);

                        //variables to save the query values
                        float salary, monthlypayment; int monthspaid, monthlimit;
                        QString occupation, beneficiaries, highriskhobbies, height, weight, physiciandetails, seriousdiagnoses;
                        bool feloncharges, misdemeanorcharges, druguser;

                        if(getLifeInsuranceDetails.exec()){
                            while(getLifeInsuranceDetails.next()){
                                QSqlRecord rec = getLifeInsuranceDetails.record();
                                salary = rec.value("salary").toFloat(); // value of the field "salary"
                                occupation = rec.value("occupation").toString(); // value of the field "occupation"
                                beneficiaries = rec.value("beneficiaries").toString(); // value of the field "beneficiaries"
                                feloncharges = rec.value("feloncharges").toBool(); // value of the field "feloncharges"
                                misdemeanorcharges = rec.value("misdemeanorcharges").toBool(); // value of the field "misdemeanorcharges"
                                druguser = rec.value("druguser").toBool(); // value of the field "druguser"
                                highriskhobbies = rec.value("highriskhobbies").toString(); // value of the field "highriskhobbies"
                                height = rec.value("height").toString(); // value of the field "height"
                                weight = rec.value("weight").toString(); // value of the field "weight"
                                physiciandetails = rec.value("physiciandetails").toString(); // value of the field "physiciandetails"
                                seriousdiagnoses = rec.value("make").toString(); // value of the field "make"
                                monthlypayment = rec.value("monthlypayment").toFloat(); // value of the field "monthlypayment"
                                monthspaid = rec.value("monthspaid").toInt(); // value of the field "monthspaid"
                                monthlimit = rec.value("monthlimit").toInt(); // value of the field "homeinsuranceid"
                            }
                            //create copy of loggedInUser object and cast it to a customer object; then add the insurance details to that object;
                            //then make the loggedInUser object be a copy of the created customer object
                            Customer* newCustomer  = dynamic_cast<Customer*>(loggedInUser);
                            newCustomer->insuranceList[2] = new LifeInsurance(salary, occupation, beneficiaries, feloncharges, misdemeanorcharges, druguser, highriskhobbies, height, weight, physiciandetails, seriousdiagnoses, /**/userid, monthlypayment, monthspaid, monthlimit);
                            loggedInUser = newCustomer;
                        }else{
                            qDebug()<<"get life insurance details query failed";
                        }
                    }//end adding life insurance details
                }
            }//end checking userlevel
            return true;
        }
        qDebug()<<"NO user with such details exists; failed log in...";
    }else{
        qDebug()<<"select query failed";
    }
    return false;
}

bool Database::checkEmail(QString em)
{
    QSqlQuery getEmail;
    getEmail.prepare("SELECT * FROM user WHERE email = :email && status = 1;");
    getEmail.bindValue(":email", em);

    if(getEmail.exec()){
        qDebug()<<"getEmail query executed successfully";
        if(getEmail.size() == 1){
            return true; //return true if a record exists with that email
        }
    }
    return false;
}

bool Database::addDeskUser(QString uname, QString fname, QString lname, int a, QString em, QString pwd)
{
    QSqlQuery addDeskUser;
    addDeskUser.prepare("INSERT INTO `user` (`userid`, `userlevelid`, `customerid`, `username`, `firstname`, `lastname`, `age`, `email`, `password`, `status`) VALUES (DEFAULT, :userlevelid, NULL, :uname, :fname, :lname, :age, :email, :password, :status);");
    addDeskUser.bindValue(":userlevelid", 2);
    addDeskUser.bindValue(":uname", uname);
    addDeskUser.bindValue(":fname", fname);
    addDeskUser.bindValue(":lname", lname);
    addDeskUser.bindValue(":age", a);
    addDeskUser.bindValue(":email", em);
    addDeskUser.bindValue(":password", pwd);
    addDeskUser.bindValue(":status", 1);

    if(addDeskUser.exec()){
        qDebug()<<"add-user query executed successfully";
        return true;
    }else{
        qDebug()<<"select query failed";
    }

    return false;
}

bool Database::changePassword(int userId, QString password)
{
    QSqlQuery changePassword;
    changePassword.prepare("UPDATE user SET password = :pwd WHERE userid = :id");
    changePassword.bindValue(":pwd", password);
    changePassword.bindValue(":id", userId);

    if(changePassword.exec()){
        qDebug()<<"change password query executed successfully";
        loggedInUser->set_password(password);
        return true;
    }
    return false;
}
