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
#include "veins_inet/Cache.h"
#include "veins_inet/DataRequestMessage_m.h"
#include "veins_inet/DataReplyMessage_m.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"



#include <string>

using namespace inet;
using namespace std;

Define_Module(VeinsInetSampleApplication);

VeinsInetSampleApplication::VeinsInetSampleApplication()
{
}

bool VeinsInetSampleApplication::startApplication()
{
    cout << "running";

    if (getParentModule()->getIndex() == 1) {
        Cache* cache = (Cache*)(getParentModule()->getSubmodule("cache"));
        cache->refer("test/data1", "testData1");
        cache->refer("test/data2", "testData2");
        cache->display();

    }

    if (getParentModule()->getIndex() == 2) {
        Cache* cache = (Cache*)(getParentModule()->getSubmodule("cache"));
        cache->refer("test/data3", "testData3");
        cache->display();
    }

    // host[0] requests at t=15s
    if (getParentModule()->getIndex() == 0) {
        auto callback = [this]() {

            getParentModule()->getDisplayString().setTagArg("i", 1, "red");

            auto sendPayload = makeShared<DataRequestMessage>();
            timestampPayload(sendPayload);
            sendPayload->setChunkLength(B(100));

            auto sendingPacket = createPacket("cache request");
            sendingPacket->insertAtBack(sendPayload);
            sendPacket(std::move(sendingPacket));



        };
        timerManager.create(veins::TimerSpecification(callback).oneshotAt(SimTime(15, SIMTIME_S)));
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
    if (!strcmp(pk->getName(), "cache request"))
    {
        auto payloadReceived = pk->peekAtFront<DataRequestMessage>();

        EV_INFO << "Received packet: " << payloadReceived << endl;

        getParentModule()->getDisplayString().setTagArg("i", 1, "green");

        auto replyPayload = makeShared<DataReplyMessage>();
        timestampPayload(replyPayload);
        replyPayload->setChunkLength(B(100));

        auto replyPacket = createPacket("reply");
        replyPacket->insertAtBack(replyPayload);
        sendPacket(std::move(replyPacket));
    }
}
