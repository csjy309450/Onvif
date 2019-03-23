//
// Created by yz on 19-3-23.
//

#include "Logger.h"
#include "wsaapi.h"
#include "onvif/discoveryobj.h"

int main() {
  struct soap *serv = soap_new1(SOAP_IO_UDP);
  const char *_xaddr = "http://192.168.1.13:8004";
  const char *_endpoint = (char *) soap_wsa_rand_uuid(serv);
  const char *_scope = \
    "onvif://www.onvif.org/Profile/Streaming " \
    "onvif://www.onvif.org/hardware/NetworkVideoTransmitter " \
    "onvif://www.onvif.org/location/country/Azerbaijan " \
    "onvif://www.onvif.org/location/city/Baku " \
    "onvif://www.onvif.org/name/NVT";
  const char *_type = "discows:NetworkVideoTransmitter";
  
  //for genereatin randoim uuid end
  LOG(INFO) << "start server";
  
  DiscoveryObj *discoveryObj = new DiscoveryObj(SERVER_MODE, 1, _xaddr, _type, _scope, _endpoint);
  
  while (1) {
    printf("main thread !\n");
    sleep(5);
  }
  
  return 0;
}