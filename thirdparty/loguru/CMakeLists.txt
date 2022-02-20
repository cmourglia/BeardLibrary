project(loguru)
add_library(${PROJECT_NAME} STATIC loguru.cpp)
target_include_directories(loguru PUBLIC .)
target_compile_options(loguru
                       PRIVATE $<$<CXX_COMPILER_ID:gcc>:-Wno-format-truncation>)
