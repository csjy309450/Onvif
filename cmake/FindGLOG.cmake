##########################################################################
#
##########################################################################
message("* glog:")
#message("${PROJECT_SOURCE_DIR}/common/glog/inlcude")

find_path(GLOG_INCLUDE_DIR glog ${PROJECT_SOURCE_DIR}/modules/common/)
message("*   GLOG_INCLUDE_DIR = ${GLOG_INCLUDE_DIR}")

find_library(GLOG_LIBRARY glog ${PROJECT_SOURCE_DIR}/lib)
message("*   GLOG_LIBRARY = ${GLOG_LIBRARY}")

if(GLOG_INCLUDE_DIR AND GLOG_LIBRARY)
    set(GLOG_FOUND TRUE)
endif(GLOG_INCLUDE_DIR AND GLOG_LIBRARY)