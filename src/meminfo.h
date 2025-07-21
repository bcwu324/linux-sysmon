#ifndef MEMINFO_H
#define MEMINFO_H
#include <map>
#include <string>

std::map<std::string, long> parseMemInfo(const std::string &path);
void printMemoryInfo(const std::map<std::string, long> &mem_values);

#endif // MEMINFO_H
