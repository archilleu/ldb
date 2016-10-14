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
    //if(false == TestInvaild())  return false;
    //if(false == TestBoolean())  return false;
    //if(false == TestInt())  return false;
    //if(false == TestUInt())  return false;
    //if(false == TestFloat())  return false;
    //if(false == TestBinary())  return false;
    //if(false == TestString())  return false;
    //if(false == TestList())  return false;
    //if(false == TestSet())  return false;
    //if(false == TestZSet())  return false;
    //if(false == TestHash())  return false;
    if(false == TestMix())  return false;

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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    UnDump ud;
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

    //l1.push_back(Value(list));
    l1.push_back(Value(set));
    //l1.push_back(Value(zset));
    //l1.push_back(Value(hash));

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
    //o["set"] = Value(s1);
    //o["zset"] = Value(zs1);
    //o["hash"] = Value(h1);

    std::cout << "================" << std::endl;
        std::cout << o << std::endl;
    std::cout << "================" << std::endl;

    Dump d(o);
    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "mix:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;

    UnDump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    /*
    //hash[]
    MY_ASSERT(o["hash"]["key0"] == Value());
    MY_ASSERT(o["hash"]["key1"] == Value(true));
    MY_ASSERT(o["hash"]["key2"] == Value(true));
    MY_ASSERT(o["hash"]["key3"] == Value(false));
    MY_ASSERT(o["hash"]["key4"] == Value(int64_t(LONG_LONG_MAX)));
    MY_ASSERT(o["hash"]["key5"] == Value(uint64_t(ULONG_LONG_MAX)));
    MY_ASSERT(o["hash"]["key6"] == Value(DBL_MAX));
    MY_ASSERT(o["hash"]["key7"] == Value("string"));
    o["hash"]["key7"] = Value("new string");
    std::cout << o["hash"]["key7"] << std::endl;

    //zset[]
    Value::List zl1 = o["zset"][1];
    std::cout << "nil:" << Value(zl1) << std::endl;

    Value::List zl2 = o["zset"][2];
    Value zlv1(zl2);
    std::cout << "true:" << zlv1 << std::endl;
    zl2.begin()->SetBoolean(false);
    Value zlv2(zl2);
    std::cout << "true:" << zlv1 << std::endl;
    std::cout << "false:" << zlv2 << std::endl;

    Value::List zl3 = o["zset"][3];
    std::cout << "true:" << Value(zl3) << std::endl;

    Value::List zl4 = o["zset"][4];
    std::cout << "false:" << Value(zl4) << std::endl;

    Value::List zl5 = o["zset"][5];
    std::cout << "LL:" << Value(zl5) << std::endl;

    Value::List zl6 = o["zset"][6];
    std::cout << "ULL:" << Value(zl6) << std::endl;

    Value::List zl7 = o["zset"][7];
    std::cout << "FM:" << Value(zl7) << std::endl;

    Value::List zl8 = o["zset"][8];
    std::cout << "string:" << Value(zl8) << std::endl;

    */
    return true;
}
//---------------------------------------------------------------------------
