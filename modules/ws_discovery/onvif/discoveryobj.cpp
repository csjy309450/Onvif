/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** probe.cpp
** 
** WS-Discovery probe/resolve
**
** -------------------------------------------------------------------------*/
#include "../soap/wsddapi.h"
#include <getopt.h>
#include "discoveryobj.h"
#include "Logger.h"
#include "soap/wsdd.nsmap"

DiscoveryObj *DiscoveryObj::theDiscovery = NULL;

DiscoveryObj::DiscoveryObj(DiscoveryMode mode, int _metadataVersion, const char *_xaddr, const char *_type,
                           const char *_scope,
                           const char *_endpoint) {
  this->mode = mode;
  theDiscovery = this;
  this->_metadataVersion = _metadataVersion;
  this->_xaddr = _xaddr;
  this->_type = _type;
  this->_scope = _scope;
  this->_endpoint = _endpoint;
  
  discoveryThread.start();
  if (mode == SERVER_MODE) {
    sendHello();
  }
}

DiscoveryObj::~DiscoveryObj() {
  LOG(INFO) << "DiscoveryObj deleted";
  sendBye();
}

void DiscoveryObj::discoveredDevice(DescDevice dev) {

}

int DiscoveryObj::sendProb() {
  const char *endpoint = "";
  const char *type = NULL;
  const char *scope = NULL;

//	int c = 0;
//	while ((c = getopt (argc, argv, "r:t:s:")) != -1)
//	{
//		switch (c)
//		{
//			case 'r': endpoint = optarg; break;
//			case 't': type     = optarg; break;
//			case 's': scope    = optarg; break;
//			default:
//				std::cout << int(c) << std::endl;
//				std::cout << argv[0] << std::endl;
//				std::cout << "\t -r <endpoint>        : resolve endpoint" << std::endl;
//				std::cout << "\t -t <type> -s <scope> : probe for type/scope" << std::endl;
//				exit(0);
//			break;
//		}
//	}
  
  // create soap instance
  struct soap *serv = soap_new1(SOAP_IO_UDP);
  if (!soap_valid_socket(soap_bind(serv, NULL, 0, 1000))) {
    soap_print_fault(serv, stderr);
    exit(1);
  }
  
  int res = 0;
  // call resolve or probe
  if (strlen(endpoint) == 0) {
    res = soap_wsdd_Probe(serv,
                          SOAP_WSDD_ADHOC,      // mode
                          SOAP_WSDD_TO_TS,      // to a TS
                          "soap.udp://239.255.255.250:3702",         // address of TS
                          soap_wsa_rand_uuid(serv),                   // message ID
                          NULL,                 // ReplyTo
                          type,
                          scope,
                          NULL);
  } else {
    // send resolve request
    res = soap_wsdd_Resolve(serv,
                            SOAP_WSDD_ADHOC,      // mode
                            SOAP_WSDD_TO_TS,      // to a TS
                            "soap.udp://239.255.255.250:3702",         // address of TS
                            soap_wsa_rand_uuid(serv),                   // message ID
                            NULL,                 // ReplyTo
                            endpoint);
  }
  
  if (res != SOAP_OK) {
    soap_print_fault(serv, stderr);
    fflush(stderr);
  }
  
  // listen answers
  soap_wsdd_listen(serv, -1000000);
  
  return 0;
  
}


int DiscoveryObj::sendHello() {
  struct soap *soap = soap_new1(SOAP_IO_UDP);
  LOG(INFO) << ("call soap_wsdd_Hello\n");
  int res = soap_wsdd_Hello(soap,
                            SOAP_WSDD_ADHOC,      // mode
                            "soap.udp://239.255.255.250:3702",         // address of TS
                            soap_wsa_rand_uuid(soap),                   // message ID
                            NULL,
                            _endpoint,
                            _type,
                            _scope,
                            NULL,
                            _xaddr,
                            _metadataVersion);
  if (res != SOAP_OK) {
    soap_print_fault(soap, stderr);
  }
  soap_end(soap);
}

int DiscoveryObj::sendBye() {
  struct soap *soap = soap_new1(SOAP_IO_UDP);
  LOG(INFO) << ("call soap_wsdd_Hello\n");
  int res = soap_wsdd_Bye(soap,
                          SOAP_WSDD_ADHOC,      // mode
                          "soap.udp://239.255.255.250:3702",         // address of TS
                          soap_wsa_rand_uuid(soap),                   // message ID
                          _endpoint,
                          _type,
                          _scope,
                          NULL,
                          _xaddr,
                          _metadataVersion);
  if (res != SOAP_OK) {
    soap_print_fault(soap, stderr);
  }
  soap_end(soap);
}


template<class T>
void printMatch(const T &match) {
  LOG(INFO) << "===================================================================" << std::endl;
  if (match.wsa__EndpointReference.Address) {
    LOG(INFO) << "Endpoint:\t" << match.wsa__EndpointReference.Address << std::endl;
  }
  if (match.Types) {
    LOG(INFO) << "Types:\t\t" << match.Types << std::endl;
  }
  if (match.Scopes) {
    if (match.Scopes->__item) {
      LOG(INFO) << "Scopes:\t\t" << match.Scopes->__item << std::endl;
    }
    if (match.Scopes->MatchBy) {
      LOG(INFO) << "MatchBy:\t" << match.Scopes->MatchBy << std::endl;
    }
  }
  if (match.XAddrs) {
    LOG(INFO) << "XAddrs:\t\t" << match.XAddrs << std::endl;
  }
  LOG(INFO) << "MetadataVersion:\t\t" << match.MetadataVersion << std::endl;
  LOG(INFO) << "===================================================================" << std::endl;
}

void
wsdd_event_ProbeMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber,
                        const char *MessageID, const char *RelatesTo, struct wsdd__ProbeMatchesType *matches) {
  if (DiscoveryObj::theDiscovery == NULL) {
    LOG(INFO) << "DiscoveryObj::theDiscovery is NULL. Check why";
  }
  
  if (DiscoveryObj::theDiscovery->mode == CLIENT_MODE) {
    LOG(INFO) << "wsdd_event_ProbeMatches nbMatch:" << matches->__sizeProbeMatch;
    for (int i = 0; i < matches->__sizeProbeMatch; ++i) {
      wsdd__ProbeMatchType &elt = matches->ProbeMatch[i];
      
      //mycode start
      DescDevice device;
      device.metadataversion = elt.MetadataVersion;
      device.types = string(elt.Types);
      device.xAddrs = string(elt.XAddrs);
      wsdd__ScopesType *scope = elt.Scopes;
      if (scope != NULL) {
        device.scopes = string(scope->__item);
      }
      //LOG(INFO)<< "Socopes inside " << device.scopes;
      
      //DiscoveryObj::getDiscoveryObj()->discoveredDevice(device);
      DiscoveryObj::theDiscovery->discoveredDevice(device);
      //my code end
      
      
      printMatch(elt);
    }
  }
  
}

void wsdd_event_ResolveMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId,
                               unsigned int MessageNumber, const char *MessageID, const char *RelatesTo,
                               struct wsdd__ResolveMatchType *match) {
  if (DiscoveryObj::theDiscovery == NULL) {
    LOG(INFO) << "DiscoveryObj::theDiscovery is NULL. Check why";
  }
  if (DiscoveryObj::theDiscovery->mode == CLIENT_MODE) {
    LOG(INFO) << "wsdd_event_ResolveMatches";
    printMatch(*match);
  }
}

void wsdd_event_Hello(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber,
                      const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types,
                      const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int MetadataVersion) {
  LOG(INFO) << "in wsdd_event_Hello";
  LOG(INFO)
    << "wsdd_event_Hello id=" << LOGSTR(MessageID) << " EndpointReference=" << LOGSTR(EndpointReference) << " Types="
    << LOGSTR(Types)
    << " Scopes=" << LOGSTR(Scopes) << " XAddrs=" << LOGSTR(XAddrs);
}

void wsdd_event_Bye(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber,
                    const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types,
                    const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int *MetadataVersion) {
  LOG(INFO) << "in wsdd_event_Bye";
  LOG(INFO)
    << "wsdd_event_Hello id=" << LOGSTR(MessageID) << " EndpointReference=" << LOGSTR(EndpointReference) << " Types="
    << LOGSTR(Types)
    << " Scopes=" << LOGSTR(Scopes) << " XAddrs=" << LOGSTR(XAddrs);
}

soap_wsdd_mode
wsdd_event_Resolve(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *EndpointReference,
                   struct wsdd__ResolveMatchType *match) {
  if (DiscoveryObj::theDiscovery == NULL) {
    LOG(INFO) << "DiscoveryObj::theDiscovery is NULL. Check why";
  }
  if (DiscoveryObj::theDiscovery->mode == SERVER_MODE) {
    LOG(INFO) << "in wsdd_event_Resolve";
    LOG(INFO) << "wsdd_event_Resolve id=" << LOGSTR(MessageID) << " replyTo=" << LOGSTR(ReplyTo) << " endpoint="
              << LOGSTR(EndpointReference);
    if (EndpointReference && (strcmp(EndpointReference, DiscoveryObj::theDiscovery->_endpoint) == 0)) {
      soap_wsdd_ResolveMatches(soap, NULL, soap_wsa_rand_uuid(soap), MessageID, ReplyTo,
                               DiscoveryObj::theDiscovery->_endpoint, DiscoveryObj::theDiscovery->_type,
                               DiscoveryObj::theDiscovery->_scope, NULL, DiscoveryObj::theDiscovery->_xaddr,
                               DiscoveryObj::theDiscovery->_metadataVersion);
    }
    
  }
  return SOAP_WSDD_ADHOC;
}

soap_wsdd_mode
wsdd_event_Probe(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *Types, const char *Scopes,
                 const char *MatchBy, struct wsdd__ProbeMatchesType *matches) {
  if (DiscoveryObj::theDiscovery == NULL) {
    LOG(INFO) << "DiscoveryObj::theDiscovery is NULL. Check why";
  }
  if (DiscoveryObj::theDiscovery->mode == SERVER_MODE) {
    LOG(INFO) << "in wsdd_event_Resolve";
    LOG(INFO) << "wsdd_event_Probe tid = " << LOGSTR(MessageID) << " replyTo = " << LOGSTR(ReplyTo) << " types ="
              << LOGSTR(Types)
              << " scopes =" << LOGSTR(Scopes);
    soap_wsdd_init_ProbeMatches(soap, matches);
    soap_wsdd_add_ProbeMatch(soap, matches, DiscoveryObj::theDiscovery->_endpoint, DiscoveryObj::theDiscovery->_type,
                             DiscoveryObj::theDiscovery->_scope, NULL, DiscoveryObj::theDiscovery->_xaddr,
                             DiscoveryObj::theDiscovery->_metadataVersion);
    //soap_wsdd_add_ProbeMatch(soap, matches, DiscoveryObj::theDiscovery->_endpoint, "", DiscoveryObj::theDiscovery->_scope, NULL, "http://172.16.6.79:8080", DiscoveryObj::theDiscovery->_metadataVersion);
    //type = discows:NetworkVideoTransmitter
    soap_wsdd_ProbeMatches(soap, NULL, soap_wsa_rand_uuid(soap), MessageID, ReplyTo, matches);
    
    
  }
  return SOAP_WSDD_ADHOC;
}
