//Tadeo Bennett
#include "BaseUserInfo.h"

BaseUserInfo::BaseUserInfo()
{
    set_userid(0);
}

BaseUserInfo::BaseUserInfo(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString em, QString pwd):
    userid(user_id), userlevelid(userlevel_id), username(uname), firstname(fname), lastname(lname), age(a), email(em), password(pwd)
{}

void BaseUserInfo::set_userid(int id)
{ userid = id; }

void BaseUserInfo::set_userlevelid(int id)
{ userlevelid = id;}

void BaseUserInfo::set_username(QString name)
{ username = name; }

void BaseUserInfo::set_firstname(QString name)
{ firstname = name; }

void BaseUserInfo::set_lastname(QString name)
{ lastname = name; }

void BaseUserInfo::set_age(int a)
{ age = a; }

void BaseUserInfo::set_email(QString em)
{ email = em; }

void BaseUserInfo::set_password(QString pwd)
{ password = pwd; }

//-----------------------------------------------------------------------------------

int BaseUserInfo::get_userid()
{ return userid; }

int BaseUserInfo::get_userlevelid()
{ return userlevelid; }

QString BaseUserInfo::get_username()
{ return username; }

QString BaseUserInfo::get_firstname()
{ return firstname; }

QString BaseUserInfo::get_lastname()
{ return lastname; }

int BaseUserInfo::get_age()
{ return age; }

QString BaseUserInfo::get_email()
{ return email; }

QString BaseUserInfo::get_password()
{ return password; }
