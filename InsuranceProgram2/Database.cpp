#include "Database.h"

extern BaseUserInfo * loggedInUser; //holds the values of the logged in user

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

QSqlDatabase Database::get_databaseStatus()
{ return db; }

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
            int userid, userlevelid, age;
            QString username, firstname, lastname, email, password;
            while(getUserLoggingIn.next()){
                QSqlRecord rec = getUserLoggingIn.record();
                userid = rec.value("userid").toInt(); // index of the field "name"
                userlevelid = rec.value("userlevelid").toInt(); // index of the field "userlevelid"
                username = rec.value("username").toString(); // index of the field "username"
                firstname = rec.value("firstname").toString(); // index of the field "firstname"
                lastname = rec.value("lastname").toString(); // index of the field "lastname"
                age = rec.value("age").toInt(); // index of the field "age"
                email = rec.value("email").toString(); // index of the field "email"
                password = rec.value("password").toString(); // index of the field "password"
            }

            //assigning a global object the values necessary to track the details of this logged-in user
            if(userlevelid == 1){
                loggedInUser = new Administrator( userid, userlevelid, username, firstname, lastname, age, email, password);
            }else if(userlevelid == 2){
                loggedInUser = new Desk( userid, userlevelid, username, firstname, lastname, age, email, password);
            }else if(userlevelid == 3){
                loggedInUser = new Customer( userid, userlevelid, username, firstname, lastname, age, email, password);
            }
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
    addDeskUser.prepare("INSERT INTO `user` (`userid`, `userlevelid`, `username`, `firstname`, `lastname`, `age`, `email`, `password`, `status`) VALUES (DEFAULT, :userlevelid, :uname, :fname, :lname, :age, :email, :password, :status);");
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
