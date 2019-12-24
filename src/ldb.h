//---------------------------------------------------------------------------
#ifndef DB_LDB_H_
#define DB_LDB_H_
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

class Ldb
{
public:
    Ldb(const HashValue& val);
    Ldb(const Ldb&) =delete;
    Ldb operator=(const Ldb&) =delete;

    bool Save(const std::string& filename);
    bool Load(const std::string& filename);

private:
    std::string MakeTempFilename();
    std::string MakeVersion();

    void Checksum(const std::string& data);
    void Checksum(char c);

private:
    base::FileHelper file_;
    int64_t checksum_;
    const HashValue& val_;

private:
    const char* HEADER_SIGN = "LDB";
    const int HEADER_VERSION = 1;
    const unsigned char HEADER_EOF = static_cast<unsigned char>(0xFF);
};


}//namespace db
//---------------------------------------------------------------------------
#endif //DB_LDB_H_
