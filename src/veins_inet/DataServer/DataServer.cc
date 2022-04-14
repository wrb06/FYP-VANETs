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

#include "DataServer.h"

#include <unordered_map>
#include <string>
#include <iostream>

#include "veins_inet/veins_inet.h"
#include "inet/common/ModuleAccess.h"
#include "veins_inet/Messages/DataRequestMessage_m.h"
#include "veins_inet/Messages/DataReplyMessage_m.h"
#include "veins_inet/VeinsInetApplicationBase.h"
#include "inet/networklayer/common/L3AddressTag_m.h"

Define_Module(DataServer);

using namespace inet;

void DataServer::initialize()
{
    this->receiveSignal = registerSignal("receive");
}

void DataServer::handleMessage(cMessage *msg)
{
    emit(this->receiveSignal, ++requestsReceived);

    // receive a request
    Packet* pk = check_and_cast<Packet*>(msg);
    auto payloadReceived = pk->peekAtFront<DataRequestMessage>();
    delete msg;

    auto mainApp = getParentModule()->getSubmodule("app", 0);
    auto replyPayload = makeShared<DataReplyMessage>();

    replyPayload->setRequesterAddress(payloadReceived->getRequesterAddress());
    replyPayload->setChunkLength(B(512));
    replyPayload->setDataId(payloadReceived->getDataId());
    if (this->containsDataAt(payloadReceived->getDataId()))
    {
        replyPayload->setData(getDataAt(payloadReceived->getDataId()).c_str());
    }
    if (strcmp(payloadReceived->getRequesterAddress(), getParentModule()->getFullPath().c_str())){
        replyPayload->setBroadcast(true);
    }

    // send message
    auto replyPacket = new Packet("cache reply");
    replyPacket->insertAtBack(replyPayload);
    replyPacket->addTag<inet::L3AddressInd>();

    sendDirect(replyPacket, SimTime(rand()%100, SIMTIME_MS), SimTime(rand()%100, SIMTIME_MS),  mainApp->gate("messagesIn"));

}

string DataServer::getDataAt(string name){
    return hashmap[name];
}

bool DataServer::containsDataAt(string dataId) {
    return !(hashmap.find(dataId) == hashmap.end());
}

void DataServer::display() {
    // Iterate over the hashmap and print all the elements in it
    cout << this->getFullPath() << endl;
    for (auto it = hashmap.begin(); it != hashmap.end(); ++it){
        cout<<"    " <<it->first << " " << it->second << endl;
    }
    cout << endl;
}

void DataServer::refer(string name, string data) {
    hashmap[name] = data;
}
