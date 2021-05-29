project(cpp_utils)
cmake_minimum_required(VERSION 3.10)

add_library(cpp_utils INTERFACE)
target_include_directories(cpp_utils INTERFACE include)
target_compile_definitions(cpp_utils INTERFACE 
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS> 
    $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
)