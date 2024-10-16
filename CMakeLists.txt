cmake_minimum_required(VERSION 3.26)
project(untitled43)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled43 source/main.cpp
        source/operationsFunc.cpp
        header/operationFuncs.h
        source/interfaceFuncs.cpp
        header/interfaceFuncs.h
        source/Product.cpp
        header/Product.h
        source/Profile.cpp
        header/Profile.h
        source/profileFuncs.cpp
        header/profileFuncs.h
        source/profileInterface.cpp
        header/profileInterface.h
        source/ProductData.cpp
        header/ProductData.h
)
