//---------------------------------------------------------------------------
#ifndef DB_TEST_TYPE_H_
#define DB_TEST_TYPE_H_
//---------------------------------------------------------------------------
#include "test_base.h"
//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

class TestType : public TestBase
{
public:
    TestType()
    {
    }

    virtual ~TestType()
    {
    }

    virtual bool DoTest();

private:
    bool TestNormal();
};

}// namespace test

}//namespace db
//---------------------------------------------------------------------------
#endif// DB_TEST_TYPE_H_
