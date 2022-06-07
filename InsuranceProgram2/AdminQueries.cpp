#include "AdminQueries.h"

AdminQueries::AdminQueries()
{

}


bool AdminQueries::updateUser(int userid, int userlevelid, QString username, QString firstname, QString lastname, int age, QString email, int status)
{
    QSqlQuery updateUser;
    updateUser.prepare("UPDATE user SET userlevelid = :usl_id, username = :uname, firstname = :fname, lastname = :lname, age = :age, email = :em, status = :stat  WHERE userid = :id;");
    updateUser.bindValue(":usl_id", userlevelid);
    updateUser.bindValue(":uname", username);
    updateUser.bindValue(":fname", firstname);
    updateUser.bindValue(":lname", lastname);
    updateUser.bindValue(":age", age);
    updateUser.bindValue(":em", email);
    updateUser.bindValue(":stat", status);
    updateUser.bindValue(":id", userid);

    if(updateUser.exec()){
        qDebug()<<"update user query executed successfully";
        return true;
    }else{
        qDebug()<<"update user query failed";
    }
    return false;
}

bool AdminQueries::addDeskUser(QString uname, QString fname, QString lname, int a, QString em, QString pwd)
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

bool AdminQueries::deleteUser(int userid)
{
    QSqlQuery deleteUser;
    deleteUser.prepare("UPDATE user SET status = 0 WHERE userid = :id;");
    deleteUser.bindValue(":id", userid);

    if(deleteUser.exec()){
        qDebug()<<"delete user query executed successfully";
        return true;
    }else{
        qDebug()<<"delete user query failed";
    }
    return false;
}

QSqlQueryModel* AdminQueries::getEmployeeListModel()
{
    QSqlQueryModel* newModel = new QSqlQueryModel();
    newModel->setQuery("SELECT userid, userlevelid, username, firstname, lastname, age, email  FROM user WHERE userlevelid = 1 OR userlevelid = 2 && status = 1 ORDER BY firstname");
    return newModel;
}
