#ifndef _REQUESTLOGBOOK_H
#define _REQUESTLOGBOOK_H

#include "F4vu.h"
#include "FalcMesg.h"
#include "mission.h"
#include "InvalidBufferException.h"

#pragma pack (1)

/*
 * Message Type Request Logbook
 */
class UI_RequestLogbook : public FalconEvent
{
public:
    UI_RequestLogbook(VU_ID entityId, VuTargetEntity *target, VU_BOOL loopback = TRUE);
    UI_RequestLogbook(VU_MSG_TYPE type, VU_ID senderid, VU_ID target);
    ~UI_RequestLogbook(void);
    virtual int Size() const
    {
        return sizeof(dataBlock) + FalconEvent::Size();
    };
    //sfr: changed to long*
    int Decode(VU_BYTE **buf, long *rem)
    {
        long init = *rem;
        FalconEvent::Decode(buf, rem);
        memcpychk(&dataBlock, buf, sizeof(dataBlock), rem);
        return init - *rem;
    }
    int Encode(VU_BYTE **buf)
    {
        int size;
        size = FalconEvent::Encode(buf);
        memcpy(*buf, &dataBlock, sizeof(dataBlock));
        *buf += sizeof(dataBlock);
        size += sizeof(dataBlock);
        return size;
    }
    class DATA_BLOCK
    {
    public:
        VU_ID fromID;
    } dataBlock;

protected:
    int Process(uchar autodisp);
};

#pragma pack ()

#endif
