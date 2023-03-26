cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab1 main.cpp service/CarService.cpp service_header/CarService.h service/InstructorService.cpp service_header/InstructorService.h view/view.cpp view/view.h entity/Car.cpp entity/Car.h entity/Instructor.cpp entity/Instructor.h respository/Repository.cpp repository_header/Repository.h)
