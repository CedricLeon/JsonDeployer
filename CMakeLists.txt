cmake_minimum_required(VERSION 3.15)
project(jsonDeployer)

set(SOURCE_FILES
    src/main.cpp)

#set CMAKE_PREFIX_PATH to find path of Qt5 package
set(CMAKE_PREFIX_PATH
    /home/cleonard/Qt/5.14.2/gcc_64/)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(jsonDeployer ${SOURCE_FILES})
target_compile_features(jsonDeployer PUBLIC cxx_std_17)
target_link_libraries(jsonDeployer Qt5::Core)