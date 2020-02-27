#pragma once

#include <iostream>
#include <experimental/filesystem>

class StorageInfo {

public:
    StorageInfo(std::string);
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
    std::string storagePath;
};
