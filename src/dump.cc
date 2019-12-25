//---------------------------------------------------------------------------
#include "dump.h"
#include "../thirdpart/base/include/function.h"
#include "../thirdpart/base/include/thread.h"
#include "../thirdpart/base/include/crc64.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
const char Dump::kIDNAME[3] = {'L','D','B'};
const char Dump::kVERSION[4] = {'0','0','0','1'};
const uint8_t Dump::kEOF = 0xFF;
//---------------------------------------------------------------------------
Dump::Dump(const std::vector<HashValue>& val)
:   val_(val)
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

        //data
        
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
    Write(kIDNAME, sizeof(kIDNAME));
}
//---------------------------------------------------------------------------
void Dump::WriteVersion()
{
    Write(kVERSION, sizeof(kVERSION));
}
//---------------------------------------------------------------------------
void Dump::WriteEOF()
{
    WriteType(kEOF);
}
//---------------------------------------------------------------------------
void Dump::WriteChecksum()
{
    WriteInt(checksum_);
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
