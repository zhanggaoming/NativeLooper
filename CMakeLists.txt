cmake_minimum_required(VERSION 3.10)
project(NativeLooper)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_CXX_COMPILER MATCHES "android")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif()

include_directories(./)

add_executable(NativeLooper MessageQueue.cpp NativeLooper.cpp NativeHandler.cpp Message.cpp Util.cpp main.cpp)

message("This CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}.")

if(CMAKE_CXX_COMPILER MATCHES "android")
    message("This is an Android build for ${CMAKE_ANDROID_ARCH_ABI}.")
    target_link_libraries(NativeLooper)
    # 添加特定于 Android 的配置
else()
    target_link_libraries(NativeLooper pthread)
    # 添加其他平台的配置
endif()


