//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/Messages/DataRequestMessage.msg.
//

#ifndef __DATAREQUESTMESSAGE_M_H
#define __DATAREQUESTMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



class DataRequestMessage;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/Messages/DataRequestMessage.msg:21</tt> by nedtool.
 * <pre>
 * class DataRequestMessage extends inet::FieldsChunk
 * {
 *     int requesterAddress;
 *     string dataId;
 * }
 * </pre>
 */
class DataRequestMessage : public ::inet::FieldsChunk
{
  protected:
    int requesterAddress = 0;
    omnetpp::opp_string dataId;

  private:
    void copy(const DataRequestMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DataRequestMessage&);

  public:
    DataRequestMessage();
    DataRequestMessage(const DataRequestMessage& other);
    virtual ~DataRequestMessage();
    DataRequestMessage& operator=(const DataRequestMessage& other);
    virtual DataRequestMessage *dup() const override {return new DataRequestMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRequesterAddress() const;
    virtual void setRequesterAddress(int requesterAddress);
    virtual const char * getDataId() const;
    virtual void setDataId(const char * dataId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DataRequestMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DataRequestMessage& obj) {obj.parsimUnpack(b);}

#endif // ifndef __DATAREQUESTMESSAGE_M_H

