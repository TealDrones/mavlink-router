#pragma once

#include <sys/statvfs.h>
#include <string>
#include <iostream> 

using namespace std;

class StorageInfo {

public:
    StorageInfo();
    StorageInfo(string);
    ~StorageInfo();
    uint8_t storage_id;
    uint8_t storage_count;
    uint8_t status;

    float capacity;
    float available;
    float free;
    float used;

    float read_speed;
    float write_speed;

    void updateInfo();
private:
    string storagePath;
};
