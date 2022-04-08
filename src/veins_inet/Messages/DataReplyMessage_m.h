//
// Generated file, do not edit! Created by nedtool 5.6 from veins_inet/Messages/DataReplyMessage.msg.
//

#ifndef __DATAREPLYMESSAGE_M_H
#define __DATAREPLYMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



class DataReplyMessage;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/Messages/DataReplyMessage.msg:18</tt> by nedtool.
 * <pre>
 * class DataReplyMessage extends inet::FieldsChunk
 * {
 *     string requesterAddress;
 *     string dataId;
 *     string data;
 * }
 * </pre>
 */
class DataReplyMessage : public ::inet::FieldsChunk
{
  protected:
    omnetpp::opp_string requesterAddress;
    omnetpp::opp_string dataId;
    omnetpp::opp_string data;

  private:
    void copy(const DataReplyMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DataReplyMessage&);

  public:
    DataReplyMessage();
    DataReplyMessage(const DataReplyMessage& other);
    virtual ~DataReplyMessage();
    DataReplyMessage& operator=(const DataReplyMessage& other);
    virtual DataReplyMessage *dup() const override {return new DataReplyMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getRequesterAddress() const;
    virtual void setRequesterAddress(const char * requesterAddress);
    virtual const char * getDataId() const;
    virtual void setDataId(const char * dataId);
    virtual const char * getData() const;
    virtual void setData(const char * data);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DataReplyMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DataReplyMessage& obj) {obj.parsimUnpack(b);}

#endif // ifndef __DATAREPLYMESSAGE_M_H

