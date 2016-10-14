//---------------------------------------------------------------------------
#ifndef DB_TEST_DUMP_H_
#define DB_TEST_DUMP_H_
//---------------------------------------------------------------------------
#include "test_base.h"
//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

class TestDump : public TestBase
{
public:
    TestDump()
    {
    }

    virtual ~TestDump()
    {
    }

    virtual bool DoTest();

private:
    bool TestInvaild();
    bool TestBoolean();
    bool TestInt();
    bool TestList();
    bool TestZSet();
};

}

}
//---------------------------------------------------------------------------
#endif //DB_TEST_DUMP_H_
