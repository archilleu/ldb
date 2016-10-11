//---------------------------------------------------------------------------
#include "test_value.h"
#include "../value.h"
#include <string.h>
#include <limits.h>
#include <float.h>
#include <memory>
#include <cmath>
#include <sstream>
//---------------------------------------------------------------------------
namespace db
{

namespace test
{

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
    if(false == TestMix())  return false;

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestInvaild()
{
    //none
    {
    Value o;
    MY_ASSERT(o.type() == Value::INVALID);
    std::cout << o << std::endl;

    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(oc.type() == Value::INVALID);
    MY_ASSERT(oc.obj() == p);

    Value om(std::move(o));
    MY_ASSERT(om == o);
    MY_ASSERT(om.type() == Value::INVALID);
    MY_ASSERT(om.obj() == p);

    MY_ASSERT(o.type() == Value::INVALID);
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
    std::cout << o << std::endl;
    MY_ASSERT(Value(false) != o);
    MY_ASSERT(o.type() == Value::BOOLEAN);
    MY_ASSERT(true == o.GetBoolean());

    o.SetBoolean(false);
    MY_ASSERT(false == o.GetBoolean());
    MY_ASSERT(o.type() == Value::BOOLEAN);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(false == oc.GetBoolean());
    MY_ASSERT(oc.type() == Value::BOOLEAN);
    oc.SetBoolean(true);
    MY_ASSERT(true == oc.GetBoolean());

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.type() == Value::BOOLEAN); MY_ASSERT(false == om.GetBoolean());
    om.SetBoolean(true);
    MY_ASSERT(true== om.GetBoolean());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::INVALID);
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
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::INT);
    MY_ASSERT(LONG_LONG_MAX == o.GetInt());
    MY_ASSERT(Value(int64_t(1)) != o);

    o.SetInt(1);
    MY_ASSERT(1 == o.GetInt());
    MY_ASSERT(o.type() == Value::INT);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(1 == oc.GetInt());
    MY_ASSERT(oc.type() == Value::INT);
    oc.SetInt(1);
    MY_ASSERT(1 == oc.GetInt());
    MY_ASSERT(oc.type() == Value::INT);

    Value om(std::move(o));
    MY_ASSERT(om.type() == Value::INT);
    MY_ASSERT(1 == om.GetInt());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::INVALID);
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
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::UINT);
    MY_ASSERT(ULONG_LONG_MAX == o.GetUInt());
    MY_ASSERT(Value(int64_t(1)) != o);


    o.SetUInt(1);
    MY_ASSERT(1 == o.GetUInt());
    MY_ASSERT(o.type() == Value::UINT);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(1 == oc.GetUInt());
    MY_ASSERT(oc.type() == Value::UINT);
    o.SetUInt(1);
    MY_ASSERT(1 == oc.GetUInt());
    MY_ASSERT(oc.type() == Value::UINT);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.type() == Value::UINT);
    MY_ASSERT(1 == om.GetUInt());
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::INVALID);
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
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::FLOAT);
    double diff = o.GetFloat() - v;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(Value(1.0f) != o);

    o.SetFloat(1.0);
    diff = o.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(o.type() == Value::FLOAT);

    Value oc(o);
    MY_ASSERT(oc == o);
    oc.SetFloat(1.0);
    diff = oc.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(oc.type() == Value::FLOAT);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    diff = om.GetFloat() - 1.0;
    diff = abs(static_cast<int>(diff));
    MY_ASSERT(0 == diff);
    MY_ASSERT(om.type() == Value::FLOAT);
    MY_ASSERT(om.obj().unique());

    MY_ASSERT(o.type() == Value::INVALID);
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
    const int size = 8;
    Value::Binary bin1(size, 'a');
    Value::Binary bin2(size, 'b');

    Value o(bin1);
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::BINARY);
    MY_ASSERT(bin1 == o.GetBinary());
    MY_ASSERT(bin1.empty() == false);
    o.SetBinary(bin2);
    MY_ASSERT(bin2 == o.GetBinary());
    MY_ASSERT(o.type() == Value::BINARY);
    MY_ASSERT(Value(bin1) != o);

    Value o1(Value::Binary(size, 'a'));
    MY_ASSERT(o1.type() == Value::BINARY);
    MY_ASSERT(bin1 == o1.GetBinary());
    MY_ASSERT(bin1.empty() == false);
    o1.SetBinary(Value::Binary(size, 'b'));
    MY_ASSERT(bin2 == o1.GetBinary());
    MY_ASSERT(o1.type() == Value::BINARY);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::BINARY);
    MY_ASSERT(bin2 == oc.GetBinary());
    MY_ASSERT(oc != (Value(bin1)));
    oc.SetBinary(bin1);
    MY_ASSERT(oc == (Value(bin1)));
    MY_ASSERT(bin1 == oc.GetBinary());
    MY_ASSERT(oc.type() == Value::BINARY);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::BINARY);
    MY_ASSERT(bin2 == om.GetBinary());
    om.SetBinary(bin1);
    MY_ASSERT(bin1 == om.GetBinary());
    MY_ASSERT(om.type() == Value::BINARY);

    MY_ASSERT(o.type() == Value::INVALID);
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
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::STRING);
    MY_ASSERT(str1 == o.GetString());
    MY_ASSERT(o.SetString(str2));
    MY_ASSERT(str2 == o.GetString());
    MY_ASSERT(o.type() == Value::STRING);
    MY_ASSERT(Value(str1) != o);

    Value o1(Value::String(size, 'a'));
    MY_ASSERT(o1.type() == Value::STRING);
    MY_ASSERT(str1 == o1.GetString());
    MY_ASSERT(o1.SetString(Value::String(size, 'b')));
    MY_ASSERT(str2 == o1.GetString());
    MY_ASSERT(o1.type() == Value::STRING);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(oc != Value("abc"));
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::STRING);
    MY_ASSERT(str2 == oc.GetString());
    MY_ASSERT(oc.SetString(str1));
    MY_ASSERT(str1 == oc.GetString());
    MY_ASSERT(oc.type() == Value::STRING);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::STRING);
    MY_ASSERT(str2 == om.GetString());
    MY_ASSERT(om.SetString(str1));
    MY_ASSERT(str1 == om.GetString());
    MY_ASSERT(om.type() == Value::STRING);

    MY_ASSERT(o.type() == Value::INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestList()
{
    const int size = 3;
    Value::List list1(size, Value(true));
    Value::List list2(size, Value(false));

    Value o(list1);
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::LIST);
    MY_ASSERT(list1 == o.GetList());
    MY_ASSERT(o.SetList(list2));
    MY_ASSERT(list2 == o.GetList());
    MY_ASSERT(o.type() == Value::LIST);
    MY_ASSERT(Value(list1) != o);

    Value o1(Value::List(size, Value(true)));
    MY_ASSERT(o1.type() == Value::LIST);
    MY_ASSERT(list1 == o1.GetList());
    MY_ASSERT(o1.SetList(Value::List(size, Value(false))));
    MY_ASSERT(list2 == o1.GetList());
    MY_ASSERT(o1.type() == Value::LIST);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::LIST);
    MY_ASSERT(list2 == oc.GetList());
    MY_ASSERT(oc.SetList(list1));
    MY_ASSERT(list1 == oc.GetList());
    MY_ASSERT(oc.type() == Value::LIST);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::LIST);
    MY_ASSERT(list2 == om.GetList());
    MY_ASSERT(om.SetList(list1));
    MY_ASSERT(list1  == om.GetList());
    MY_ASSERT(om.type() == Value::LIST);

    auto& val = om.GetList();
    val.push_back(Value(int64_t(LONG_LONG_MAX)));
    val.push_back(Value(uint64_t(ULONG_LONG_MAX)));
    val.push_back(Value(3.14));
    val.push_back(Value("string"));
    val.push_back(Value(Value::List(1,Value(false))));
    val.push_back(Value(Value::List(1,Value("3.14"))));
    val.push_back(Value(Value::List(1,Value("ss"))));
    val.push_back(Value("string"));
    val.push_back(Value(Value::List(1,Value())));
    val.push_back(Value(Value::List(1,Value("1"))));
    std::cout << om << std::endl;

    MY_ASSERT(o.type() == Value::INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    return true;
}
//---------------------------------------------------------------------------
void PrintSet(const Value::Set& val)
{
    for(auto iter : val)
        std::cout << iter << ", ";

    std::cout << std::endl;
}
//---------------------------------------------------------------------------
bool TestValue::TestSet()
{
    Value::Set set1;
    Value::Set set2;
    set1.insert(Value(true));
    set2.insert(Value(false));
    set1.insert(Value(int64_t(1)));
    set2.insert(Value(int64_t(2)));
    set1.insert(Value(1.0));
    set2.insert(Value(2.0));
    set1.insert(Value("string1"));
    set2.insert(Value("string2"));

    Value o(set1);
    MY_ASSERT(Value(set1) == o);
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::SET);
    MY_ASSERT(set1 == o.GetSet());
    MY_ASSERT(o.SetSet(set2));
    MY_ASSERT(set2 == o.GetSet());
    MY_ASSERT(o.type() == Value::SET);
    MY_ASSERT(Value(set1) != o);
    MY_ASSERT(Value(set2) == o);
    std::cout << o << std::endl;

    Value o1(set1);
    MY_ASSERT(o1.type() == Value::SET);
    MY_ASSERT(set1 == o1.GetSet());
    MY_ASSERT(o1.SetSet(Value::Set(set2)));
    MY_ASSERT(set2 == o1.GetSet());
    MY_ASSERT(o1.type() == Value::SET);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::SET);
    MY_ASSERT(set2  == oc.GetSet());
    MY_ASSERT(oc.SetSet(set1));
    MY_ASSERT(set1 == oc.GetSet());
    MY_ASSERT(oc.type() == Value::SET);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::SET);
    MY_ASSERT(set2 == om.GetSet());
    MY_ASSERT(om.SetSet(set1));
    MY_ASSERT(set1 == om.GetSet());
    MY_ASSERT(om.type() == Value::SET);

    auto& val = om.GetSet();
    val.insert(Value(int64_t(LONG_LONG_MAX)));
    val.insert(Value(uint64_t(ULONG_LONG_MAX)));
    val.insert(Value(3.14));
    std::cout << om << std::endl;
    val.insert(Value(val));
    val.insert(Value("string"));
    val.insert(Value("string"));
    val.insert(Value("string"));
    val.insert(Value("string"));
    std::cout << om << std::endl;

    MY_ASSERT(o.type() == Value::INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestZSet()
{
    Value::ZSet zset1;
    Value::ZSet zset2;
    zset1.emplace(1.0, Value(true));
    zset2.emplace(2.0, Value(false));
    zset1.emplace(1.0, Value(int64_t(LONG_LONG_MAX)));
    zset2.emplace(2.0, Value(int64_t(LONG_LONG_MAX)));
    zset1.emplace(1.0, Value(1.0));
    zset2.emplace(2.0, Value(2.0));
    zset1.emplace(1.0, Value("string1"));
    zset2.emplace(2.0, Value("string2"));

    Value o(zset1);
    MY_ASSERT(Value(zset1) == o);
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::ZSET);
    MY_ASSERT(zset1 == o.GetZSet());
    MY_ASSERT(o.SetZSet(zset2));
    MY_ASSERT(zset2 == o.GetZSet());
    MY_ASSERT(o.type() == Value::ZSET);
    MY_ASSERT(Value(zset1) != o);
    MY_ASSERT(Value(zset2) == o);
    std::cout << o << std::endl;

    Value o1(zset1);
    MY_ASSERT(o1.type() == Value::ZSET);
    MY_ASSERT(zset1 == o1.GetZSet());
    MY_ASSERT(o1.SetZSet(Value::ZSet(zset2)));
    MY_ASSERT(zset2 == o1.GetZSet());
    MY_ASSERT(o1.type() == Value::ZSET);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::ZSET);
    MY_ASSERT(zset2  == oc.GetZSet());
    MY_ASSERT(oc.SetZSet(zset1));
    MY_ASSERT(zset1 == oc.GetZSet());
    MY_ASSERT(oc.type() == Value::ZSET);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::ZSET);
    MY_ASSERT(zset2 == om.GetZSet());
    MY_ASSERT(om.SetZSet(zset1));
    MY_ASSERT(zset1 == om.GetZSet());
    MY_ASSERT(om.type() == Value::ZSET);

    auto& val = om.GetZSet();
    val.emplace(3.0, Value(val));
    val.emplace(1.0, Value(int64_t(LONG_LONG_MAX)));
    val.emplace(1.0, Value(uint64_t(ULONG_LONG_MAX)));
    val.emplace(1.0, Value(3.14));
    val.emplace(2.0, Value("string"));
    std::cout << om << std::endl;

    MY_ASSERT(o.type() == Value::INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestHash()
{
    Value::Hash hash1;
    Value::Hash hash2;
    hash1.emplace("key1", Value(true));
    hash2.emplace("key1", Value(false));
    hash1.emplace("key2", Value(int64_t(LONG_LONG_MAX)));
    hash2.emplace("key2", Value(int64_t(LONG_LONG_MAX)));
    hash1.emplace("key3", Value(1.0));
    hash2.emplace("key3", Value(2.0));
    hash1.emplace("key4", Value("string1"));
    hash2.emplace("key4444", Value("string2"));

    Value o(hash1);
    MY_ASSERT(Value(hash1) == o);
    std::cout << o << std::endl;
    MY_ASSERT(o.type() == Value::HASH);
    MY_ASSERT(hash1 == o.GetHash());
    MY_ASSERT(o.SetHash(hash2));
    MY_ASSERT(hash2 == o.GetHash());
    MY_ASSERT(o.type() == Value::HASH);
    MY_ASSERT(Value(hash1) != o);
    MY_ASSERT(Value(hash2) == o);
    std::cout << o << std::endl;

    Value o1(hash1);
    MY_ASSERT(o1.type() == Value::HASH);
    MY_ASSERT(hash1 == o1.GetHash());
    MY_ASSERT(o1.SetHash(Value::Hash(hash2)));
    MY_ASSERT(hash2 == o1.GetHash());
    MY_ASSERT(o1.type() == Value::HASH);

    Value oc(o);
    MY_ASSERT(oc == o);
    MY_ASSERT(false == oc.obj().unique());
    MY_ASSERT(oc.type() == Value::HASH);
    MY_ASSERT(hash2  == oc.GetHash());
    MY_ASSERT(oc.SetHash(hash1));
    MY_ASSERT(hash1 == oc.GetHash());
    MY_ASSERT(oc.type() == Value::HASH);

    Value om(std::move(o));
    MY_ASSERT(oc != o);
    MY_ASSERT(om.obj().unique());
    MY_ASSERT(om.type() == Value::HASH);
    MY_ASSERT(hash2 == om.GetHash());
    MY_ASSERT(om.SetHash(hash1));
    MY_ASSERT(hash1 == om.GetHash());
    MY_ASSERT(om.type() == Value::HASH);

    Value::List list(3, Value(true));

    Value::ZSet zset1;
    zset1.emplace(1.0, Value(true));
    zset1.emplace(1.0, Value(int64_t(LONG_LONG_MAX)));
    zset1.emplace(1.0, Value(1.0));
    zset1.emplace(1.0, Value("string1"));
    zset1.emplace(1.0, Value(Value::List()));
    zset1.emplace(1.0, Value(Value::ZSet()));
    Value zs(zset1);

    auto& val = om.GetHash();
    val.emplace("key10", zs);
    val.emplace("key11", Value(list));
    val.emplace("key5", Value(val));
    val.emplace("key6", Value(int64_t(LONG_LONG_MAX)));
    val.emplace("key7", Value(uint64_t(ULONG_LONG_MAX)));
    val.emplace("key8", Value(3.14));
    val.emplace("key9", Value("string"));
    val.emplace("key9", Value("dup string"));
    std::cout << om << std::endl;

    MY_ASSERT(o.type() == Value::INVALID);
    std::shared_ptr<void> p;
    MY_ASSERT(o.obj() == p);

    return true;
}
//---------------------------------------------------------------------------
bool TestValue::TestMix()
{
    Value::List list;
    list.push_back(Value());
    list.push_back(Value(true));
    list.push_back(Value(false));
    list.push_back(Value(int64_t(LONG_LONG_MAX)));
    list.push_back(Value(uint64_t(ULONG_LONG_MAX)));
    list.push_back(Value(DBL_MAX));
    list.push_back(Value("string"));

    Value::Set set;
    set.insert(Value());
    set.insert(Value(true));
    set.insert(Value(true));
    set.insert(Value(false));
    set.insert(Value(int64_t(LONG_LONG_MAX)));
    set.insert(Value(uint64_t(ULONG_LONG_MAX)));
    set.insert(Value(DBL_MAX));
    set.insert(Value("string"));

    Value::ZSet zset;
    zset.emplace(1, Value());
    zset.emplace(2, Value(true));
    zset.emplace(3, Value(true));
    zset.emplace(4, Value(false));
    zset.emplace(5, Value(int64_t(LONG_LONG_MAX)));
    zset.emplace(6, Value(uint64_t(ULONG_LONG_MAX)));
    zset.emplace(7, Value(DBL_MAX));
    zset.emplace(8, Value("string"));

    Value::Hash hash;
    hash.emplace("key0", Value());
    hash.emplace("key1", Value(true));
    hash.emplace("key2", Value(true));
    hash.emplace("key3", Value(false));
    hash.emplace("key4", Value(int64_t(LONG_LONG_MAX)));
    hash.emplace("key5", Value(uint64_t(ULONG_LONG_MAX)));
    hash.emplace("key6", Value(DBL_MAX));
    hash.emplace("key7", Value("string"));
    hash.emplace("key7", Value("dup string"));

    Value::List l1(list);
    Value::Set s1(set);
    Value::ZSet zs1(zset);
    Value::Hash h1(hash);

    l1.push_back(Value(list));
    l1.push_back(Value(set));
    l1.push_back(Value(zset));
    l1.push_back(Value(hash));

    s1.insert(Value(list));
    s1.insert(Value(set));
    s1.insert(Value(zset));
    s1.insert(Value(hash));

    zs1.emplace(9, Value(list));
    zs1.emplace(9, Value(set));
    zs1.emplace(9, Value(zset));
    zs1.emplace(9, Value(hash));

    h1.emplace("key8", Value(list));
    h1.emplace("key9", Value(set));
    h1.emplace("key10", Value(zset));
    h1.emplace("key11", Value(hash));

    Value o(Value::TYPE::HASH);
    Value::Hash& v = o.GetHash();
    v.emplace("list", Value(l1));
    v.emplace("set", Value(s1));
    v.emplace("zset", Value(zs1));
    v.emplace("hash", Value(h1));

    std::cout << "================" << std::endl;
        std::cout << o << std::endl;
    std::cout << "================" << std::endl;

    return true;
}
//---------------------------------------------------------------------------
}// namespace test

}//namespace db
