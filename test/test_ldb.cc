//---------------------------------------------------------------------------
#include "test_ldb.h"
#include "../ldb.h"
#include <string.h>
//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

bool TestLdb::DoTest()
{
    if(false == TestNormal()) return false;

    return true;
}
//---------------------------------------------------------------------------
bool TestLdb::TestNormal()
{
    int no = 1;
    Ldb ldb(no);
    
    MY_ASSERT(no == ldb.no());

    ldb["haha"] = Value(true);
    std::cout << ldb.dict() << std::endl;
    MY_ASSERT(1 == ldb.Size())
    MY_ASSERT(ldb["haha"] == Value(true));
    ldb.Clear();
    MY_ASSERT(0 == ldb.Size())
    std::cout << ldb.dict() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
}// namespace test

}//namespace db
