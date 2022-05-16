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

/*
 * The application that the vehicles run, it contains the main logic for the
 * request -> reply algorithm, but is spread out due to the event based nature
 * of the system.
 */

class VEINS_INET_API VeinsInetVehicleApplication : public veins::VeinsInetApplicationBase {
private:
    // default caching to true
    bool cachingEnabled = true;

protected:
    // store pointers for ease of use
    Cache* cache;
    DataServer* dataServer;

    // logging variables
    vector<pair<string, simtime_t>> requests;
    simsignal_t packetReceivedTime;

    // data for logging
    unordered_map<string, string> availableData = {
            {"/test/dataId_0", "Test data zero"},
            {"/test/dataId_1", "Test data one"},
            {"/test/dataId_2", "Test data two"},
            {"/test/dataId_3", "Test data three"},
            {"/test/dataId_4", "Test data four"},
            {"/test/dataId_5", "Test data five"},
            {"/test/dataId_6", "Test data six"},
            {"/test/dataId_7", "Test data seven"},
            {"/test/dataId_8", "Test data eight"},
            {"/test/dataId_9", "Test data nine"},
            {"/test/dataId_A", "Test data a"},
            {"/test/dataId_B", "Test data b"},
            {"/test/dataId_C", "Test data c"},
            {"/test/dataId_D", "Test data d"},
            {"/test/dataId_E", "Test data e"},
            {"/test/dataId_F", "Test data f"},
    };
    // override methods
    virtual bool startApplication() override;
    virtual bool stopApplication() override;
    virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;
    virtual void initialize();

    // searching helper methods
    virtual void startSearch(string dataId);
    virtual void startExternalSearch(string dataId);

    // Process messages
    virtual void processDataRequestMessage(std::shared_ptr<inet::Packet> pk);
    virtual void processDataReplyMessage(std::shared_ptr<inet::Packet> pk);
    virtual void processOtherMessage(std::shared_ptr<inet::Packet> pk);

    // logging methods
    virtual void logReceived(string dataId);
    virtual void logStarted(string dataId);

    virtual void setupDemoNode();
    virtual void setupStandardNode();
public:
    VeinsInetVehicleApplication();
    ~VeinsInetVehicleApplication();
};
