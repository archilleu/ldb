//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/string_value.h"
#include "../src/list_value.h"
#include "../src/set_value.h"
#include "../src/hash_value.h"
#include "../src/object_ptr.h"
//---------------------------------------------------------------------------
using namespace db;
using namespace db::test;
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    //构造
    {
    ObjectPtr op = ObjectPtr();
    TEST_ASSERT(0 == op.object());
    
    ObjectPtr op1 = MakeObject<StringValue>("string");
    ObjectPtr op2 = MakeObject<ListValue>();
    ObjectPtr op3 = MakeObject<HashValue>(16);
    ObjectPtr op4 = MakeObject<SetValue>(16);

    op4.ToString();
    }

    return 0;
}
//---------------------------------------------------------------------------
