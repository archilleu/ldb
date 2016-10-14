//---------------------------------------------------------------------------
#ifndef DB_UNDUMP_H_
#define DB_UNDUMP_H_
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
class UnDump 
{
public:
    using Memory = std::vector<uint8_t>;

    UnDump()
    :   cksum_(0),
        enable_cksum_(false)
    {
    }
    bool FromBin(const Memory& bin);
    bool FromBin(Memory&& bin);
    bool FromFile(std::string&& name);

    const Value& value() { return val_; }

private:
    //bin to value
    bool BinToValue(Value* val); 

    bool BinToInvalid(Value* val);
    bool BinToBoolean(Value* val);
    bool BinToInt(Value* val);
    bool BinToUInt(Value* val);
    bool BinToFloat(Value* val);
    bool BinToBinary(Value* val);
    bool BinToString(Value* val);
    bool BinToList(Value* val);
    bool BinToSet(Value* val);
    bool BinToZSet(Value* val);
    bool BinToHash(Value* val);

    bool Read(void* buf, size_t len);
    bool ReadType(uint8_t* type);
    bool ReadSize(uint32_t* size);
    bool ReadScore(double* score);
    bool ReadKey(std::string* key);
    bool ReadIdName(char id_name[3]);
    bool ReadVersion(char version[4]);
    bool ReadEOF(uint8_t* eof);
    bool ReadChecksum(uint64_t* cksum);

public:
    const static char kIDNAME[3];   //"LDB"
    const static char kVERSION[4];  //current bin format version
    const static uint8_t kEOF;      //end of db bin

private:
    Value val_;

    char id_name_[3];
    char version_[4];
    uint64_t cksum_;
    bool enable_cksum_;
    bool file_or_bin_; //read from file or memory
    
    Memory bin_;
    std::string dump_name_;
    std::shared_ptr<FILE> file_;
    size_t pos_;
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_UNDUMP_H_
