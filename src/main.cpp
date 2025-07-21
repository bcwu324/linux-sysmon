#include <iostream>
#include "meminfo.h"
#include "cpuinfo.h"

int main() {
    auto mem_values = parseMemInfo("/proc/meminfo");
    printMemoryInfo(mem_values);
    auto cpu_usage = getCpuUsage();
    std::cout << "CPU Usage: user " << cpu_usage.first
              << "% system " << cpu_usage.second << "%" << std::endl;
    return 0;
}
