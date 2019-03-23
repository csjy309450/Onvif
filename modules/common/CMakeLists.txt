#######################################################################
# MODULE:   common
# AUTHOR:   YangZheng
# DATE:     2019-03-23
#######################################################################

set(common_name WSDiscovery)
set(common_version 1.0.0)
set(common_target lib${wsdd_name}.so.${wsdd_version})
set(common_header
        ${CMAKE_CURRENT_LIST_DIR}/../common/stlvector.h
        ${CMAKE_CURRENT_LIST_DIR}/../common/threads.h
        ${CMAKE_CURRENT_LIST_DIR}/../common/stdsoap2.h
        ${CMAKE_CURRENT_LIST_DIR}/../common/Logger.h
        )
set(common_src
        ${CMAKE_CURRENT_LIST_DIR}/../common/stdsoap2.cpp
        ${CMAKE_CURRENT_LIST_DIR}/../common/threads.cpp
        ${CMAKE_CURRENT_LIST_DIR}/../common/Logger.cpp
        )