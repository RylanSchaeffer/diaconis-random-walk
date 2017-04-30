cmake_minimum_required(VERSION 3.6)
project(diaconis-random-walk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES DiaconisDecipher.cpp PermutationFunctions.cpp BigramFrequencies.cpp)
add_executable(diaconis-random-walk ${SOURCE_FILES})