//---------------------------------------------------------------------------
#include <cassert>
//TODO:del
#include <iostream>

#include "defines.h"
#include "undump.h"
#include "../thirdpart/base/include/function.h"
#include "../thirdpart/base/include/crc64.h"

#include "object_ptr.h"
#include "string_value.h"
#include "hash_value.h"
#include "list_value.h"
#include "set_value.h"
#include "zset_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
Undump::Undump(Server& server)
:   server_(server),
    buffer_(1024*1024),
    checksum_(0)
{
}
//---------------------------------------------------------------------------
bool Undump::Load(const std::string& path)
{
    try
    {
        file_.Open(path);

        if(false == CheckIdName())  return false;
        if(false == CheckVersion()) return false;

        //load data
        Load();
        
        if(false == CheckEOF())     return false;
        if(false == CheckChecksum())return false;

        file_.Close();

    }
    catch(std::exception e)
    {
        return false;
    }

    std::cout << server_.dbs()[0].ToString() << std::endl;;
    return true;
}
//---------------------------------------------------------------------------
void Undump::Read(size_t len)
{
    MakeSureSize(len);

    if(len != file_.Read(const_cast<char*>(buffer_.data()), len))
        throw std::runtime_error("read file failed");

    checksum_ = base::crc64(checksum_, reinterpret_cast<const unsigned char*>(buffer_.data()), len);

    return;
}
//---------------------------------------------------------------------------
uint8_t Undump::ReadType()
{
    Read(sizeof(uint8_t));
    return buffer_.front();
}
//---------------------------------------------------------------------------
uint32_t Undump::ReadSize()
{
    Read(sizeof(uint32_t));
    return *reinterpret_cast<uint32_t*>(const_cast<char*>((buffer_.data())));
}
//---------------------------------------------------------------------------
double Undump::ReadScore()
{
    Read(sizeof(double));
    return *reinterpret_cast<double*>(const_cast<char*>((buffer_.data())));
}
//---------------------------------------------------------------------------
int64_t Undump::ReadInt()
{
    Read(sizeof(int64_t));
    return *reinterpret_cast<int64_t*>(const_cast<char*>((buffer_.data())));
}
//---------------------------------------------------------------------------
bool Undump::CheckIdName()
{
    Read(sizeof(kLDB_NAME));
    if(0 != memcmp(kLDB_NAME, buffer_.data(), sizeof(kLDB_NAME)))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool Undump::CheckVersion()
{
    Read(sizeof(kLDB_VERSION));
    if(0 != memcmp(kLDB_VERSION, buffer_.data(), sizeof(kLDB_VERSION)))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool Undump::CheckEOF()
{
    Read(sizeof(kLDB_EOF));
    if(0 != memcmp(&kLDB_EOF, buffer_.data(), sizeof(kLDB_EOF)))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool Undump::CheckChecksum()
{
    if(sizeof(int64_t) != file_.Read(const_cast<char*>(buffer_.data()), sizeof(int64_t)))
        throw std::runtime_error("read file failed");

    int64_t checksum = *reinterpret_cast<int64_t*>(const_cast<char*>((buffer_.data())));
    if(checksum_ != checksum)
        return false;

    return true;
}
//---------------------------------------------------------------------------
void Undump::MakeSureSize(size_t size)
{
    if(size > buffer_.size())
        buffer_.resize(size *2);

    return;
}
//---------------------------------------------------------------------------
void Undump::Load()
{
    while(true)
    {
        uint8_t type = ReadType();
        if(kLDB_OPCODE_EXPIRETIME == type)
        {
            //TODO:处理过期时间
        }
        else if(kLDB_OPCODE_EXPIRETIME == type)
        {
            //TODO:处理过期时间
        }

        //读取kv结束
        if(kLDB_OPCODE_EOF == type)
            break;

        //选取数据库
        if(kLDB_OPCODE_SELECTDB == type) 
        {
            uint32_t size = ReadSize();
            server_.set_cur_db_idx(size);
            continue;
        }

        /**
         * 读入kv
         */
        LoadKeyValuePair(type, server_.cur_db());
    }

    return;
}
//---------------------------------------------------------------------------
void Undump::LoadKeyValuePair(uint8_t type, HashValue& hash)
{
    //获取键
    std::string key = LoadKey();

    //获取值
    ObjectPtr value = LoadValue(type);

    hash.Insert(std::move(key), std::move(value));

    return;
}
//---------------------------------------------------------------------------
std::string Undump::LoadKey()
{
    size_t size = ReadSize();
    Read(size);
    std::string key(buffer_.data(), size);
    return key;
}
//---------------------------------------------------------------------------
ObjectPtr Undump::LoadValue(uint8_t type)
{
    switch(type)
    {
        case Value::Type::STRING:
            return LoadValueString();

        case Value::Type::HASH:

        case Value::Type::LIST:
        case Value::Type::SET:
        case Value::Type::ZSET:

        default:
            throw std::runtime_error("read file failed");
    }
}
//---------------------------------------------------------------------------
ObjectPtr Undump::LoadValueString()
{
    /**
     * |----32bit----|
     * encode|zip|len|string
     */

    uint32_t size = ReadSize();
    //高位32表示INT
    if(size&0x80000000)
    {
        int64_t val = ReadInt();
        ObjectPtr op = MakeObject<StringValue>(val);
        return op;
    }
    else
    {
        //高位31表示压缩
        if(size&0x40000000)
        {
            //TODO:
        }
        uint32_t len = (0x3FFFFFFFFF & size);
        Read(len);
        std::string val(buffer_.data(), len);
        ObjectPtr op = MakeObject<StringValue>(std::move(val));
        return op;
    }
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
