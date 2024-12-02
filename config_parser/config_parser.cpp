#include "config_parser.h"


std::string RemoveExtraSpace(const std::string& str) {
    std::string removedStr;
    size_t pos1 = str.find(' ');
    size_t pos2;
    std::string tempStr = str.substr(0, pos1);

    if (tempStr != "") {
        removedStr += tempStr + ' ';
    }

    while (pos1 != std::string::npos) {
        pos2 = str.find(' ', pos1 + 1);
        tempStr = str.substr(pos1 + 1, pos2 - pos1 - 1);
        if (tempStr != "") {
            removedStr += tempStr + ' ';
        }
        pos1 = pos2;
    }
    removedStr.pop_back();

    return removedStr;
}

std::vector<std::string> Split(const std::string& str) {
    std::vector<std::string> splittedStr;
    size_t pos1 = str.find(' ');
    size_t pos2;
    std::string tempWord = str.substr(0, pos1);

    splittedStr.push_back(tempWord);

    while (pos1 != std::string::npos) {
        pos2 = str.find(' ', pos1 + 1);
        tempWord = str.substr(pos1 + 1, pos2 - pos1 - 1);
        splittedStr.push_back(tempWord);
        pos1 = pos2;
    }

    return splittedStr;
}

std::vector<std::vector<std::string>> TConfigParser::Parse(const std::string& filePath) {
    std::vector<std::vector<std::string>> config;
    std::ifstream file;
    std::string line;

    file.open(filePath, std::ios::in);

    while (std::getline(file, line)) {
        if (line[0] == '#' || !line.size()) {
            continue;
        }
        config.push_back(Split(RemoveExtraSpace(line)));
    }
    file.close();

    return config;
}