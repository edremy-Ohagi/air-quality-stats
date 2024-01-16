cmake_minimum_required(VERSION 3.15)
project(AirQualityStats LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将可执行文件输出到 build/bin，方便与 AQ_1.csv 放在一起
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(AirQualityStats
    空气质量统计系统.cpp
)

# 数据文件提示
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/AQ_1.csv")
    message(WARNING
        "AQ_1.csv not found in source directory. "
        "Please copy it to ${CMAKE_BINARY_DIR}/bin before running.")
else()
    # 如果数据文件存在，自动复制到输出目录
    configure_file(
        "${CMAKE_SOURCE_DIR}/AQ_1.csv"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AQ_1.csv"
        COPYONLY
    )
endif()
