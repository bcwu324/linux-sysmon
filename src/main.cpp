#include <iostream>
#include "meminfo.h"
#include "cpuinfo.h"
#include "diskusage.h"

int main() {
    auto mem_values = parseMemInfo("/proc/meminfo");
    printMemoryInfo(mem_values);
    auto disk_usage = getDiskUsage("/");
    printDiskUsage(disk_usage);
    auto cpu_usage = getCpuUsage();
    std::cout << "CPU Usage: user " << cpu_usage.first
              << "% system " << cpu_usage.second << "%" << std::endl;
    return 0;
}
