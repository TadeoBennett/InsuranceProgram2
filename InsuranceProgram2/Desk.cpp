#include "Desk.h"

Desk::Desk()
{

}

Desk::Desk(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd):BaseUserInfo(user_id, userlevel_id, uname, fname, lname, a, pwd){
    //this is an inherited constructor
}
