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
    // TODO - Generated method body
}

void Cache::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

Cache::Cache()
{
    csize = 10;
}

Cache::Cache(int n)
{
    csize = n;
}

// Refers key x with in the LRU cache
void Cache::refer(int x)
{
    // not present in cache
    if (hashmap.find(x) == hashmap.end()) {
        // cache is full
        if (keys.size() == csize) {
            // delete least recently used element
            int last = keys.back();

            // Pops the last element
            keys.pop_back();

            // Erase the last
            hashmap.erase(last);
        }
    }

    // present in cache
    else
        keys.erase(hashmap[x]);

    // update reference
    keys.push_front(x);
    hashmap[x] = keys.begin();
}


void Cache::display()
{

    // Iterate in the deque and print
    // all the elements in it
    for (auto it = keys.begin(); it != keys.end(); it++)
        cout << (*it) << " ";

    cout << endl;
}
