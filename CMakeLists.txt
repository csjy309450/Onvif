cmake_minimum_required(VERSION 3.2)
project(Onvif CXX C)

set(CMAKE_CXX_STANDARD 98)

#message("ss${PROJECT_SOURCE_DIR}")

option(OVF_BUILD_WSDD "This is a option for xxx" ON)
option(OVF_BUILD_TEST "This is a option for xxx" ON)
option(OVF_USING_GLOG "This is a option for xxx" ON)
option(OVF_USING_BOOST "This is a option for xxx" OFF)
option(OVF_USING_PROTOBUF "This is a option for xxx" OFF)

include(${PROJECT_SOURCE_DIR}/CMake/Dependance.cmake)

include(${PROJECT_SOURCE_DIR}/modules/common/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/modules/ws_discovery/CMakeLists.txt)