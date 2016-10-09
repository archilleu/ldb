//---------------------------------------------------------------------------
#include "test_value.h"
#include "../value.h"
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

//---------------------------------------------------------------------------
template<typename T>
static void PrintContainer(const T& val)
{
    std::cout << "[ ";
    for(auto iter : val)
    {
        switch(iter.type())
        {
            case Value::TYPE_INVALID:
                std::cout << "nil" << ", ";
                break;

            case Value::TYPE_BOOLEAN: 
                std::cout << iter.GetBoolean() << ", ";
                break;

            case Value::TYPE_INT: 
                std::cout << iter.GetInt() << ", ";
                break;

            case Value::TYPE_UINT: 
                std::cout << iter.GetUInt() << ", ";
                break;

            case Value::TYPE_FLOAT: 
                std::cout << iter.GetFloat() << ", ";
                break;

            case Value::TYPE_STRING: 
                std::cout << iter.GetString() << ", ";
                break;

            case Value::TYPE_BINARY:
             //   PrintContainer(iter.GetBinary());
                break;

            case Value::TYPE_LIST:
                PrintContainer(iter.GetList());
                break;

            case Value::TYPE_SET:
                PrintContainer(iter.GetSet());
                break;

            case Value::TYPE_ZSET:
            //    PrintContainer(iter.GetZSet());
                break;

            case Value::TYPE_HASH:
                //PrintContainer(iter.GetHash());
                break;

            default:
                assert(0);
        }
    }

    std::cout << " ]" << std::endl;
}
//---------------------------------------------------------------------------
static void PrintValue(const Value& val)
{
    switch(val.type())
    {
        case Value::TYPE_INVALID:
            std::cout << "nil" << std::endl;
            break;

        case Value::TYPE_BOOLEAN: 
            std::cout << val.GetBoolean() << std::endl;;
            break;

        case Value::TYPE_INT: 
            std::cout << val.GetInt() << std::endl;
            break;

        case Value::TYPE_UINT: 
            std::cout << val.GetUInt() << std::endl;
            break;

        case Value::TYPE_FLOAT: 
            std::cout << val.GetFloat() << std::endl;
            break;

        case Value::TYPE_STRING: 
            std::cout << val.GetString() << std::endl;
            break;

        case Value::TYPE_BINARY:
            //PrintContainer(val.GetBinary());
            break;

        case Value::TYPE_LIST:
            PrintContainer(val.GetList());
            break;

        case Value::TYPE_SET:
            PrintContainer(val.GetSet());
            break;

        case Value::TYPE_ZSET:
            //PrintContainer(val.GetZSet());
            break;

        case Value::TYPE_HASH:
            //PrintContainer(val.GetHash());
            break;
    }
}
//---------------------------------------------------------------------------
bool TestValue::DoTest()
{
    if(false == TestInvaild())  return false;
    if(false == TestBoolean())  return false;
    if(false == TestInt())  return false;
    if(false == TestUInt())  return false;
    if(false == TestFloat())  return false;
    if(false == TestBinary())  return false;
    if(false == TestString())  return false;
    if(false == TestList())  return false;
    if(false == TestSet())  return false;
    if(false == TestZSet())  return false;
    if(false == TestHash())  return false;

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestInvaild()
{
    //none
    {
    Value o;
    MY_ASSERT(o.type() == Value::TYPE_INVALID);

    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    Value oc(o);
    MY_ASSERT(oc.type() == Value::TYPE_INVALID);
    MY_ASSERT(oc.obj() == p);

    Value om(std::move(o));
    MY_ASSERT(om.type() == Value::TYPE_INVALID);
    MY_ASSERT(om.obj() == p);

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    MY_ASSERT(o.obj() == p);
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestBoolean()
{
    //boolean
    {
    Value o(true);
    MY_ASSERT(o.type() == Value::TYPE_BOOLEAN);
    MY_ASSERT(true == o.GetBoolean());

    o.SetBoolean(false);
    MY_ASSERT(false == o.GetBoolean());
    MY_ASSERT(o.type() == Value::TYPE_BOOLEAN);

    Value oc(o);
    MY_ASSERT(false == oc.GetBoolean());
    MY_ASSERT(oc.type() == Value::TYPE_BOOLEAN);
    oc.SetBoolean(true);
    MY_ASSERT(true == oc.GetBoolean());

    Value om(std::move(o));
    MY_ASSERT(om.type() == Value::TYPE_BOOLEAN); MY_ASSERT(false == om.GetBoolean());
    om.SetBoolean(true);
    MY_ASSERT(true== om.GetBoolean());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestInt()
{
    //int
    {
    int64_t v = LONG_LONG_MAX;
    Value o(v);
    MY_ASSERT(o.type() == Value::TYPE_INT);
    MY_ASSERT(LONG_LONG_MAX == o.GetInt());

    o.SetInt(1);
    MY_ASSERT(1 == o.GetInt());
    MY_ASSERT(o.type() == Value::TYPE_INT);

    Value oc(o);
    MY_ASSERT(1 == oc.GetInt());
    MY_ASSERT(oc.type() == Value::TYPE_INT);
    oc.SetInt(1);
    MY_ASSERT(1 == oc.GetInt());
    MY_ASSERT(oc.type() == Value::TYPE_INT);

    Value om(std::move(o));
    MY_ASSERT(om.type() == Value::TYPE_INT);
    MY_ASSERT(1 == om.GetInt());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestUInt()
{
    //uint
    {
    uint64_t v = ULONG_LONG_MAX;
    Value o(v);
    MY_ASSERT(o.type() == Value::TYPE_UINT);
    MY_ASSERT(ULONG_LONG_MAX == o.GetUInt());

    o.SetUInt(1);
    MY_ASSERT(1 == o.GetUInt());
    MY_ASSERT(o.type() == Value::TYPE_UINT);

    Value oc(o);
    MY_ASSERT(1 == oc.GetUInt());
    MY_ASSERT(oc.type() == Value::TYPE_UINT);
    o.SetUInt(1);
    MY_ASSERT(1 == oc.GetUInt());
    MY_ASSERT(oc.type() == Value::TYPE_UINT);

    Value om(std::move(o));
    MY_ASSERT(om.type() == Value::TYPE_UINT);
    MY_ASSERT(1 == om.GetUInt());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestFloat()
{
    //float
    {
    double v = DBL_MAX;
    Value o(v);
    MY_ASSERT(o.type() == Value::TYPE_FLOAT);
    double diff = o.GetFloat() - v;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);

    o.SetFloat(1.0);
    diff = o.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(o.type() == Value::TYPE_FLOAT);

    Value oc(o);
    oc.SetFloat(1.0);
    diff = oc.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(oc.type() == Value::TYPE_FLOAT);

    Value om(std::move(o));
    diff = om.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(om.type() == Value::TYPE_FLOAT);
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestBinary()
{
    //Binary
    {
    const int size = 128;
    Value::Binary bin1(size, 'a');
    Value::Binary bin2(size, 'b');

    Value o(bin1);
    MY_ASSERT(o.type() == Value::TYPE_BINARY);
    MY_ASSERT(bin1 == o.GetBinary());
    MY_ASSERT(bin1.empty() == false);
    o.SetBinary(bin2);
    MY_ASSERT(bin2 == o.GetBinary());
    MY_ASSERT(o.type() == Value::TYPE_BINARY);

    Value o1(Value::Binary(size, 'a'));
    MY_ASSERT(o1.type() == Value::TYPE_BINARY);
    MY_ASSERT(bin1 == o1.GetBinary());
    MY_ASSERT(bin1.empty() == false);
    o1.SetBinary(Value::Binary(size, 'b'));
    MY_ASSERT(bin2 == o1.GetBinary());
    MY_ASSERT(o1.type() == Value::TYPE_BINARY);

    Value oc(o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::TYPE_BINARY);
    MY_ASSERT(bin2 == oc.GetBinary());
    oc.SetBinary(bin1);
    MY_ASSERT(bin1 == oc.GetBinary());
    MY_ASSERT(oc.type() == Value::TYPE_BINARY);

    Value om(std::move(o));
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::TYPE_BINARY);
    MY_ASSERT(bin2 == om.GetBinary());
    om.SetBinary(bin1);
    MY_ASSERT(bin1 == om.GetBinary());
    MY_ASSERT(om.type() == Value::TYPE_BINARY);

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);
    }

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestString()
{
    const int size = 128;
    Value::String str1(size, 'a');
    Value::String str2(size, 'b');

    Value o(str1);
    MY_ASSERT(o.type() == Value::TYPE_STRING);
    MY_ASSERT(str1 == o.GetString());
    MY_ASSERT(o.SetString(str2));
    MY_ASSERT(str2 == o.GetString());
    MY_ASSERT(o.type() == Value::TYPE_STRING);

    Value o1(Value::String(size, 'a'));
    MY_ASSERT(o1.type() == Value::TYPE_STRING);
    MY_ASSERT(str1 == o1.GetString());
    MY_ASSERT(o1.SetString(Value::String(size, 'b')));
    MY_ASSERT(str2 == o1.GetString());
    MY_ASSERT(o1.type() == Value::TYPE_STRING);

    Value oc(o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::TYPE_STRING);
    MY_ASSERT(str2 == oc.GetString());
    MY_ASSERT(oc.SetString(str1));
    MY_ASSERT(str1 == oc.GetString());
    MY_ASSERT(oc.type() == Value::TYPE_STRING);

    Value om(std::move(o));
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::TYPE_STRING);
    MY_ASSERT(str2 == om.GetString());
    MY_ASSERT(om.SetString(str1));
    MY_ASSERT(str1 == om.GetString());
    MY_ASSERT(om.type() == Value::TYPE_STRING);

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestList()
{
    const int size = 6;
    Value::List list1(size, Value(true));
    Value::List list2(size, Value(false));

    Value o(list1);
    MY_ASSERT(o.type() == Value::TYPE_LIST);
    MY_ASSERT(list1 == o.GetList());
    MY_ASSERT(o.SetList(list2));
    MY_ASSERT(list2 == o.GetList());
    MY_ASSERT(o.type() == Value::TYPE_LIST);

    Value o1(Value::List(size, Value(true)));
    MY_ASSERT(o1.type() == Value::TYPE_LIST);
    MY_ASSERT(list1 == o1.GetList());
    MY_ASSERT(o1.SetList(Value::List(size, Value(false))));
    MY_ASSERT(list2 == o1.GetList());
    MY_ASSERT(o1.type() == Value::TYPE_LIST);

    Value oc(o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::TYPE_LIST);
    MY_ASSERT(list2 == oc.GetList());
    MY_ASSERT(oc.SetList(list1));
    MY_ASSERT(list1 == oc.GetList());
    MY_ASSERT(oc.type() == Value::TYPE_LIST);

    Value om(std::move(o));
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::TYPE_LIST);
    MY_ASSERT(list2 == om.GetList());
    MY_ASSERT(om.SetList(list1));
    MY_ASSERT(list1  == om.GetList());
    MY_ASSERT(om.type() == Value::TYPE_LIST);

    auto& val = om.GetList();
    val.push_back(Value(int64_t(LONG_LONG_MAX)));
    val.push_back(Value(uint64_t(ULONG_LONG_MAX)));
    val.push_back(Value(3.14));
    val.push_back(Value("string"));
    PrintValue(om);

    MY_ASSERT(o.type() == Value::TYPE_INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestSet()
{
    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestZSet()
{
    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestHash()
{
    return true;
}
//---------------------------------------------------------------------------
}// namespace test

}//namespace db
