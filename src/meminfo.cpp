#include "meminfo.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::map<std::string, long> parseMemInfo(const std::string &path) {
    std::ifstream meminfo_file(path);
    if (!meminfo_file.is_open()) {
        std::cerr << "Error: Could not open " << path << std::endl;
        return {};
    }
    std::map<std::string, long> mem_values;
    std::string line;
    while (std::getline(meminfo_file, line)) {
        std::stringstream ss(line);
        std::string key;
        long value;
        std::string unit;
        if (std::getline(ss, key, ':')) {
            ss >> value >> unit;
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            mem_values[key] = value;
        }
    }
    return mem_values;
}

void printMemoryInfo(const std::map<std::string, long> &mem_values) {
    std::cout << "Memory Information:" << std::endl;
    if (mem_values.count("MemTotal")) {
        std::cout << "  Total Memory: " << mem_values.at("MemTotal") << " kB" << std::endl;
    }
    if (mem_values.count("MemFree")) {
        std::cout << "  Free Memory:  " << mem_values.at("MemFree") << " kB" << std::endl;
    }
    if (mem_values.count("MemAvailable")) {
        std::cout << "  Available Memory: " << mem_values.at("MemAvailable") << " kB" << std::endl;
    }
    if (mem_values.count("Buffers")) {
        std::cout << "  Buffers:      " << mem_values.at("Buffers") << " kB" << std::endl;
    }
    if (mem_values.count("Cached")) {
        std::cout << "  Cached:       " << mem_values.at("Cached") << " kB" << std::endl;
    }
}
