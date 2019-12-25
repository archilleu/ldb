//---------------------------------------------------------------------------
#ifndef DB_DUMP_H_
#define DB_DUMP_H_
//---------------------------------------------------------------------------
/*
 * ldb文件结构
 * "LDB"|"0001"|DATA|EOF|CHECKSUM
 */
//---------------------------------------------------------------------------
#include <string>

#include "../thirdpart/base/include/file_helper.h"

#include "hash_value.h"
//---------------------------------------------------------------------------
namespace db
{

class Dump
{
public:
    Dump(const std::vector<HashValue>& val);
    Dump(const Dump&) =delete;
    Dump operator=(const Dump&) =delete;

    bool Save(const std::string& path);

    std::vector<uint8_t> ToBin();

private:
    std::string MakeTempFilename() const;

    void Write(const void* dat, size_t len);
    void WriteType(uint8_t type);
    void WriteSize(uint32_t len);
    void WriteScore(double score);
    void WriteInt(int64_t val);
    void WriteKey(const std::string& key);
    void WriteIdName();
    void WriteVersion();
    void WriteEOF();
    void WriteChecksum();

private:
    base::FileHelper file_;
    int64_t checksum_;
    const std::vector<HashValue>& val_;

private:
    const static char kIDNAME[3];
    const static char kVERSION[4];
    const static uint8_t kEOF;
};


}//namespace db
//---------------------------------------------------------------------------
#endif //DB_DUMP_H_
