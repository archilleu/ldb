//---------------------------------------------------------------------------
#include "test_dump.h"
#include "../dump.h"
#include "../undump.h"
#include <algorithm>
#include <float.h>
#include <limits.h>
//---------------------------------------------------------------------------
using namespace db;
using namespace test;
//---------------------------------------------------------------------------
bool TestDump::DoTest()
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
    if(false == TestCompSTL()) return false;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestInvaild()
{
    Value val;
    Dump d(val);
    std::cout << val << std::endl;

    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "invalid:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestBoolean()
{
    Value val(true);
    Dump d(val);
    std::cout << val << std::endl;

    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "boolean:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestInt()
{
    Value val(int64_t(LONG_LONG_MAX));
    Dump d(val);
    std::cout << val << std::endl;

    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "int:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestUInt()
{
    Value val(uint64_t(ULONG_LONG_MAX));
    Dump d(val);
    std::cout << val << std::endl;

    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "uint:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestFloat()
{
    Value val(DBL_MAX);
    Dump d(val);
    std::cout << val << std::endl;

    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "double:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestBinary()
{
    Value::Binary b(6, 'a');
    Value val(b);
    std::cout << val << std::endl;
    Dump d(val);

    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "binary:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestString()
{
    Value::String str(6, 'a');
    Value val(str);
    Dump d(val);
    std::cout << val << std::endl;

    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "string:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestList()
{
    Value v(Value::LIST);
    Value::List& list = v.GetList();
    for(int i=0; i<2; i++)
        list.push_back(Value(true));
    Value val(list);
    std::cout << val << std::endl;

    Dump d(val);
    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "list:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;
    std::cout << val << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestSet()
{
    Value v(Value::SET);
    Value::Set& set = v.GetSet();
    set.insert(Value(true));
    set.insert(Value(int64_t(1)));
    Value val(set);

    Dump d(val);
    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "set:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;
    std::cout << val << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestZSet()
{
    Value v(Value::ZSET);
    Value::ZSet& zset = v.GetZSet();
    for(int i=0; i<2; i++)
        zset.emplace(i, Value(uint64_t(i)));
    Value val(zset);
    std::cout << val << std::endl;

    Dump d(val);
    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "zset:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestHash()
{
    Value v(Value::HASH);
    Value::Hash& hash = v.GetHash();
    hash.emplace("a", Value(uint64_t(1)));
    hash.emplace("b", Value(uint64_t(2)));
    Value val(hash);
    std::cout << val << std::endl;

    Dump d(val);
    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "hash:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;
    std::cout << val << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestMix()
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
    o["list"] = Value(l1);
    o["set"] = Value(s1);
    o["zset"] = Value(zs1);
    o["hash"] = Value(h1);

    std::cout << "================" << std::endl;
        std::cout << o << std::endl;
    std::cout << "================" << std::endl;

    Dump d(o);
    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "mix:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    Undump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
static std::string NumToStr(int64_t num)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "%zu",  num);

    return buf;
}
//---------------------------------------------------------------------------
bool TestDump::TestCompSTL()
{
    int64_t size = 1024*10;
    std::list<int64_t> stl_list;
    std::unordered_set<std::string> stl_set;
    std::multimap<double, std::string> stl_zset;
    std::unordered_map<std::string, int64_t> stl_hash;

    //stl_list
    for(int64_t i=0; i<size; i++)
        stl_list.push_back(i);

    //stl_set
    for(int64_t i=0; i<size; i++)
        stl_set.insert(NumToStr(i));

    //stl_zset
    for(int64_t i=0; i<size; i++)
        stl_zset.emplace(i, NumToStr(i));

    //stl_hash
    for(int64_t i=0; i<size; i++)
        stl_hash.emplace(NumToStr(i), i);

    MY_ASSERT(size == static_cast<int64_t>(stl_list.size()));
    MY_ASSERT(size == static_cast<int64_t>(stl_set.size()));
    MY_ASSERT(size == static_cast<int64_t>(stl_zset.size()));
    MY_ASSERT(size == static_cast<int64_t>(stl_hash.size()));


    Value::List list;
    Value::Set set;
    Value::ZSet zset;
    Value::Hash hash;

    //list
    for(int64_t i=0; i<size; i++)
        list.push_back(Value(i));

    //set
    for(int64_t i=0; i<size; i++)
        set.insert(Value(NumToStr(i)));

    //zset
    for(int64_t i=0; i<size; i++)
        zset.emplace(i, Value(NumToStr(i)));

    //hash
    for(int64_t i=0; i<size; i++)
        hash.emplace(NumToStr(i), Value(i));

    MY_ASSERT(size == static_cast<int64_t>(list.size()));
    MY_ASSERT(size == static_cast<int64_t>(set.size()));
    MY_ASSERT(size == static_cast<int64_t>(zset.size()));
    MY_ASSERT(size == static_cast<int64_t>(hash.size()));

    Value vl(list);
    Value vs(set);
    Value vzs(zset);
    Value vh(hash);

    //comp list
    {
    auto v2 = list.begin();
    for(auto v1=stl_list.begin(); v1!=stl_list.end(); ++v1)
    {
        assert(*v1 == v2->GetInt());
        ++v2;
    }
    }

    //comp set
    {
    for(auto v1=stl_set.begin(); v1!=stl_set.end(); ++v1)
    {
        auto iter = set.find(Value(*v1));
        if(set.end() == iter)
            assert(0);
    }

    //comp zset
    for(auto v1=stl_zset.begin(); v1!=stl_zset.end(); ++v1)
    {
        auto iter = zset.find(v1->first);
        if(zset.end() == iter)
            assert(0);
    }

    //comp hash 
    for(auto v1=stl_hash.begin(); v1!=stl_hash.end(); ++v1)
    {
        auto iter = hash.find(v1->first);
        if(hash.end() == iter)
            assert(0);
    }

    Value mix(Value::HASH);
    mix["list"] = Value(list);
    mix["set"] = Value(set);
    mix["zset"] = Value(zset);
    mix["hash"] = Value(hash);

    MY_ASSERT(mix.SaveFile("dump.ldb"));
    Value v2;
    MY_ASSERT(v2.LoadFile("dump.ldb"));

    auto l1 = v2["list"];
    auto s1 = v2["set"];
    auto zs1 = v2["zset"];
    auto h1 = v2["hash"];

    //comp list
    {
    auto v3 = l1.GetList().begin();
    for(auto v1=stl_list.begin(); v1!=stl_list.end(); ++v1)
    {
        assert(*v1 == v3->GetInt());
        ++v3;
    }
    }

    //comp set
    for(auto v1=stl_set.begin(); v1!=stl_set.end(); ++v1)
    {
        auto iter = s1.GetSet().find(Value(*v1));
        if(s1.GetSet().end() == iter)
            assert(0);
    }

    //comp zset
    for(auto v1=stl_zset.begin(); v1!=stl_zset.end(); ++v1)
    {
        auto iter = zs1.GetZSet().find(v1->first);
        if(zs1.GetZSet().end() == iter)
            assert(0);
    }

    //comp hash 
    for(auto v1=stl_hash.begin(); v1!=stl_hash.end(); ++v1)
    {
        auto iter = h1.GetHash().find(v1->first);
        if(h1.GetHash().end() == iter)
            assert(0);
    }

    }

    return true;
}
//---------------------------------------------------------------------------
