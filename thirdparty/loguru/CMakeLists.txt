project(loguru)
add_library(${PROJECT_NAME} STATIC loguru.cpp)
target_include_directories(loguru PUBLIC .)