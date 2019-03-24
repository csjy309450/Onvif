include(${PROJECT_SOURCE_DIR}/modules/WSDiscovery/CMakeLists.txt)

set(WSDiscovery_INCLUDE_DIR )
set(WSDiscovery_LIBRARY )

find_path(WSDiscovery_INCLUDE_DIR discoveryobj.h discoverythread.h ${OVF_INC_DIR}/ws_discovery)
message("WSDiscovery_INCLUDE_DIR = ${WSDiscovery_INCLUDE_DIR}")

find_library(WSDiscovery_LIBRARY WSDiscovery ${OVF_LIBS_DIR})
message("lib dir: ${WSDiscovery_LIBRARY}")
message("OVF_LIBS_DIR = ${OVF_LIBS_DIR}")

if(WSDiscovery_INCLUDE_DIR AND WSDiscovery_LIBRARY)
    set(WSDiscovery_FOUND TRUE)
endif(WSDiscovery_INCLUDE_DIR AND WSDiscovery_LIBRARY)