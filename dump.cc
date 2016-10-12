//---------------------------------------------------------------------------
#include "dump.h"
#include "crc64.h"
#include <unistd.h>
#include <memory>
#include <cstdio>
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
const char Dump::kIDNAME[3]     = {'L','D','B'};
const char Dump::kVERSION[4]    = {'0','0','0','1'};
const unsigned char Dump::kEOF  = 0xFF;
//-----------------------------------------------------------------------------
bool Dump::ToBin(std::vector<unsigned char>* bin)
{
    (void)bin;
    std::string temp_file = "temp-" + dump_name_ + ".ldb";
    FILE* fp = fopen(temp_file.c_str(), "w");
    if(0 == fp)
        return false;
    file_.reset(fp, FileClose);



    //uint64_t cksum = 0;


//ERROR:
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
        case Value::BOOLEAN:
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

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::InvalidToBin()
{
    if(sizeof(uint8_t) != WriteType(Value::INVALID))
        return false;

    static const uint8_t invalid = 0;
    if(sizeof(invalid) != Write(&invalid, sizeof(invalid)))
        return false;

    return true;
}
//-----------------------------------------------------------------------------
bool Dump::BooleanToBin(bool val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::IntToBin(int64_t val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::UIntToBin(uint64_t val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::FloatToBin(float val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::StringToBin(const Value::String& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::ListToBin(const Value::List& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::SetToBin(const Value::Set& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::ZSetToBin(const Value::ZSet& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::HashToBin(const Value::Hash& val)
{
    (void)val;
    return 1;
}
//-----------------------------------------------------------------------------
bool Dump::Write(const void* buf, size_t len)
{
    if(enable_cksum_)
        cksum_ = crc64(cksum_, static_cast<const unsigned char*>(buf), static_cast<uint64_t>(len));

    return fwrite_unlocked(buf, 1, len, file_.get());
}
//-----------------------------------------------------------------------------
bool Dump::WriteType(uint8_t type)
{
    return Write(&type, sizeof(uint8_t));
}
//-----------------------------------------------------------------------------

}//namespace db
//-----------------------------------------------------------------------------
