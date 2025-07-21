#include "cpuinfo.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::pair<double, double> parseStat(std::istream &in) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.rfind("cpu ", 0) == 0) {
            std::istringstream ss(line);
            std::string cpu;
            long long user = 0, nice = 0, system = 0, idle = 0;
            long long iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0, guest_nice = 0;
            ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
            long long user_time = user + nice;
            long long system_time = system + irq + softirq;
            long long total = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
            if (total == 0) return {0.0, 0.0};
            double user_pct = 100.0 * static_cast<double>(user_time) / static_cast<double>(total);
            double system_pct = 100.0 * static_cast<double>(system_time) / static_cast<double>(total);
            return {user_pct, system_pct};
        }
    }
    return {0.0, 0.0};
}

std::pair<double, double> getCpuUsageFromFile(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << path << std::endl;
        return {0.0, 0.0};
    }
    return parseStat(file);
}

std::pair<double, double> getCpuUsage() {
    std::ifstream file("/proc/stat");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open /proc/stat" << std::endl;
        return {0.0, 0.0};
    }
    return parseStat(file);
}
