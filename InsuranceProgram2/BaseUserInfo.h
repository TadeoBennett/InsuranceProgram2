#ifndef BASEUSERINFO_H
#define BASEUSERINFO_H

#include <QString>
#include <QList>
#include <QStringList>

class BaseUserInfo
{
public:
    BaseUserInfo();
    BaseUserInfo(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd);

private:
    int userid;
    int userlevelid;
    QString username;
    QString firstname;
    QString lastname;
    int age;
    QString password;

public:
    //setters
    void set_userid(int id);
    void set_userlevelid(int id);
    void set_username(QString name);
    void set_firstname(QString name);
    void set_lastname(QString name);
    void set_age(int a);
    void set_password(QString pwd);


    //getters
    int get_userid();
    int get_userlevelid();
    QString get_username();
    QString get_firstname();
    QString get_lastname();
    int get_age();
    QString get_password();
};

#endif // BASEUSERINFO_H
