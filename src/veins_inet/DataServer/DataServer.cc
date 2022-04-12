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
    // TODO - Generated method body12
}

void DataServer::handleMessage(cMessage *msg)
{
    auto mainApp = getParentModule()->getSubmodule("app", 0);
    cout << mainApp->getFullPath() << endl;

    auto replyPayload = makeShared<DataReplyMessage>();
    replyPayload->setRequesterAddress("rad");
    replyPayload->setData("data");
    replyPayload->setChunkLength(B(512));
    replyPayload->setDataId("dataid");

    // send message
    auto replyPacket = new Packet("cache reply");
    replyPacket->insertAtBack(replyPayload);
    replyPacket->addTag<inet::L3AddressInd>();


    sendDirect(replyPacket, mainApp->gate("messagesIn"));

}

string DataServer::getDataAt(string name){
    return name;
}
