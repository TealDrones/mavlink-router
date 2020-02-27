#include "StorageInfo.h"

namespace fs = std::experimental::filesystem;
StorageInfo::StorageInfo(std::string path) {
    storagePath = path;
    updateInfo();
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
