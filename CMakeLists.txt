cmake_minimum_required(VERSION 4.2)
project(binary_file_writer)

set(CMAKE_CXX_STANDARD 20)

configure_file(inlet.in inlet.in COPYONLY)

add_executable(binary_file_writer main.cpp src/file/TextFileReader.cpp
        src/ListNode.h
        src/file/TextFileReader.cpp
        src/file/BinaryFileWriter.cpp
        src/file/BinaryFileWriter.h)