//---------------------------------------------------------------------------
#ifndef DB_DUMP_H_
#define DB_DUMP_H_
//---------------------------------------------------------------------------
/*
 * ldb文件结构
 * "LDB"|"0001"|DATA|EOF|CHECKSUM
 */
//---------------------------------------------------------------------------
#include "../thirdpart/base/include/file_helper.h"

#include "server.h"
#include "hash_value.h"
//---------------------------------------------------------------------------
namespace db
{

class Dump
{
public:
    Dump(Server& server);
    Dump(const Dump&) =delete;
    Dump& operator=(const Dump&) =delete;

public:
    bool Save(const std::string& path);

    const Server& server() const { return server_; }

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

    void SaveKeyValuePair(const std::string& key, const ObjectPtr& value);
    void SaveType(const ObjectPtr& value);
    void SaveKey(const std::string& key);
    void SaveValue(const ObjectPtr& value);
    void SaveValueString(const ObjectPtr& value);

private:
    base::FileHelper file_;
    int64_t checksum_;

    Server& server_;
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_DUMP_H_
