#pragma once
#include "User.h"
class Admin :
    public User
{
public:
    Admin() {}
    ~Admin() {}
    virtual int saveToFile();
    virtual void LoadData(int pos);
   
};

