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

    if(false == BinToValue(&val_))
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
    if(false == BinToValue(&val_))      goto ERROR;
    if(false == ReadChecksum(&cksum_))  goto ERROR;

    file_.reset();
    return true;

ERROR:
    file_.reset();
    return false;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToValue(Value* val)
{
    uint8_t type = Value::INVALID;
    if(false == ReadType(&type))
        return false;

    switch(type)
    {
        case Value::INVALID:    return BinToInvalid(val);
        case Value::BOOLEAN:    return BinToBoolean(val);
        case Value::INT:        return BinToInt(val);
        case Value::UINT:       return BinToUInt(val);
        case Value::FLOAT:      return BinToFloat(val);
        case Value::BINARY:     return BinToBinary(val);
        case Value::STRING:     return BinToString(val);
        case Value::LIST:       return BinToList(val);
        case Value::SET:        return BinToSet(val);
        case Value::ZSET:       return BinToZSet(val);
        case Value::HASH:       return BinToHash(val);

        default:
            assert(0);
    }

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToInvalid(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    static uint8_t invalid = 0;
    if(false == Read(&invalid, sizeof(invalid)))
        return false;

    *val = Value();
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToBoolean(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    bool v;
    if(false == Read(&v, sizeof(bool)))
        return false;

    *val = Value(v);
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToInt(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    int64_t v;
    if(false == Read(&v, sizeof(int64_t)))
        return false;

    *val = Value(v);
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToUInt(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    uint64_t v;
    if(false == Read(&v, sizeof(uint64_t)))
        return false;

    *val = Value(v);
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToFloat(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    double v;
    if(false == Read(&v, sizeof(double)))
        return false;

    *val = Value(v);
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToBinary(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|value|
     */

    //read size
    uint32_t size;
    if(false == ReadSize(&size))
        return false;

    //read val
    Value::Binary bin(size);
    if(false == Read(bin.data(), size))
        return false;
    
    *val = Value(std::move(bin));
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToString(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|value|
     */

    Value::String str;
    if(false == ReadKey(&str))
        return false;
    
    *val = Value(std::move(str));
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToList(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|value|
     */

    //read size
    uint32_t size;
    if(false == ReadSize(&size))
        return false;

    //read value
    Value::List list;
    for(uint32_t i=0; i<size; i++)
    {
        Value v;
        if(false == BinToValue(&v))
            return false;

        list.push_back(std::move(v));
    }

    *val = Value(std::move(list));
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToSet(Value* val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|value|
     */

    //read size
    uint32_t size;
    if(false == ReadSize(&size))
        return false;

    //read value
    Value::Set set;
    for(uint32_t i=0; i<size; i++)
    {
        Value v;
        if(false == BinToValue(&v))
            return false;

        set.insert(std::move(v));
    }

    *val = Value(std::move(set));
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToZSet(Value* val)
{
    //read size

    uint32_t size;
    if(false == ReadSize(&size))
        return false;

    //read values
    Value::ZSet zset;
    for(uint32_t i=0; i<size; i++)
    {
        //read score
        double score;
        if(false == ReadScore(&score))
            return false;

        //read value
        Value v;
        if(false == BinToValue(&v))
            return false;

        zset.emplace(score, std::move(v));
    }

    *val = Value(std::move(zset));
    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::BinToHash(Value* val)
{
    //read size
    uint32_t size;
    if(false == ReadSize(&size))
        return false;

    //read values
    Value::Hash hash;
    for(uint32_t i=0; i<size; i++)
    {
        //read key 
        std::string key;
        if(false == ReadKey(&key))
            return false;

        //read value
        Value v;
        if(false == BinToValue(&v))
            return false;

        hash.emplace(std::move(key), std::move(v));
    }

    *val = Value(std::move(hash));
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
bool UnDump::ReadSize(uint32_t* size)
{
    if(false == Read(size, sizeof(uint32_t)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::ReadScore(double* score)
{
    if(false == Read(score, sizeof(double)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool UnDump::ReadKey(std::string* key)
{
    //read size
    uint32_t size;
    if(false == ReadSize(&size))
        return false;

    //read str
    key->resize(size);
    if(false == Read(const_cast<char*>(key->data()), size))
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
