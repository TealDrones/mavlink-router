#pragma once

#include "GimbalManager.h"

GimbalManager::GimbalManager() {
    //cout << "Starting gimbal proxy";
    mq_server = new mqueue();
    mq_server->set_queue_name("/data/teal/mqueue/gimbal.msg");
    mq_server->start(true);
    mq_server->set_single_message_mode(true);
}

GimbalManager::~GimbalManager() {
}

// usage sendMessage(ch);
void GimbalManager::sendMessage(int msg) {
    char send = msg;
    if(!mq_server->write(& send)) {
        printf("Message_queue failed, client did not read the message\n");
        //cout << "Message_queue failed, client did not read the message";
    }
}

void GimbalManager::panUp() {
    printf("GimbaManager: pan UP\n");
    for (int i = 0; i < 5; i++){
        sendMessage('P');
    }
}

void GimbalManager::panDown() {
    printf("GimbaManager: pan DOWN\n");
    for (int i = 0; i < 5; i++){
        sendMessage('p');
    }
}
