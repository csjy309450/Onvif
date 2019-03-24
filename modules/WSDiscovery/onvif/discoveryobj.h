#ifndef DISCOVERYOBJ_H
#define DISCOVERYOBJ_H

#include <vector>
#include <string>
#include "descdevice.h"
#include "discoverythread.h"

using namespace std;

enum DiscoveryMode {
  SERVER_MODE, 
  CLIENT_MODE
};

class DiscoveryObj {

private:
  DiscoveryThread discoveryThread;

public:
//    const int   _metadataVersion = 1;
//    const char* _xaddr="http://localhost/service";
//    const char* _type="\"http://schemas.xmlsoap.org/ws/2006/02/devprof\":device";
//    const char* _scope="scope";
//    const char* _endpoint="urn";
  
  void discoveredDevice(DescDevice);
  
  
  DiscoveryMode mode;
  static DiscoveryObj *theDiscovery;
  int _metadataVersion;
  const char *_xaddr;
  const char *_type;
  const char *_scope;
  const char *_endpoint;
  
  DiscoveryObj(DiscoveryMode mode, int _metadataVersion, const char *_xaddr, const char *_type, const char *_scope,
               const char *_endpoint);
  
  ~DiscoveryObj();
  
  int sendProb();
  
  int sendHello();
  
  int sendBye();
};

#endif
