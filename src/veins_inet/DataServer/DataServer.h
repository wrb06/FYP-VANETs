//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __V2V_CACHING_DATASERVER_H_
#define __V2V_CACHING_DATASERVER_H_

#include <omnetpp.h>
#include <unordered_map>
#include "veins_inet/veins_inet.h"
#include "inet/common/packet/Packet.h"
#include "veins_inet/VeinsInetApplicationBase.h"

using namespace omnetpp;
using namespace std;
/**
 * TODO - Generated class
 */
class DataServer : public cSimpleModule
{
private:
    long requestsReceived = 0;
    simsignal_t receiveSignal;
    unordered_map<string, string> hashmap;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

public:
    void display();
    string getDataAt(string name);
    bool containsDataAt(string dataId);
    void refer(string name, string data);
};

#endif
