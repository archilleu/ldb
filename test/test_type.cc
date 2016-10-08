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

    Object om(std::move(o));
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

    Object oc(o);
    MY_ASSERT(false == oc.GetBoolean());
    MY_ASSERT(oc.type() == TYPE_BOOLEAN);
    oc.SetBoolean(true);
    MY_ASSERT(true == oc.GetBoolean());

    Object om(std::move(o));
    MY_ASSERT(om.type() == TYPE_BOOLEAN);
    MY_ASSERT(false == om.GetBoolean());
    om.SetBoolean(true);
    MY_ASSERT(true== om.GetBoolean());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
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

    Object oc(o);
    MY_ASSERT(1 == oc.GetInt());
    MY_ASSERT(oc.type() == TYPE_INT);
    oc.SetInt(1);
    MY_ASSERT(1 == oc.GetInt());
    MY_ASSERT(oc.type() == TYPE_INT);

    Object om(std::move(o));
    MY_ASSERT(om.type() == TYPE_INT);
    MY_ASSERT(1 == om.GetInt());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    //uint
    {
    uint64_t v = ULONG_LONG_MAX;
    Object o(v);
    MY_ASSERT(o.type() == TYPE_UINT);
    MY_ASSERT(ULONG_LONG_MAX == o.GetUInt());

    o.SetUInt(1);
    MY_ASSERT(1 == o.GetUInt());
    MY_ASSERT(o.type() == TYPE_UINT);

    Object oc(o);
    MY_ASSERT(1 == oc.GetUInt());
    MY_ASSERT(oc.type() == TYPE_UINT);
    o.SetUInt(1);
    MY_ASSERT(1 == oc.GetUInt());
    MY_ASSERT(oc.type() == TYPE_UINT);

    Object om(std::move(o));
    MY_ASSERT(om.type() == TYPE_UINT);
    MY_ASSERT(1 == om.GetUInt());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    //float
    {
    double v = DBL_MAX;
    Object o(v);
    MY_ASSERT(o.type() == TYPE_FLOAT);
    double diff = o.GetFloat() - v;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);

    o.SetFloat(1.0);
    diff = o.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(o.type() == TYPE_FLOAT);

    Object oc(o);
    oc.SetFloat(1.0);
    diff = oc.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(oc.type() == TYPE_FLOAT);

    Object om(std::move(o));
    diff = om.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(om.type() == TYPE_FLOAT);
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    //Binary
    {
    const int size = 128;
    Binary bin1(size, 'a');
    Binary bin2(size, 'b');

    Object o(bin1);
    MY_ASSERT(o.type() == TYPE_BINARY);
    MY_ASSERT(bin1 == o.GetBinary());
    MY_ASSERT(bin1.empty() == false);
    o.SetBinary(bin2);
    MY_ASSERT(bin2 == o.GetBinary());
    MY_ASSERT(o.type() == TYPE_BINARY);

    Object o1(Binary(size, 'a'));
    MY_ASSERT(o1.type() == TYPE_BINARY);
    MY_ASSERT(bin1 == o1.GetBinary());
    MY_ASSERT(bin1.empty() == false);
    o1.SetBinary(Binary(size, 'b'));
    MY_ASSERT(bin2 == o1.GetBinary());
    MY_ASSERT(o1.type() == TYPE_BINARY);

    Object oc(o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == TYPE_BINARY);
    MY_ASSERT(bin2 == oc.GetBinary());
    oc.SetBinary(bin1);
    MY_ASSERT(bin1 == oc.GetBinary());
    MY_ASSERT(oc.type() == TYPE_BINARY);

    Object om(std::move(o));
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == TYPE_BINARY);
    MY_ASSERT(bin2 == om.GetBinary());
    om.SetBinary(bin1);
    MY_ASSERT(bin1 == om.GetBinary());
    MY_ASSERT(om.type() == TYPE_BINARY);

    MY_ASSERT(o.type() == TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    return true;
}
//---------------------------------------------------------------------------
}// namespace test

}//namespace db
