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

#pragma once

#include "veins_inet/veins_inet.h"
#include "veins_inet/Cache/Cache.h"
#include "veins_inet/DataServer/DataServer.h"
#include "veins_inet/VeinsInetApplicationBase.h"

class VEINS_INET_API VeinsInetSampleApplication : public veins::VeinsInetApplicationBase {
protected:
    Cache* cache;
    DataServer* dataServer;

    unordered_map<string, string> availableData = {
            {"/test/dataId1", "Test data one"},
            {"/test/dataId2", "Test data two"},
            {"/test/dataId3", "Test data three"},
            {"/test/dataId4", "Test data four"},
            {"/test/dataId5", "Test data five"},
            {"/test/dataId6", "Test data six"},
            {"/test/dataId7", "Test data seven"},
            {"/test/dataId8", "Test data eight"},
    };

protected:
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;
    virtual void startSearch(string dataId);
    virtual void startExternalSearch(string dataId);
    virtual void processDataRequestMessage(std::shared_ptr<inet::Packet> pk);
    virtual void processDataReplyMessage(std::shared_ptr<inet::Packet> pk);
    virtual void processOtherMessage(std::shared_ptr<inet::Packet> pk);

public:
    VeinsInetSampleApplication();
    ~VeinsInetSampleApplication();
};
