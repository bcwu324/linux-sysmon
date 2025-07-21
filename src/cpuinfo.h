#ifndef CPUINFO_H
#define CPUINFO_H

#include <utility>
#include <string>

std::pair<double, double> getCpuUsage();
std::pair<double, double> getCpuUsageFromFile(const std::string &path);

#endif // CPUINFO_H
