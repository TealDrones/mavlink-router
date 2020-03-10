#include "StorageInfo.h"

StorageInfo::StorageInfo(string path) {
    updateInfo();
    storagePath = path;
}

StorageInfo::StorageInfo() {
    storagePath = "/mnt/sdcard";
    storage_id = 1;
    storage_count = 1;
    status = 2; /* ready */
    capacity = 8000.0;
    available = 4000.0;
    used = 4000.0;
    read_speed = 3000;
    write_speed = 3000;
    updateInfo();
}

StorageInfo::~StorageInfo() {

}

void StorageInfo::updateInfo()
{
    struct statvfs vfs;

    if (statvfs(storagePath.c_str(), &vfs) != 0) {
        // error happens, just quits here
        return;
    }

    // // the available size is f_bsize * f_bavail
    // printf("mounted on %s:\n",storagePath);
    // printf("filesystem block size: f_bsize: %ld\n",  (long) vfs.f_bsize);
    // printf("fragment size:         f_frsize: %ld\n", (long) vfs.f_frsize);
    // printf("size of fs in f_frsize units: f_blocks: %lu\n", (unsigned long) vfs.f_blocks);
    // printf("free blocks:           f_bfree: %lu\n",  (unsigned long) vfs.f_bfree);
    // printf("free blocks for unprivileged users: f_bavail: %lu\n", (unsigned long) vfs.f_bavail);
    // printf("inodes: f_files: %lu\n",  (unsigned long) vfs.f_files);
    // printf("free inodes: f_ffree: %lu\n",  (unsigned long) vfs.f_ffree);
    // printf("free inodes for unprivileged users: f_favail: %lu\n", (unsigned long) vfs.f_favail);
    // printf("filesystem ID: f_fsid: %#lx\n",  (unsigned long) vfs.f_fsid);

    long mb = 1024*1024;
    long block_size = (long) vfs.f_bsize;
    long fragement_size = (long) vfs.f_frsize;
    unsigned long fragment_blocks = (unsigned long) vfs.f_blocks;
    unsigned long free_blocks = (unsigned long) vfs.f_bfree;

    capacity = fragement_size * fragment_blocks / mb;
    available = block_size * free_blocks / mb;
    used = capacity - available;

    cout << ".\tCapacity\tAvailable\tused\n" << storagePath << "\t" << capacity << "\t" << available << "\t" << used << " MB\n";

}
