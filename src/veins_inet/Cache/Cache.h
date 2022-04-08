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

using namespace omnetpp;
using namespace std;
/**
 * TODO - Generated class
 */
class Cache : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    list<string> keys;
    unordered_map<string, string> hashmap;
    int csize = 0;

  public:
      Cache();
      Cache(int n);
      void refer(string name, string data);
      void display();
      bool containsDataAt(string name);
      string getDataAt(string name);
      int getCacheSize();
      void setCacheSize(int n);
};

#endif
