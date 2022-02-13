project(beard)
cmake_minimum_required(VERSION 3.20)

option(BEARD_BUILD_TESTS "Build tests" ON)
option(BEARD_ENABLE_GLM "Enable GLM" OFF)
option(BEARD_ENABLE_STB "Enable STB" OFF)

set(CMAKE_CXX_STANDARD 20)

if (ENABLE_GLM)
    add_subdirectory(thirdparty/glm)
endif ()

if (ENABLE_STB)
    add_library(stb_image STATIC thirdparty/stb_units/stb_image.c)
    target_include_directories(stb_image PUBLIC thirdparty/stb)
    target_compile_definitions(stb_image PRIVATE $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>)
    add_library(stb_truetype STATIC thirdparty/stb_units/stb_truetype.c)
    target_include_directories(stb_truetype PUBLIC thirdparty/stb)
endif ()

set(FETCHCONTENT_QUIET OFF CACHE BOOL "" FORCE)
include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 8.1.1
)

FetchContent_MakeAvailable(fmt)

add_subdirectory(thirdparty/loguru)

add_library(${PROJECT_NAME} STATIC
        src/timer.cpp
        src/io.cpp

        include/beard/core/macros.h

        include/beard/containers/array.h
        include/beard/misc/hash.h

        include/beard/containers/hash_map.h
        include/beard/io/io.h
        include/beard/misc/timer.h
        include/beard/misc/optional.h)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
        $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
        $<$<CXX_COMPILER_ID:MSVC>:_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING=1>
        )

target_link_libraries(${PROJECT_NAME} PUBLIC loguru fmt)

if (BEARD_BUILD_TESTS)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.0.0-preview4
    )

    FetchContent_MakeAvailable(Catch2)

    enable_testing()

    add_executable(TestCompile tests/TestCompile.cpp)
    target_link_libraries(TestCompile PRIVATE ${PROJECT_NAME})

    add_test(NAME TestCompile COMMAND TestCompile)
endif ()