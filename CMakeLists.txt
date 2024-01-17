cmake_minimum_required(VERSION 3.27)
project(PEA_Zad3)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif(WIN32)

set(CMAKE_CXX_STANDARD 20)

add_executable(PEA_Zad3 menu/main.cpp
        algorithms/geneticBase.cpp
        algorithms/geneticBase.h
        data/dataGenerator.cpp
        data/dataGenerator.h
        data/fileOperator.cpp
        data/fileOperator.h
        algorithms/geneticOX.cpp
        algorithms/geneticOX.h
        algorithms/geneticPMX.cpp
        algorithms/geneticPMX.h
        tests/tester.cpp
        tests/tester.h)

