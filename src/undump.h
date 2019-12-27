//---------------------------------------------------------------------------
#ifndef DB_UNDUMP_H_
#define DB_UNDUMP_H_
//---------------------------------------------------------------------------
/*
 * ldb文件结构
 * "LDB"|"0001"|DATA|EOF|CHECKSUM
 */
//---------------------------------------------------------------------------
#include "../thirdpart/base/include/file_helper.h"

#include "object_ptr.h"
#include "server.h"
//---------------------------------------------------------------------------
namespace db
{

class HashValue;

class Undump
{
public:
    Undump(Server& server);
    Undump(const Undump&) =delete;
    Undump& operator=(const Undump&) =delete;

public:
    bool Load(const std::string& path);

private:
    void Read(size_t len);
    uint8_t ReadType();
    uint32_t ReadSize();
    double ReadScore();
    int64_t ReadInt();

    bool CheckIdName();
    bool CheckVersion();
    bool CheckEOF();
    bool CheckChecksum();

    void MakeSureSize(size_t size);

    void Load();
    void LoadKeyValuePair(uint8_t type, HashValue& hash);
    std::string LoadKey();
    ObjectPtr LoadValue(uint8_t type);
    ObjectPtr LoadValueString();

private:
    Server& server_;
    base::FileHelper file_;
    std::vector<char> buffer_;
    int64_t checksum_;
};


}//namespace db
//---------------------------------------------------------------------------
#endif //DB_UNDUMP_H_
