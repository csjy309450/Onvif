//
// Created by yz on 18-8-26.
//

#ifndef LIBPUMP_LOGGER_H
#define LIBPUMP_LOGGER_H

#include <glog/logging.h>

namespace nsp_std = ::std;
namespace nsp_google = ::google;

#define LOGSTR(pStr) ((pStr==NULL || !strcmp(pStr, ""))?"\"\"":pStr)

class Logger {
public:
  Logger();
  
  ~Logger();
};


#endif //LIBPUMP_LOGGER_H
