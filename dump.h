//---------------------------------------------------------------------------
#ifndef DB_DUMP_H_
#define DB_DUMP_H_
//---------------------------------------------------------------------------
/*
 * ldb bin format
 * |IDNAME|VERSION|db data|EOF|cksum|
 */
//---------------------------------------------------------------------------
#include "value.h"
#include <memory>
//-----------------------------------------------------------------------------
namespace db
{

//-----------------------------------------------------------------------------
class Dump 
{
public:
    Dump()
    :   cksum_(0),
        enable_cksum_(false)
    {
    }

    bool ToBin(std::vector<unsigned char>* bin);

    void set_enable_cksum_(bool enable) { enable_cksum_ = enable; }
    bool enable_cksum() { return enable_cksum_; }

    void set_dump_name(std::string&& name) { dump_name_ = name; }
    const std::string& dump_name() const { return dump_name_; }

private:
    bool ValueToBin(const Value& val);

    bool InvalidToBin();
    bool BooleanToBin(bool val);
    bool IntToBin(int64_t val);
    bool UIntToBin(uint64_t val);
    bool FloatToBin(float val);
    bool StringToBin(const Value::String& val);
    bool ListToBin(const Value::List& val);
    bool SetToBin(const Value::Set& val);
    bool ZSetToBin(const Value::ZSet& val);
    bool HashToBin(const Value::Hash& val);

    bool Write(const void* buf, size_t len);
    bool WriteType(uint8_t type);

public:
    const static char kIDNAME[3];   //"LDB"
    const static char kVERSION[4];  //current bin format version
    const static unsigned char kEOF;//end of db bin

private:
    uint64_t cksum_;
    bool enable_cksum_;
    std::string dump_name_;
    std::shared_ptr<FILE> file_;
};


}//namespace db
//-----------------------------------------------------------------------------
#endif //DB_DUMP_H_
