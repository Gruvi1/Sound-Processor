#pragma once

#include <fstream>
#include <vector>
#include <string>


class TConfigParser {
public:
    TConfigParser() = default;
    ~TConfigParser() = default;
    std::vector<std::vector<std::string>> Parse(const std::string& filePath);
};