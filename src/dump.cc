//---------------------------------------------------------------------------
#include <cassert>
#include "../thirdpart/base/include/function.h"
#include "../thirdpart/base/include/thread.h"
#include "../thirdpart/base/include/crc64.h"
#include "defines.h"
#include "dump.h"

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
Dump::Dump(Server& server)
:   server_(server)
{
    checksum_ = 0;
}
//---------------------------------------------------------------------------
bool Dump::Save(const std::string& path)
{
    try
    {
        std::string tmp_file = MakeTempFilename();
        file_.Open(tmp_file);

        WriteIdName();
        WriteVersion();

        /**
         * data
         * SELECTEDB|db_number|key_value_pairs
         */
        for(size_t i=0; i<server_.dbs().size(); i++)
        {
            HashValue& db = server_.dbs()[i];
            if(true == db.Empty())
                continue;

            //写入DB opcode
            WriteType(kLDB_OPCODE_SELECTDB);
            WriteSize(static_cast<uint32_t>(i));

            //遍历数据库，写入key value
            for(auto it=db.Begin(); db.End()!=it; ++it)
            {
                SaveKeyValuePair(it->first, it->second);
            }
        }
        //写入DB EOF
        WriteType(kLDB_OPCODE_EOF);
        
        WriteEOF();
        WriteChecksum();

        file_.Close();

        if(-1 == rename(tmp_file.c_str(), path.c_str()))
        {
            unlink(tmp_file.c_str());
            return false;
        }
    }
    catch(std::exception e)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
std::string Dump::MakeTempFilename() const
{
    return base::CombineString("temp-%d.ldb", base::CurrentThread::tid());
}
//---------------------------------------------------------------------------
void Dump::Write(const void* dat, size_t len)
{
    file_.Write(dat, len);
    checksum_ = base::crc64(checksum_, reinterpret_cast<const unsigned char*>(dat), len);

    return;
}
//---------------------------------------------------------------------------
void Dump::WriteType(uint8_t type)
{
    Write(&type, sizeof(type));
}
//---------------------------------------------------------------------------
void Dump::WriteSize(uint32_t len)
{
    Write(&len, sizeof(len));
}
//---------------------------------------------------------------------------
void Dump::WriteScore(double score)
{
    Write(&score, sizeof(score));
}
//---------------------------------------------------------------------------
void Dump::WriteInt(int64_t val)
{
    Write(&val, sizeof(val));
}
//---------------------------------------------------------------------------
void Dump::WriteKey(const std::string& key)
{
    WriteSize(static_cast<uint32_t>(key.length()));
    Write(key.data(), key.length());
}
//---------------------------------------------------------------------------
void Dump::WriteIdName()
{
    Write(kLDB_NAME, sizeof(kLDB_NAME));
}
//---------------------------------------------------------------------------
void Dump::WriteVersion()
{
    Write(kLDB_VERSION, sizeof(kLDB_VERSION));
}
//---------------------------------------------------------------------------
void Dump::WriteEOF()
{
    WriteType(kLDB_EOF);
}
//---------------------------------------------------------------------------
void Dump::WriteChecksum()
{
    WriteInt(checksum_);
}
//---------------------------------------------------------------------------
void Dump::SaveKeyValuePair(const std::string& key, const ObjectPtr& value)
{
    /**
     * type|key|value
     */

    //保存类型
    SaveType(value);
    
    //保存键
    SaveKey(key);

    //保存值
    SaveValue(value);
}
//---------------------------------------------------------------------------
void Dump::SaveType(const ObjectPtr& value)
{
    switch(value.object()->type())
    {
        case Value::Type::STRING:
            WriteType(kLDB_TYPE_STRING);
            break;

        case Value::Type::HASH:
            WriteType(kLDB_TYPE_HASH);
            break;

        case Value::Type::LIST:
            WriteType(kLDB_TYPE_LIST);
            break;
        case Value::Type::SET:
            WriteType(kLDB_TYPE_SET);
            break;
        case Value::Type::ZSET:
            WriteType(kLDB_TYPE_ZSET);
            break;

        default:
            assert(0);
    }
}
//---------------------------------------------------------------------------
void Dump::SaveKey(const std::string& key)
{
    /**
     * len|str
     */
    WriteSize(static_cast<uint32_t>(key.size()));
    Write(key.data(), key.size());
}
//---------------------------------------------------------------------------
void Dump::SaveValue(const ObjectPtr& value)
{
    switch(value.object()->type())
    {
        case Value::Type::STRING:
            SaveValueString(value);
            break;

        case Value::Type::HASH:
            break;

        case Value::Type::LIST:
            break;
        case Value::Type::SET:
            break;
        case Value::Type::ZSET:
            break;

        default:
            assert(0);
    }
}
//---------------------------------------------------------------------------
void Dump::SaveValueString(const ObjectPtr& value)
{
    /**
     * |-----8bit----|
     * encode|zip|len|string
     */

    uint32_t len = 0;
    StringValuePtr ptr = value.AsStringPtr();
    if(Value::Encoding::INT == ptr->encoding())
    {
        //高位32表示INT
        len |= 1<<31;
        WriteSize(len);
        int64_t val = ptr->AsInt();
        Write(&val, sizeof(val));
    }
    else
    {
        if(false)
        {
            //高位31表示压缩
            len &= 1<<30;
        }

        const char* str = ptr->val();
        uint32_t size = static_cast<uint32_t>(std::strlen(str));
        len |= size;
        WriteSize(len);
        Write(str, size);
    }

    return;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
