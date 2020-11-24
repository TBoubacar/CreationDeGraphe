cmake_minimum_required(VERSION 3.1.0)
project(TP1_LectureEcritureGraphe CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options(-Wall -Wpedantic)
endif()

add_executable(TP1_LectureEcritureGraphe main.cpp fonctionsio.cc)
