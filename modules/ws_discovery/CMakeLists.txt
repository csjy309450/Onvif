#######################################################################
# MODULE:   WSDiscovery
# AUTHOR:   YangZheng
# DATE:     2019-03-23
#######################################################################

set(wsdd_target WSDiscovery)
set(wsdd_version 1.0.0)
set(wsdd_link_flag -lWSDiscovery)
set(wsdd_target_name lib${wsdd_target}.so)
set(wsdd_header
        ${glog_inc}
        ${common_header}
        ${CMAKE_CURRENT_LIST_DIR}/onvif/descdevice.h
        ${CMAKE_CURRENT_LIST_DIR}/onvif/discoveryobj.h
        ${CMAKE_CURRENT_LIST_DIR}/onvif/discoverythread.h
        ${CMAKE_CURRENT_LIST_DIR}/soap/wsaapi.h
        ${CMAKE_CURRENT_LIST_DIR}/soap/wsddapi.h
        ${CMAKE_CURRENT_LIST_DIR}/soap/onvifdiscoH.h
        ${CMAKE_CURRENT_LIST_DIR}/soap/onvifdiscoStub.h
        )
set(wsdd_src
        ${common_src}
        ${CMAKE_CURRENT_LIST_DIR}/onvif/discoveryobj.cpp
        ${CMAKE_CURRENT_LIST_DIR}/onvif/discoverythread.cpp
        ${CMAKE_CURRENT_LIST_DIR}/soap/wsaapi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/soap/wsddapi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/soap/onvifdiscoC.cpp
        ${CMAKE_CURRENT_LIST_DIR}/soap/onvifdiscoClient.cpp
        )

message("\n*****************************************************************")
message("* TAR: ${wsdd_target_name}\n* DIR: ${CMAKE_CURRENT_LIST_DIR} ")
message("*****************************************************************\n")

include_directories(
        ${CMAKE_CURRENT_LIST_DIR}/../common
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/onvif
        ${CMAKE_CURRENT_LIST_DIR}/soap
        )

if(OVF_USING_GLOG)
    ADD_DEFINITIONS(-D HAVE_USING_GLOG)
endif()

if(OVF_BUILD_WSDD)
    ## compile libWSDiscovery
    add_library(${wsdd_target} SHARED ${wsdd_header} ${wsdd_src})
endif()

if(OVF_BUILD_TEST)
    ## test code
    add_executable(wsdd_server ${CMAKE_CURRENT_LIST_DIR}/test/wsdd_server.cpp)
    target_link_libraries(wsdd_server ${glog_libs} ${wsdd_target})
endif()


## cmake test, should be removed in release code!
#add_library(ss SHARED ${wsdd_header} ${wsdd_src})
##set_target_properties (${wsdd_name} PROPERTIES OUTPUT_NAME ${wsdd_target})
#target_link_libraries(ss ${glog_libs})

#add_executable(wsdd_server ${CMAKE_CURRENT_LIST_DIR}/test/wsdd_server.cpp)
#target_link_libraries(wsdd_server ${glog_libs} ${wsdd_target})

#add_executable(wsdd_test ${CMAKE_CURRENT_LIST_DIR}/test/wsdd_test.cpp)
#target_link_libraries(wsdd_test ${glog_libs} ${wsdd_target})
