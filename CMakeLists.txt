cmake_minimum_required(VERSION 3.2)
project(Onvif CXX C)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(OVF_LIBS_DIR ${PROJECT_SOURCE_DIR}/lib) # complie lib dir, default is "libonvif/lib"
set(OVF_INC_DIR ${PROJECT_SOURCE_DIR}/include) # complie header dir, default is "libonvif/include"

message("OVF_LIBS_DIR = ${OVF_LIBS_DIR}")

option(OVF_BUILD_WSDD "This is a option for xxx" ON)
option(OVF_BUILD_TEST "This is a option for xxx" ON)
option(OVF_USING_GLOG "This is a option for xxx" ON)
option(OVF_USING_BOOST "This is a option for xxx" OFF)
option(OVF_USING_PROTOBUF "This is a option for xxx" OFF)

include(${PROJECT_SOURCE_DIR}/cmake/Dependance.cmake)

include(${PROJECT_SOURCE_DIR}/modules/common/CMakeLists.txt)
add_subdirectory(${PROJECT_SOURCE_DIR}/modules/WSDiscovery)
#include(${PROJECT_SOURCE_DIR}/modules/WSDiscovery/CMakeLists.txt)