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

#ifndef __V2V_CACHING_CACHE_H_
#define __V2V_CACHING_CACHE_H_

#include <omnetpp.h>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace omnetpp;

/**
 * Cache header file
 *
 * Replacement Policy : LRU
 * Default size : 1024 items
 */
class Cache : public cSimpleModule
{
protected:
    // implement interface methods
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

private:
    // Cache variables
    list<string> keys;
    unordered_map<string, string> hashmap;
    int csize = 0;

    // logging
    long requestsReceived = 0;
    simsignal_t receiveSignal;

    long requestsAnswered = 0;
    simsignal_t answerSignal;

    simsignal_t hitRate;

    // methods for accurate logging
    void increaseRequestCount();
    void increaseAnswerCount();

public:
    // constructors
    Cache();
    Cache(int n);

    // IO methods
    void saveData(string name, string data);
    void display();
    bool containsDataAt(string name);
    string getDataAt(string name);
    int getCacheSize();
    void setCacheSize(int n);
};

#endif
