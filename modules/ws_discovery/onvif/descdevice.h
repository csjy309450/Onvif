#ifndef DESCDEVICE_H
#define DESCDEVICE_H

#include <string>

using namespace std;

struct DescDevice{
    int metadataversion;
    string types;
    string xAddrs;
    string scopes;
};

#endif // DESCDEVICE_H

