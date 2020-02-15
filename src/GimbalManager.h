#pragma once

#include <iostream>

#include "mqueue.h"

class GimbalManager 
{
public:
    GimbalManager();
    ~GimbalManager();
    void panUp();
    void panDown();
private:
    mqueue * mq_server;
    void sendMessage(int msg);
};
