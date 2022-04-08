//
// Copyright (C) 2018 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "veins_inet/VeinsInetSampleApplication.h"
#include "veins_inet/Cache/Cache.h"
#include "veins_inet/Messages/DataRequestMessage_m.h"
#include "veins_inet/Messages/DataReplyMessage_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/queueing/classifier/PacketClassifier.h"

#include <string>

using namespace inet;
using namespace std;

Define_Module(VeinsInetSampleApplication);

#define myAddress getParentModule()->getFullPath()

VeinsInetSampleApplication::VeinsInetSampleApplication()
{
}

bool VeinsInetSampleApplication::startApplication()
{
    cache = (Cache*)(getParentModule()->getSubmodule("cache"));

    // setup cache
    switch (getParentModule()->getIndex()){
        case 0:
            cache->refer("test/data1", "testData1");
            cache->refer("test/data2", "testData2");
            cache->refer("test/data3", "testData3");
            break;
        case 1:
            cache->refer("test/data1", "testData1");
            cache->refer("test/data2", "testData2");
            cache->refer("test/data3", "testData3");
            break;
        case 2:
            cache->refer("test/data1", "testData1");
            cache->refer("test/data2", "testData2");
            cache->refer("test/data3", "testData3");
            break;
        default:
            break;
    }
    cache->display();

    // host[0] requests at t=16s
    if (getParentModule()->getIndex() == 1) {
        auto callback = [this]() {

            getParentModule()->getDisplayString().setTagArg("i", 1, "red");

            auto sendPayload = makeShared<DataRequestMessage>();
            auto sendingPacket = createPacket("cache request");

            timestampPayload(sendPayload);
            sendPayload->setChunkLength(B(512));
            sendPayload->setRequesterAddress(myAddress.c_str());
            sendPayload->setDataId("test/data3");

            sendingPacket->insertAtBack(sendPayload);
            sendPacket(std::move(sendingPacket));



        };
        timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(16, SIMTIME_S)));
    }

    return true;
}

bool VeinsInetSampleApplication::stopApplication()
{
    return true;
}

VeinsInetSampleApplication::~VeinsInetSampleApplication()
{
}



void VeinsInetSampleApplication::processPacket(std::shared_ptr<inet::Packet> pk)
{
    //
    // To Do: better packet detection
    //
    if (!strcmp(pk->peekData()->getClassName(), "DataRequestMessage")){
        // disassemble packet
        auto payloadReceived = pk->peekAtFront<DataRequestMessage>();
        string requesterAddress = payloadReceived->getRequesterAddress();
        string dataId = payloadReceived->getDataId();

        // log received message
        cout << "Host: " << myAddress << " Received packet: " << payloadReceived << " From: " << requesterAddress  <<  " Requesting: " << dataId << endl;

        // ignore our requests
        if (!strcmp(myAddress.c_str(), requesterAddress.c_str())) {
            cout << "discarding - own request" << endl;
        } else if (cache->containsDataAt(payloadReceived->getDataId())){
            cout << "in my cache" << endl;
            // if its in the cache generate a reply message
            auto replyPayload = makeShared<DataReplyMessage>();
            timestampPayload(replyPayload);
            replyPayload->setRequesterAddress(requesterAddress.c_str());
            replyPayload->setData(cache->getDataAt(dataId.c_str()).c_str());
            replyPayload->setChunkLength(B(512));
            replyPayload->setDataId(dataId.c_str());

            // send message
            auto replyPacket = createPacket("cache reply");
            replyPacket->insertAtBack(replyPayload);
            sendPacket(std::move(replyPacket));
            cout << "reply sent" << endl;
        } else {
            cout << "not in my cache" << endl;
        }
        cout << endl;
    } else if (!strcmp(pk->peekData()->getClassName(), "DataReplyMessage")){
        // disassemble packet
        auto payloadReceived = pk->peekAtFront<DataReplyMessage>();
        string requesterAddress = payloadReceived->getRequesterAddress();
        string dataId = payloadReceived->getDataId();
        string data = payloadReceived->getData();

        // log received message
        cout << "Host: " << myAddress << " Received packet: " << payloadReceived << " From: " << requesterAddress <<  " Requesting: " << dataId << " Data: " << data << endl;

        // ignore replies not for ourself
        if (strcmp(myAddress.c_str(), payloadReceived->getRequesterAddress())) {
            cout << "discarding - not for me" << endl;
        } else {
            cout << "for me - saving in my cache" << endl;
            // save in the cache
            cache->refer(dataId, data);
            cache->display();
            return;
        }
        cout << endl;
    }
}
