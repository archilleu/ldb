//---------------------------------------------------------------------------
#include "undump.h"
#include "crc64.h"
//#include <memory>
//#include <cstdio>
#include <cstring>
//-----------------------------------------------------------------------------
namespace db
{

namespace
{
    void FileClose(FILE* fp)
    {
        if(0 == fp)
            return;

        fclose(fp);
        fp = 0;
    }

}//namespace
//-----------------------------------------------------------------------------
const char      UnDump::kIDNAME[3]  = {'L','D','B'};
const char      UnDump::kVERSION[4] = {'0','0','0','1'};
const uint8_t   UnDump::kEOF        = 0xFF;
//-----------------------------------------------------------------------------
bool UnDump::FromBin(const Memory& bin)
{
    return FromBin(Memory(bin));
}
//-----------------------------------------------------------------------------
bool UnDump::FromBin(Memory&& bin)
{
    //write bin
    file_or_bin_ = false;
    pos_ = 0;
    bin_ = std::move(bin);

    if(false == ReadIdName(id_name_))                       return false;
    if(false == ReadVersion(version_))                      return false;
    if(0 != memcmp(id_name_, kIDNAME, sizeof(kIDNAME)))     return false;
    if(0 != memcmp(version_, kVERSION, sizeof(kVERSION)))   return false;

    if(false == BinToValue())
        return false;

    uint64_t cksum;
    if(false == ReadChecksum(&cksum))       return false;
    if(enable_cksum_) if(cksum_ != cksum)   return false;

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::FromFile(std::string&& name)
{
    //write file
    file_or_bin_ = true;
    FILE* fp = fopen(name.c_str(), "r");
    if(0 == fp)
        return false;
    file_.reset(fp, FileClose);
    dump_name_ = std::move(name);

    if(false == ReadIdName(id_name_))   goto ERROR;
    if(false == ReadVersion(version_))  goto ERROR;
    if(false == BinToValue())           goto ERROR;
    if(false == ReadChecksum(&cksum_))  goto ERROR;

    file_.reset();
    return true;

ERROR:
    file_.reset();
    return false;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToValue()
{
    uint8_t type = Value::INVALID;
    while(kEOF != type)
    {
        if(false == ReadType(&type))
            return false;

        switch(type)
        {
            case Value::INVALID:
                return BinToInvalid(&val_);

            case Value::BOOLEAN:
                return BinToBoolean(&val_);

            case Value::INT:
            case Value::UINT:
            case Value::FLOAT:
            case Value::BINARY:
            case Value::STRING:
            case Value::LIST:
            case Value::SET:
            case Value::ZSET:
            case Value::HASH:

            default:
                assert(0);
        }

    }

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToInvalid(Value* val)
{
    static uint8_t invalid = 0;
    if(false == Read(&invalid, sizeof(invalid)))
        return false;

    *val = Value();
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToBoolean(Value* val)
{
    bool b;
    if(false == Read(&b, sizeof(bool)))
        return false;

    *val = Value(b);
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::Read(void* buf, size_t len)
{
    if(true == file_or_bin_)
    {
        if(len != fread_unlocked(buf, 1, len, file_.get()))
            return false;
    }
    else
    {
        if(bin_.size() < (pos_+len))
            return false;

        memcpy(buf, bin_.data()+pos_, len);
        pos_ += len;
    }

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::ReadType(uint8_t* type)
{
    if(false == Read(type, sizeof(uint8_t)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::ReadIdName(char id_name[3])
{
    if(false == Read(id_name, sizeof(kIDNAME)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::ReadVersion(char version[4])
{
    if(false == Read(version, sizeof(kVERSION)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::ReadEOF(uint8_t* eof)
{
    if(false == Read(eof, sizeof(uint8_t)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::ReadChecksum(uint64_t* cksum)
{
    if(false == Read(&cksum, sizeof(*cksum)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------

}//namespace db
//-----------------------------------------------------------------------------
