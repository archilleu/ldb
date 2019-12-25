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
//---------------------------------------------------------------------------
namespace db
{

class HashValue;

class Undump
{
public:
    Undump();
    Undump(const Undump&) =delete;
    Undump operator=(const Undump&) =delete;

    bool Load(const std::string& path, std::vector<HashValue>* dbs);
    bool ToBin(const std::string& path, std::vector<HashValue>* dbs);

private:
    void Read(size_t len);
    uint8_t ReadType();
    uint32_t ReadSize();
    double ReadScore();
    int64_t ReadInt();
    void ReadKey();

    bool CheckIdName();
    bool CheckVersion();
    bool CheckEOF();
    bool CheckChecksum();

    void MakeSureSize(size_t size);

private:
    base::FileHelper file_;
    std::vector<char> buffer_;
    int64_t checksum_;

private:
    const static char kIDNAME[3];
    const static char kVERSION[4];
    const static uint8_t kEOF;
};


}//namespace db
//---------------------------------------------------------------------------
#endif //DB_UNDUMP_H_
