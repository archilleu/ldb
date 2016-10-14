//---------------------------------------------------------------------------
#include "test_dump.h"
#include "../dump.h"
#include "../undump.h"
#include <algorithm>
//---------------------------------------------------------------------------
using namespace db;
using namespace test;
//---------------------------------------------------------------------------
bool TestDump::DoTest()
{
    //if(false == TestInvaild())  return false;
    if(false == TestBoolean())  return false;
    if(false == TestInt())  return false;
    if(false == TestList())  return false;
    if(false == TestZSet())  return false;

    return true;
}
//---------------------------------------------------------------------------
bool TestDump::TestInvaild()
{
    Value val;
    Dump d(val);

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
bool TestDump::TestZSet()
{
    Value v(Value::ZSET);
    Value::ZSet& zset = v.GetZSet();
    for(int i=0; i<2; i++)
        zset.emplace(i, Value(uint64_t(i)));
    Value val(zset);

    Dump d(val);
    MY_ASSERT(d.ToBin());
    Dump::Memory bin = d.bin();
    std::cout << "zset:" << std::endl;
        for_each(bin.begin(), bin.end(), [](unsigned char c){ printf("%x,", c); });
    std::cout << std::endl;
    std::cout << val << std::endl;

    UnDump ud;
    MY_ASSERT(ud.FromBin(std::move(bin)));
    std::cout << ud.value() << std::endl;

    return true;
}
//---------------------------------------------------------------------------
