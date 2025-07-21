#include <iostream>
#include "meminfo.h"

int main() {
    auto mem_values = parseMemInfo("/proc/meminfo");
    printMemoryInfo(mem_values);
    return 0;
}
