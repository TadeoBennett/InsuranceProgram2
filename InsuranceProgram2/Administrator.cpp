//Tadeo Bennett

#include "Administrator.h"

Administrator::Administrator()
{

}

Administrator::Administrator(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString em, QString pwd):BaseUserInfo(user_id, userlevel_id, uname, fname, lname, a, em, pwd){
    //this is an inherited constructor
}
