#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "threads.h"

class DiscoveryThread {

#define HOST_IP "239.255.255.250"
#define HOST_PORT 3702
//    const int   _metadataVersion = 1;
//    const char* _xaddr="http://localhost/service";
//    const char* _type="\"http://schemas.xmlsoap.org/ws/2006/02/devprof\":device";
//    const char* _scope="scope";
//    const char* _endpoint="urn";
public:
  DiscoveryThread();
  
  int start();

protected:
  
  static void *run(void *);
};

#endif // MYTHREAD_H
