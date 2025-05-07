//
// Created by lbrd on 2025/4/30.
//

#include "Util.h"
#include <chrono>

long Util::getCurrentTimeMillis() {
    // 获取当前时间点
    auto now = std::chrono::steady_clock::now();
    // 转换为自纪元以来的时间
    auto duration = now.time_since_epoch();
    // 转换为毫秒
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return millis.count();
}