cmake_minimum_required(VERSION 3.30)
project(PetShelter)

set(CMAKE_CXX_STANDARD 20)

add_executable(PetShelter main.cpp cat.h cat.cpp fish.cpp fish.h interestedadopter.h interestedadopter.cpp pet.cpp pet.h)
