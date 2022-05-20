#ifndef DESK_H
#define DESK_H

#include "BaseUserInfo.h"

class Desk : public BaseUserInfo
{
public:
    Desk();

    //inherits constructor of baseuserinfo
    Desk(int user_id, int userlevel_id, QString uname, QString fname, QString lname, int a, QString em, QString pwd);
};

#endif // DESK_H
