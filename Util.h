//
// Created by lbrd on 2025/4/30.
//

#ifndef NATIVELOOPER_UTIL_H
#define NATIVELOOPER_UTIL_H
#include <cstdio>
#include <ctime>

#define MY_PRINTF(format, ...) \
    do { \
        time_t now = time(0); \
        struct tm* ltm = localtime(&now); \
        char timeBuffer[32]; \
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", ltm); \
        printf("[%s] " format "\n", timeBuffer, ##__VA_ARGS__); \
    } while (0)

class Util {

public:
    static long getCurrentTimeMillis();

};


#endif //NATIVELOOPER_UTIL_H
