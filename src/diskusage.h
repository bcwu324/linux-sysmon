#ifndef DISKUSAGE_H
#define DISKUSAGE_H

#include <string>

struct DiskUsage {
    unsigned long total_kb;
    unsigned long used_kb;
    unsigned long available_kb;
};

DiskUsage getDiskUsage(const std::string &path);
DiskUsage parseDiskUsageFile(const std::string &path);
void printDiskUsage(const DiskUsage &du);

#endif // DISKUSAGE_H
