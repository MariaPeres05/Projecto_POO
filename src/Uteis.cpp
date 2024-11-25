#include "Uteis.h"
#include <iostream>
#include <iomanip>
#include <sstream>




time_t Uteis::parseDateTime(const char* datetimeString, const char* format) {
    std::istringstream dateStream(datetimeString);
    struct tm tmStruct = {};
    dateStream >> std::get_time(&tmStruct, format);
    if (dateStream.fail()) {
        std::cerr << "Erro ao analisar a data: " << datetimeString << std::endl;
        return -1;
    }
    return mktime(&tmStruct);
}

