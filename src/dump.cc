//---------------------------------------------------------------------------
#include "dump.h"
#include "../depend/base/include/crc64.h"
#include <unistd.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <iostream>
//-----------------------------------------------------------------------------
namespace db
{

namespace
{
    void FileClose(FILE* fp)
    {
        if(0 == fp)
            return;

        fflush(fp);
        syncfs(fileno_unlocked(fp));
        fclose(fp);

        fp = 0;
    }

}//namespace
//-----------------------------------------------------------------------------
const char      Dump::kIDNAME[3]    = {'L','D','B'};
const char      Dump::kVERSION[4]   = {'0','0','0','1'};
const uint8_t   Dump::kEOF          = 0xFF;
//-----------------------------------------------------------------------------
bool Dump::ToBin()
{
    //write bin
    file_or_bin_ = false;
    bin_.clear();

    if(false == WriteIdName())      return false;
    if(false == WriteVersion())     return false;
    if(false == ValueToBin(val_))   return false;
    if(false == WriteChecksum())    return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::ToFile(const std::string& path)
{
    //write file
    file_or_bin_ = true;
    std::string temp_file = path + "-temp";
    FILE* fp = fopen(temp_file.c_str(), "w");
    if(0 == fp)
        return false;
    file_.reset(fp, FileClose);

    if(false == WriteIdName())      goto ERROR;
    if(false == WriteVersion())     goto ERROR;
    if(false == ValueToBin(val_))   goto ERROR;
    if(false == WriteEOF())         goto ERROR;
    if(false == WriteChecksum())    goto ERROR;

    file_.reset();

    //rename file
    if(-1 == rename(temp_file.c_str(), path.c_str()))
        return false;

    return true;

ERROR:
    unlink(temp_file.c_str());
    file_.reset();
    return false;

}
//-----------------------------------------------------------------------------
bool Dump::ValueToBin(const Value& val)
{
    switch(val.type())
    {
        case Value::INVALID:    return InvalidToBin(val);
        case Value::BOOLEAN:    return BooleanToBin(val);
        case Value::INT:        return IntToBin(val);
        case Value::UINT:       return UIntToBin(val);
        case Value::FLOAT:      return FloatToBin(val);
        case Value::BINARY:     return BinaryToBin(val);
        case Value::STRING:     return StringToBin(val);
        case Value::LIST:       return ListToBin(val);
        case Value::SET:        return SetToBin(val);
        case Value::ZSET:       return ZSetToBin(val);
        case Value::HASH:       return HashToBin(val);

        default:
            assert(0);
    }

    return false;
}
//-----------------------------------------------------------------------------
bool Dump::InvalidToBin(const Value& /*val*/)
{
    /*
     * |Value::INVALID(uint8_t)|value|
     */

    if(false == WriteType(Value::INVALID))
        return false;

    static const uint8_t invalid = 0;
    if(false == Write(&invalid, sizeof(invalid)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::BooleanToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    if(false == WriteType(Value::BOOLEAN))
        return false;

    bool v = val.GetBoolean();
    if(false == Write(&v, sizeof(bool)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::IntToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    if(false == WriteType(Value::INT))
        return false;

    int64_t v = val.GetInt();
    if(false == Write(&v, sizeof(int64_t)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::UIntToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    if(false == WriteType(Value::UINT))
        return false;

    uint64_t v = val.GetUInt();
    if(false == Write(&v, sizeof(uint64_t)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::FloatToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|value|
     */

    if(false == WriteType(Value::FLOAT))
        return false;

    double v = val.GetFloat();
    if(false == Write(&v, sizeof(double)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::BinaryToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|value|
     */

    if(false == WriteType(Value::BINARY))
        return false;
    
    const auto& v = val.GetBinary();

    //write size
    if(false == WriteSize(static_cast<uint32_t>(v.size())))
        return false;

    //write value
    if(false == Write(v.data(), v.size()))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::StringToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|value|
     */

    if(false == WriteType(Value::STRING))
        return false;

    const auto& v = val.GetString();

    //write size
    if(false == WriteSize(static_cast<uint32_t>(v.size())))
        return false;

    //write value
    if(false == Write(v.c_str(), v.length()))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::ListToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|Value|
     */

    if(false == WriteType(Value::LIST))
        return false;

    const auto& list  = val.GetList();
    if(false == WriteSize(static_cast<uint32_t>(list.size())))
        return false;

    for(const auto& v : list)
        ValueToBin(v);

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::SetToBin(const Value& val)
{
    /*
     * |Value::TYPE(uint8_t)|size(uint32_t)|Value|
     */

    if(false == WriteType(Value::SET))
        return false;

    const auto& set = val.GetSet();
    if(false == WriteSize(static_cast<uint32_t>(set.size())))
        return false;

    for(const auto& v : set)
        ValueToBin(v);

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::ZSetToBin(const Value& val)
{
    /*
     * |Value::ZSET(uint8_t)|size(uint32_t)|double|Value|
     */

    if(false == WriteType(Value::ZSET))
        return false;

    const auto& zset = val.GetZSet();
    if(false == WriteSize(static_cast<uint32_t>(zset.size())))
        return false;

    for(const auto& v : zset)
    {
        //write score value
        if(false == WriteScore(v.first))
            return false;

        //write value;
        if(false == ValueToBin(v.second))
            return false;
    }
    
    return true;;
}
//-----------------------------------------------------------------------------
bool Dump::HashToBin(const Value& val)
{
    /*
     * |Value::HASH(uint8_t)|size(uint32_t)|String|Value|
     */

    if(false == WriteType(Value::HASH))
        return false;

    const auto& hash = val.GetHash();
    if(false == WriteSize(static_cast<uint32_t>(hash.size())))
        return false;

    for(const auto& v : hash)
    {
        //write key
        if(false == WriteKey(v.first))
            return false;

        //write value;
        if(false == ValueToBin(v.second))
            return false;
    }
    
    return true;;
}
//-----------------------------------------------------------------------------
bool Dump::Write(const void* buf, size_t len)
{
    if(enable_cksum_)
        cksum_ = crc64(cksum_, static_cast<const unsigned char*>(buf), static_cast<uint64_t>(len));

    if(true == file_or_bin_)
    {
        if(len != fwrite_unlocked(buf, 1, len, file_.get()))
            return false;
    }
    else
    {
        const unsigned char* arr = static_cast<const unsigned char*>(buf);
        bin_.insert(bin_.end(), arr, arr+len);
    }

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::WriteType(uint8_t type)
{
    return Write(&type, sizeof(uint8_t));
}
//-----------------------------------------------------------------------------
bool Dump::WriteSize(uint32_t len)
{
    return Write(&len, sizeof(uint32_t));
}
//-----------------------------------------------------------------------------
bool Dump::WriteScore(double score)
{
    return Write(&score, sizeof(double));
}
//-----------------------------------------------------------------------------
bool Dump::WriteKey(const std::string& key)
{
    //write key len
    uint32_t size = static_cast<uint32_t>(key.size());
    if(false == Write(&size, sizeof(uint32_t)))
        return false;

    //write val
    if(false == Write(key.data(), key.length()))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::WriteIdName()
{
    return Write(kIDNAME, sizeof(kIDNAME));
}
//-----------------------------------------------------------------------------
bool Dump::WriteVersion()
{
    return Write(kVERSION, sizeof(kVERSION));
}
//-----------------------------------------------------------------------------
bool Dump::WriteEOF()
{
    return Write(&kEOF, sizeof(kEOF));
}
//-----------------------------------------------------------------------------
bool Dump::WriteChecksum()
{
    return Write(&cksum_, sizeof(cksum_));
}
//-----------------------------------------------------------------------------

}//namespace db
//-----------------------------------------------------------------------------
