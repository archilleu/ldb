//---------------------------------------------------------------------------
#include "ldb.h"
#include "../thirdpart/base/include/function.h"
#include "../thirdpart/base/include/thread.h"
#include "../thirdpart/base/include/crc64.h"
//---------------------------------------------------------------------------
namespace db
{
//---------------------------------------------------------------------------
Ldb::Ldb(const HashValue& val)
:   val_(val)
{
    checksum_ = 0;
}
//---------------------------------------------------------------------------
bool Ldb::Save(const std::string& filename)
{
    try
    {
        (void)filename;
        std::string tmp_file = MakeTempFilename();
        file_.Open(tmp_file);
        std::string version = MakeVersion();

        file_.Write(version);
        Checksum(version);

        //data
        
        file_.Write(&HEADER_EOF, 1);

        file_.Write(HEADER_EOF);
        Checksum(HEADER_EOF);
        
        file_.Write(checksum_);
    }
    catch(std::exception e)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool Ldb::Load(const std::string& filename)
{
    try
    {
        (void)filename;
    }
    catch(std::exception e)
    {
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
std::string Ldb::MakeTempFilename()
{
    return base::CombineString("temp-%d.ldb", base::CurrentThread::tid());
}
//---------------------------------------------------------------------------
std::string Ldb::MakeVersion()
{
    return base::CombineString("%s%04d", HEADER_SIGN, HEADER_VERSION);
}
//---------------------------------------------------------------------------
void Ldb::Checksum(const std::string& data)
{
    checksum_ = base::crc64(checksum_, reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
}
//---------------------------------------------------------------------------
void Ldb::Checksum(char c)
{
    checksum_ = base::crc64(checksum_, reinterpret_cast<const unsigned char*>(&c), 1);
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
