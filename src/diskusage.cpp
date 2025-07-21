#include "diskusage.h"
#include <sys/statvfs.h>
#include <fstream>
#include <iostream>

DiskUsage parseDiskUsageFile(const std::string &path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open " << path << std::endl;
        return {0, 0, 0};
    }
    DiskUsage du{};
    in >> du.total_kb >> du.used_kb >> du.available_kb;
    return du;
}

DiskUsage getDiskUsage(const std::string &path) {
    struct statvfs buf;
    if (statvfs(path.c_str(), &buf) != 0) {
        perror("statvfs");
        return {0, 0, 0};
    }
    unsigned long block_size = buf.f_frsize;
    unsigned long total = buf.f_blocks * block_size / 1024;
    unsigned long available = buf.f_bavail * block_size / 1024;
    unsigned long used = (buf.f_blocks - buf.f_bfree) * block_size / 1024;
    return {total, used, available};
}

void printDiskUsage(const DiskUsage &du) {
    std::cout << "Disk Usage:" << std::endl;
    std::cout << "  Total:      " << du.total_kb << " kB" << std::endl;
    std::cout << "  Used:       " << du.used_kb << " kB" << std::endl;
    std::cout << "  Available:  " << du.available_kb << " kB" << std::endl;
}
