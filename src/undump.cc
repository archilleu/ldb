//---------------------------------------------------------------------------
#include "undump.h"
#include "../thirdpart/base/include/function.h"
#include "../thirdpart/base/include/crc64.h"
#include "hash_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
const char Undump::kIDNAME[3] = {'L','D','B'};
const char Undump::kVERSION[4] = {'0','0','0','1'};
const uint8_t Undump::kEOF = 0xFF;
//---------------------------------------------------------------------------
Undump::Undump()
:   buffer_(1024*1024),
    checksum_(0)
{
}
//---------------------------------------------------------------------------
bool Undump::Load(const std::string& path, std::vector<HashValue>* dbs)
{
    (void)dbs;
    try
    {
        file_.Open(path);

        if(false == CheckIdName())  return false;
        if(false == CheckVersion()) return false;

        //data
        
        if(false == CheckEOF())     return false;
        if(false == CheckChecksum())return false;

        file_.Close();

    }
    catch(std::exception e)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool Undump::ToBin(const std::string& path, std::vector<HashValue>* dbs)
{
    (void)path;
    (void)dbs;
    return false;
}
//---------------------------------------------------------------------------
void Undump::Read(size_t len)
{
    MakeSureSize(len);

    if(len != file_.Read(const_cast<char*>(buffer_.data()), len))
        throw std::runtime_error("read file failed");

    checksum_ = base::crc64(checksum_, reinterpret_cast<const unsigned char*>(buffer_.data()), len);

    return;
}
//---------------------------------------------------------------------------
uint8_t Undump::ReadType()
{
    Read(sizeof(uint8_t));
    return buffer_.front();
}
//---------------------------------------------------------------------------
uint32_t Undump::ReadSize()
{
    Read(sizeof(uint32_t));
    return *reinterpret_cast<uint32_t*>(const_cast<char*>((buffer_.data())));
}
//---------------------------------------------------------------------------
double Undump::ReadScore()
{
    Read(sizeof(double));
    return *reinterpret_cast<double*>(const_cast<char*>((buffer_.data())));
}
//---------------------------------------------------------------------------
int64_t Undump::ReadInt()
{
    Read(sizeof(int64_t));
    return *reinterpret_cast<int64_t*>(const_cast<char*>((buffer_.data())));
}
//---------------------------------------------------------------------------
void Undump::ReadKey()
{
}
//---------------------------------------------------------------------------
bool Undump::CheckIdName()
{
    Read(sizeof(kIDNAME));
    if(0 != memcmp(kIDNAME, buffer_.data(), sizeof(kIDNAME)))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool Undump::CheckVersion()
{
    Read(sizeof(kVERSION));
    if(0 != memcmp(kVERSION, buffer_.data(), sizeof(kVERSION)))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool Undump::CheckEOF()
{
    Read(sizeof(kEOF));
    if(0 != memcmp(&kEOF, buffer_.data(), sizeof(kEOF)))
        return false;

    return true;
}
//---------------------------------------------------------------------------
bool Undump::CheckChecksum()
{
    if(sizeof(int64_t) != file_.Read(const_cast<char*>(buffer_.data()), sizeof(int64_t)))
        throw std::runtime_error("read file failed");

    int64_t checksum = *reinterpret_cast<int64_t*>(const_cast<char*>((buffer_.data())));
    if(checksum_ != checksum)
        return false;

    return true;
}
//---------------------------------------------------------------------------
void Undump::MakeSureSize(size_t size)
{
    if(size > buffer_.size())
        buffer_.resize(size *2);

    return;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
