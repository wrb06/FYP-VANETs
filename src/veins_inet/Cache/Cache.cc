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

#include "Cache.h"

#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;
using namespace omnetpp;

/*
 * Cache source file
 */
Define_Module(Cache);

void Cache::initialize()
{
    // display variables whilst simulation is running
    WATCH(requestsReceived);
    WATCH(requestsAnswered);

    // logging
    this->answerSignal = registerSignal("answer");
    this->receiveSignal = registerSignal("receive");

    this->hitRate = registerSignal("hitRate");
}

void Cache::handleMessage(cMessage *msg)
{
}

Cache::Cache()
{
    csize = 1024;
}

Cache::Cache(int n)
{
    csize = n;
}

void Cache::saveData(string name, string data)
{
    // if not in cache
    if ((hashmap.find(name) == hashmap.end())) {

        // if cache is full
        if (keys.size() == csize) {
            // delete least recently used element
            string last = keys.back();

            // remove from keys
            keys.pop_back();

            // remove from map
            hashmap.erase(last);
        }
    }

    // remove from keys
    else{
        keys.remove(name);
    }

    // update references
    keys.push_front(name);
    hashmap[name] = data;
}


void Cache::display()
{
    // Iterate over the hashmap and print all the elements in it to console
    cout << this->getFullPath() << endl;
    for (auto it = keys.begin(); it != keys.end(); it++){
        cout << "    " << (*it) << " ";
        cout << "    " << hashmap[(*it)] << endl;
    }
    cout << endl;
}

void Cache::finish() {
    // log results on finish
    EV << "Requests Received: " << requestsReceived << endl;
    EV << "Requests Answered: " << requestsAnswered << endl;

    recordScalar("#received", requestsReceived);
    recordScalar("#answered", requestsAnswered);
}

void Cache::setCacheSize(int n){
    csize = n;
}

int Cache::getCacheSize(){
    return csize;
}

bool Cache::containsDataAt(string name) {
    this->increaseRequestCount();
    if(!(hashmap.find(name) == hashmap.end())){
        this->increaseAnswerCount();

        // log hit rate
        emit(this->hitRate, ((float)requestsAnswered)/((float)requestsReceived));
        return true;
    } else {
        // log hit rate
        emit(this->hitRate, ((float)requestsAnswered)/((float)requestsReceived));
        return false;
    }
}

string Cache::getDataAt(string name) {
    return hashmap[name];
}

void Cache::increaseRequestCount() {
    requestsReceived++;

    // log request received
    emit(this->receiveSignal, requestsReceived);
}

void Cache::increaseAnswerCount() {
    requestsAnswered++;

    // log request answered
    emit(answerSignal, requestsAnswered);
}
