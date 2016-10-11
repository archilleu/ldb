//---------------------------------------------------------------------------
#ifndef DB_TEST_VALUE_H_
#define DB_TEST_VALUE_H_
//---------------------------------------------------------------------------
#include "test_base.h"
//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

class TestValue : public TestBase
{
public:
    TestValue()
    {
    }

    virtual ~TestValue()
    {
    }

    virtual bool DoTest();

private:
    bool TestInvaild();
    bool TestBoolean();
    bool TestInt();
    bool TestUInt();
    bool TestFloat();
    bool TestBinary();
    bool TestString();
    bool TestList();
    bool TestSet();
    bool TestZSet();
    bool TestHash();
    bool TestMix();
};

}// namespace test

}//namespace db
//---------------------------------------------------------------------------
#endif// DB_TEST_VALUE_H_
