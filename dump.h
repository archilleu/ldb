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
    using Memory = std::vector<uint8_t>;

    Dump(const Value& v)
    :   val_(v),
        cksum_(0),
        enable_cksum_(false),
        file_or_bin_(false),
        dump_name_("dump")
    {
    }

    bool ToBin();
    bool ToFile();

    const Memory& bin() const { return bin_; }

    void set_enable_cksum_(bool enable) { enable_cksum_ = enable; }
    bool enable_cksum() { return enable_cksum_; }

    void set_dump_name(std::string&& name) { dump_name_ = name; }
    const std::string& dump_name() const { return dump_name_; }

private:
    //val to bin
    bool ValueToBin(const Value& val);

    bool InvalidToBin(const Value& val);
    bool BooleanToBin(const Value& val);
    bool IntToBin(const Value& val);
    bool UIntToBin(const Value& val);
    bool FloatToBin(const Value& val);
    bool StringToBin(const Value& val);
    bool ListToBin(const Value& val);
    bool SetToBin(const Value& val);
    bool ZSetToBin(const Value& val);
    bool HashToBin(const Value& val);

    bool Write(const void* buf, size_t len);
    bool WriteType(uint8_t type);
    bool WriteIdName();
    bool WriteVersion();
    bool WriteEOF();
    bool WriteChecksum();

public:
    const static char kIDNAME[3];   //"LDB"
    const static char kVERSION[4];  //current bin format version
    const static uint8_t kEOF;      //end of db bin

private:
    const Value& val_;

    uint64_t cksum_;
    bool enable_cksum_;
    bool file_or_bin_; //write to file or memory

    Memory bin_;
    std::string dump_name_;
    std::shared_ptr<FILE> file_;
    size_t pos_;
};

}//namespace db
//-----------------------------------------------------------------------------
#endif //DB_DUMP_H_
