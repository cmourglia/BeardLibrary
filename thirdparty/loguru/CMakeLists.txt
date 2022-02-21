project(loguru)
add_library(${PROJECT_NAME} STATIC loguru.cpp)
target_include_directories(loguru PUBLIC .)

if(UNIX)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  target_link_libraries(loguru PRIVATE Threads::Threads)
endif()

target_compile_options(loguru
                       PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wno-format-truncation>)
