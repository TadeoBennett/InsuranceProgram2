#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "BaseUserInfo.h"

class Administrator : public BaseUserInfo
{
public:
    Administrator();

    //inherits constructor of baseuserinfo
    Administrator(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString pwd);
};

#endif // ADMINISTRATOR_H
