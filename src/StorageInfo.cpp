#include "StorageInfo.h"

namespace fs = std::experimental::filesystem;

StorageInfo::StorageInfo(std::string path) {
    storagePath = path;
    updateInfo();
}

StorageInfo::StorageInfo() {
    storage_id = 1;
    storage_count = 1;
    status = 2; /* ready */
    capacity = 80000.0;
    available = 40000.0;
    free = 40000.0;
    used = 40000.0;
    read_speed = 3000;
    write_speed = 30000;
}

StorageInfo::~StorageInfo() {

}

void StorageInfo::updateInfo() {
    float mb = 1024*1024;
    fs::space_info devi = fs::space(storagePath.c_str());
    capacity=devi.capacity / mb;
    free=devi.free / mb;
    available=devi.available / mb;
    used =  (capacity-free) / mb;
    std::cout << ".\tCapacity\tFree\tAvailable\n" << storagePath << capacity << "\t"  << free << "\t" << available  << '\n';
}
