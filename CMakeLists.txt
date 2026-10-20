cmake_minimum_required(VERSION 3.22)
project(apartment_finder)

set(CMAKE_CXX_STANDARD 14)

add_executable(apartment_finder
        main.cpp
        ApartmentLoader.cpp
)
