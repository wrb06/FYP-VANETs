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

Define_Module(Cache);

void Cache::initialize()
{
    WATCH(requestsReceived);
    WATCH(requestsAnswered);

    this->answerSignal = registerSignal("answer");
    this->receiveSignal = registerSignal("receive");

    this->hitRate = registerSignal("hitRate");
}

void Cache::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

Cache::Cache()
{
    csize = 1000;
}

Cache::Cache(int n)
{
    csize = n;
}

void Cache::refer(string name, string data)
{
    // not present in cache
    if ((hashmap.find(name) == hashmap.end())) {
        // cache is full
        if (keys.size() == csize) {
            // delete least recently used element
            string last = keys.back();

            // Pops the last element
            keys.pop_back();

            // Erase the last
            hashmap.erase(last);
        }
    }

    // present in cache
    else{
        keys.remove(name);
    }

    // update reference
    keys.push_front(name);
    hashmap[name] = data;
}


void Cache::display()
{

    // Iterate over the hashmap and print all the elements in its
    cout << this->getFullPath() << endl;
    for (auto it = keys.begin(); it != keys.end(); it++){
        cout << "    " << (*it) << " ";
        cout << "    " << hashmap[(*it)] << endl;
    }
    cout << endl;
}

void Cache::finish() {
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
        emit(this->hitRate, ((float)requestsAnswered)/((float)requestsReceived));
        return true;
    } else {
        emit(this->hitRate, ((float)requestsAnswered)/((float)requestsReceived));
        return false;
    }
}

string Cache::getDataAt(string name) {
    return hashmap[name];
}

void Cache::increaseRequestCount() {
    requestsReceived++;

    emit(this->receiveSignal, requestsReceived);
}

void Cache::increaseAnswerCount() {
    requestsAnswered++;

    emit(answerSignal, requestsAnswered);
}
