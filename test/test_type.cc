//---------------------------------------------------------------------------
#include "test_type.h"
#include "../type.h"
#include <string.h>
#include <limits.h>
#include <float.h>
#include <memory>
#include <cmath>

//---------------------------------------------------------------------------
namespace db 
{

namespace test
{

bool TestType::DoTest()
{
    if(false == TestNormal())  return false;

    return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool TestType::TestNormal()
{
    //none
    {
    Object o;
    MY_ASSERT(o.type() == TYPE_INVALID);

    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    Object oc(o);
    MY_ASSERT(oc.type() == TYPE_INVALID);
    MY_ASSERT(oc.obj() == p);

    Object om(o);
    MY_ASSERT(om.type() == TYPE_INVALID);
    MY_ASSERT(om.obj() == p);

    MY_ASSERT(o.type() == TYPE_INVALID);
    MY_ASSERT(o.obj() == p);
    }

    //boolean
    {
    Object o(true);
    MY_ASSERT(o.type() == TYPE_BOOLEAN);
    MY_ASSERT(true == o.GetBoolean());

    o.SetBoolean(false);
    MY_ASSERT(false == o.GetBoolean());
    MY_ASSERT(o.type() == TYPE_BOOLEAN);
    }

    //int
    {
    int64_t v = LONG_LONG_MAX;
    Object o(v);
    MY_ASSERT(o.type() == TYPE_INT);
    MY_ASSERT(LONG_LONG_MAX == o.GetInt());

    o.SetInt(1);
    MY_ASSERT(1 == o.GetInt());
    MY_ASSERT(o.type() == TYPE_INT);
    }

    //int
    {
    uint64_t v = ULONG_LONG_MAX;
    Object o(v);
    MY_ASSERT(o.type() == TYPE_UINT);
    MY_ASSERT(ULONG_LONG_MAX == o.GetUInt());

    o.SetInt(1);
    MY_ASSERT(1 == o.GetUInt());
    MY_ASSERT(o.type() == TYPE_UINT);
    }

    //float
    {
    double v = DBL_MAX;
    Object o(v);
    MY_ASSERT(o.type() == TYPE_FLOAT);
    double diff = o.GetFloat() - v;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);

    o.SetInt(1.0);
    diff = o.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(o.type() == TYPE_FLOAT);
    }

    //Binary
    {
    const int size = 128;
    Binary bin1(size, 'a');
    Binary bin2(size, 'a');

    Object o1(bin1);
    Object o2(std::move(bin2));
    MY_ASSERT(o1.type() == TYPE_BINARY);
    MY_ASSERT(o2.type() == TYPE_BINARY);
    MY_ASSERT(bin1 == o1.GetBinary());
    MY_ASSERT(bin1 == o2.GetBinary());
    MY_ASSERT(bin1.empty() == false);
    MY_ASSERT(bin2.empty() == true);

    Binary bin3(size, 'b');
    Binary bin4(size, 'b');
    o1.SetBinary(bin3);
    o2.SetBinary(std::move(bin4));
    MY_ASSERT(bin3 == o1.GetBinary());
    MY_ASSERT(bin3 == o2.GetBinary());
    MY_ASSERT(bin3.empty() == false);
    MY_ASSERT(bin4.empty() == true);

    MY_ASSERT(o1.type() == TYPE_BINARY);
    MY_ASSERT(o2.type() == TYPE_BINARY);
    }


    return true;
}
//---------------------------------------------------------------------------
}// namespace test

}//namespace db
