#ifndef UTEIS_H
#define UTEIS_H

#include <string>
#include <ctime>

class Uteis {
public:
    static time_t parseDateTime(const char* datetimeString, const char* format);
};

#endif // UTEIS_H

