//---------------------------------------------------------------------------
#include "dump.h"
#include "crc64.h"
#include <unistd.h>
#include <memory>
#include <cstdio>
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
bool Dump::ToFile()
{
    //write file
    file_or_bin_ = true;
    std::string temp_file = "temp-" + dump_name_;
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
    if(-1 == rename(temp_file.c_str(), dump_name_.c_str()))
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
        case Value::INVALID:
            return InvalidToBin(val);

        case Value::BOOLEAN:
            return BooleanToBin(val);

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

    return false;
}
//-----------------------------------------------------------------------------
bool Dump::InvalidToBin(const Value& val)
{
    (void)val;
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
    if(false == WriteType(Value::BOOLEAN))
        return false;

    if(false == Write(&val, sizeof(bool)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::IntToBin(const Value& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::UIntToBin(const Value& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::FloatToBin(const Value& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::StringToBin(const Value& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::ListToBin(const Value& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::SetToBin(const Value& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::ZSetToBin(const Value& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::HashToBin(const Value& val)
{
    (void)val;
    return 1;
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
