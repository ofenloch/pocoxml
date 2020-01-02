cmake_minimum_required(VERSION 3.0.0)
project(pocoxml VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

include(CTest)
enable_testing()

add_executable(pocoxml ${PROJECT_SOURCE_DIR}/src/main.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
