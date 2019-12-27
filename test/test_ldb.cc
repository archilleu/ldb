//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/dump.h"
#include "../src/undump.h"
#include "../src/hash_value.h"
#include "../src/server.h"
//---------------------------------------------------------------------------
using namespace db;
using namespace db::test;
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    //构造
    {

    const char* path = "./test.rdb";
    Server server1(16);
    server1.dbs().front().Insert("key1", 1);
    server1.dbs().front().Insert("key2", "value2");

    Dump dump(server1);
    TEST_ASSERT(true == dump.Save(path));

    Server server2(16);
    Undump undump(server2);
    TEST_ASSERT(true == undump.Load(path));

    }

    return 0;
}
//---------------------------------------------------------------------------
