//---------------------------------------------------------------------------
#ifndef DB_TEST_BASE_H_
#define DB_TEST_BASE_H_
//---------------------------------------------------------------------------
#include <assert.h>
#include <iostream>
#define MY_ASSERT(EXPRESSION) {if(true != (EXPRESSION)) { assert(0); return false;}}
//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

class TestBase
{
public:
    TestBase()
    {
    }

    virtual ~TestBase()
    {
    }

    virtual bool DoTest() =0;
};

}// namespace test

}//namespace db
//---------------------------------------------------------------------------
#endif// DB_TEST_BASE_H_
