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

#ifndef VEINS_INET_CLASSIFIERS_CARCLASSIFIER_H_
#define VEINS_INET_CLASSIFIERS_CARCLASSIFIER_H_

#include "inet/queueing/contract/IPacketClassifierFunction.h"

using namespace inet;

class CarClassifier : public inet::queueing::IPacketClassifierFunction, public cObject{
public:
    CarClassifier();
    virtual ~CarClassifier();

    virtual int classifyPacket(Packet *packet) const;
};


#endif /* VEINS_INET_CLASSIFIERS_CARCLASSIFIER_H_ */
