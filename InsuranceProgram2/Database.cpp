#include "Database.h"

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
