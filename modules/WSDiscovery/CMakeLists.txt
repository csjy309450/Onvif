#######################################################################
# MODULE:   WSDiscovery
# AUTHOR:   YangZheng
# DATE:     2019-03-23
#######################################################################

set(wsdd_target WSDiscovery)
set(wsdd_version 1.0.0)

set(wsdd_target_name lib${wsdd_target}.so)

#if("${CMAKE_CURRENT_LIST_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
#    set(wsdd_prefix_dir )
#else()
#
#endif()

set(wsdd_export_header
        ${CMAKE_CURRENT_LIST_DIR}/onvif/discoveryobj.h
        ${CMAKE_CURRENT_LIST_DIR}/onvif/discoverythread.h)

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
        ${GLOG_INCLUDE_DIR}
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
    set(CMAKE_CXX_FLAGS_TMP "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "-Wl,-rpath=$ORIGIN ${CMAKE_CXX_FLAGS}")
    add_library(${wsdd_target} SHARED ${wsdd_header} ${wsdd_src})
    target_link_libraries(${wsdd_target} pthread ${GLOG_LIBRARY})
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_TMP}")
    install(TARGETS ${wsdd_target}
            DESTINATION ${OVF_LIBS_DIR})
    install(FILES ${wsdd_export_header}
            DESTINATION ${OVF_INC_DIR}/WSDiscovery)
endif()



if(OVF_BUILD_TEST)
    ## test code
    add_executable(wsdd_server ${CMAKE_CURRENT_LIST_DIR}/test/wsdd_server.cpp)
    target_link_libraries(wsdd_server ${wsdd_target})
    install(TARGETS wsdd_server
            DESTINATION ${OVF_LIBS_DIR})
endif()


## cmake test, should be removed in release code!
#add_library(ss SHARED ${wsdd_header} ${wsdd_src})
##set_target_properties (${wsdd_name} PROPERTIES OUTPUT_NAME ${wsdd_target})
#target_link_libraries(ss ${glog_libs})

#add_executable(wsdd_server ${CMAKE_CURRENT_LIST_DIR}/test/wsdd_server.cpp)
#target_link_libraries(wsdd_server ${glog_libs} ${wsdd_target})

#add_executable(wsdd_test ${CMAKE_CURRENT_LIST_DIR}/test/wsdd_test.cpp)
#target_link_libraries(wsdd_test ${glog_libs} ${wsdd_target})
