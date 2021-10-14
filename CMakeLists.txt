project(BeardLibrary)
cmake_minimum_required(VERSION 3.20)

option(BEARD_BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
    src/Timer.cpp
    src/IO.cpp

    include/Beard/Macros.h

    include/Beard/Array.h
    include/Beard/Hash.h
    include/Beard/HashMap.h
    include/Beard/IO.h
    include/Beard/Timer.h
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
)

if(BEARD_BUILD_TESTS)
    enable_testing()

    add_executable(TestCompile tests/TestCompile.cpp)
    target_link_libraries(TestCompile PRIVATE ${PROJECT_NAME})

    add_test(NAME TestCompile COMMAND TestCompile)
endif()