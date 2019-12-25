//---------------------------------------------------------------------------
#include <climits>
#include "test_inc.h"
#include "../src/string_value.h"
#include "../src/list_value.h"
#include "../src/set_value.h"
#include "../src/zset_value.h"
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
    ObjectPtr op5 = MakeObject<ZSetValue>(16);

    ObjectPtr dop1 = op1.Dup();
    ObjectPtr dop2 = op2.Dup();
    ObjectPtr dop3 = op3.Dup();
    ObjectPtr dop4 = op4.Dup();
    ObjectPtr dop5 = op5.Dup();
    }

    //string to string
    {
    ObjectPtr op1 = MakeObject<StringValue>("string");
    ObjectPtr op2 = MakeObject<StringValue>(2);
    ObjectPtr op3 = MakeObject<StringValue>(LONG_MIN);
    ObjectPtr op4 = MakeObject<StringValue>(LONG_MAX);
    ObjectPtr op5 = MakeObject<StringValue>(static_cast<size_t>(5));
    ObjectPtr op6 = MakeObject<StringValue>(1.0);
    std::cout << op1.ToString() << std::endl;
    std::cout << op2.ToString() << std::endl;
    std::cout << op3.ToString() << std::endl;
    std::cout << op4.ToString() << std::endl;
    std::cout << op5.ToString() << std::endl;
    std::cout << op6.ToString() << std::endl;
    }

    //list to string
    {
    ListValuePtr list = MakeObject<ListValue>().AsListPtr();

    ObjectPtr op1 = MakeObject<StringValue>("string");
    ObjectPtr op2 = MakeObject<StringValue>(2);
    ObjectPtr op3 = MakeObject<StringValue>(LONG_MIN);
    ObjectPtr op4 = MakeObject<StringValue>(LONG_MAX);
    ObjectPtr op5 = MakeObject<StringValue>(static_cast<size_t>(5));
    ObjectPtr op6 = MakeObject<StringValue>(1.0);

    list->PushBack(op1);
    list->PushBack(op2);
    list->PushBack(op3);
    list->PushBack(op4);
    list->PushBack(op5);
    list->PushBack(op6);

    ObjectPtr set = MakeObject<SetValue>();
    SetValuePtr setp = set.AsSetPtr();
    setp->Insert(op1);
    setp->Insert(op2);
    setp->Insert(op3);
    setp->Insert(op4);
    setp->Insert(op5);
    setp->Insert(op6);
    list->PushBack(set);

    ObjectPtr hash = MakeObject<HashValue>();
    HashValuePtr hashp = hash.AsHashPtr();
    hashp->Insert("hash1", op1);
    hashp->Insert("hash2", op2);
    hashp->Insert("hash3", op3);
    hashp->Insert("hash4", op4);
    hashp->Insert("hash5", op5);
    hashp->Insert("hash6", op6);
    list->PushBack(hash);

    ObjectPtr zset = MakeObject<ZSetValue>();
    ZSetValuePtr zsetp = zset.AsZSetPtr();
    zsetp->Insert(1.1, op1);
    zsetp->Insert(2.1, op2);
    zsetp->Insert(2.2, op3);
    zsetp->Insert(1.1, op4);
    zsetp->Insert(2.1, op5);
    zsetp->Insert(2.2, op6);
    list->PushBack(zset);

    std::cout << "list: " << list->ToString() << std::endl;
    }

    //hash value string
    {
    HashValuePtr hash = MakeObject<HashValue>().AsHashPtr();

    ObjectPtr op1 = MakeObject<StringValue>("string");
    ObjectPtr op2 = MakeObject<StringValue>(2);
    ObjectPtr op3 = MakeObject<StringValue>(LONG_MIN);
    ObjectPtr op4 = MakeObject<StringValue>(LONG_MAX);
    ObjectPtr op5 = MakeObject<StringValue>(static_cast<size_t>(5));
    ObjectPtr op6 = MakeObject<StringValue>(1.0);

    hash->Insert("hash1", op1);
    hash->Insert("hash2", op2);
    hash->Insert("hash3", op3);
    hash->Insert("hash4", op4);
    hash->Insert("hash5", op5);
    hash->Insert("hash6", op6);

    ObjectPtr l = MakeObject<ListValue>();
    hash->Insert("list", l);
    ListValuePtr list = l.AsListPtr();
    list->PushBack(op1);
    list->PushBack(op2);
    list->PushBack(op3);
    list->PushBack(op4);
    list->PushBack(op5);
    list->PushBack(op6);

    ObjectPtr set = MakeObject<SetValue>();
    hash->Insert("set", set);
    SetValuePtr setp = set.AsSetPtr();
    setp->Insert(op1);
    setp->Insert(op2);
    setp->Insert(op3);
    setp->Insert(op4);
    setp->Insert(op5);
    setp->Insert(op6);

    ObjectPtr zset = MakeObject<ZSetValue>();
    hash->Insert("zset", zset);
    ZSetValuePtr zsetp = zset.AsZSetPtr();
    zsetp->Insert(1.1, op1);
    zsetp->Insert(2.1, op2);
    zsetp->Insert(3.2, op3);
    zsetp->Insert(4.1, op4);
    zsetp->Insert(5.1, op5);
    zsetp->Insert(6.2, op6);

    std::cout << "hash:" << hash->ToString() << std::endl;
    }

    //set value string
    {
    ObjectPtr op1 = MakeObject<StringValue>("string");
    ObjectPtr op2 = MakeObject<StringValue>(2);
    ObjectPtr op3 = MakeObject<StringValue>(LONG_MIN);
    ObjectPtr op4 = MakeObject<StringValue>(LONG_MAX);
    ObjectPtr op5 = MakeObject<StringValue>(static_cast<size_t>(5));
    ObjectPtr op6 = MakeObject<StringValue>(1.0);

    SetValuePtr set = MakeObject<SetValue>().AsSetPtr();
    set->Insert(op1);
    set->Insert(op2);
    set->Insert(op3);
    set->Insert(op4);
    set->Insert(op5);
    set->Insert(op6);

    ObjectPtr h = MakeObject<HashValue>();
    set->Insert(h);
    HashValuePtr hash = h.AsHashPtr();
    hash->Insert("hash1", op1);
    hash->Insert("hash2", op2);
    hash->Insert("hash3", op3);
    hash->Insert("hash4", op4);
    hash->Insert("hash5", op5);
    hash->Insert("hash6", op6);

    ObjectPtr l = MakeObject<ListValue>();
    set->Insert(l);
    ListValuePtr list = l.AsListPtr();
    list->PushBack(op1);
    list->PushBack(op2);
    list->PushBack(op3);
    list->PushBack(op4);
    list->PushBack(op5);
    list->PushBack(op6);

    ObjectPtr zset = MakeObject<ZSetValue>();
    set->Insert(zset);
    ZSetValuePtr zsetp = zset.AsZSetPtr();
    zsetp->Insert(1.1, op1);
    zsetp->Insert(2.2, op2);
    zsetp->Insert(3.3, op3);
    zsetp->Insert(4.4, op4);
    zsetp->Insert(5.5, op5);
    zsetp->Insert(6.6, op6);

    std::cout << "set:" << set->ToString() << std::endl;
    }

    //zset value string
    {
    ObjectPtr op1 = MakeObject<StringValue>("string");
    ObjectPtr op2 = MakeObject<StringValue>(2);
    ObjectPtr op3 = MakeObject<StringValue>(LONG_MIN);
    ObjectPtr op4 = MakeObject<StringValue>(LONG_MAX);
    ObjectPtr op5 = MakeObject<StringValue>(static_cast<size_t>(5));
    ObjectPtr op6 = MakeObject<StringValue>(1.0);

    ZSetValuePtr zset = MakeObject<ZSetValue>().AsZSetPtr();
    zset->Insert(1.1, op1);
    zset->Insert(2.2, op2);
    zset->Insert(3.3, op3);
    zset->Insert(4.4, op4);
    zset->Insert(5.5, op5);
    zset->Insert(6.6, op6);

    ObjectPtr s = MakeObject<SetValue>();
    zset->Insert(1.0, s);
    SetValuePtr set = s.AsSetPtr();
    set->Insert(op1);
    set->Insert(op2);
    set->Insert(op3);
    set->Insert(op4);
    set->Insert(op5);
    set->Insert(op6);

    ObjectPtr h = MakeObject<HashValue>();
    zset->Insert(2.0, h);
    HashValuePtr hash = h.AsHashPtr();
    hash->Insert("hash1", op1);
    hash->Insert("hash2", op2);
    hash->Insert("hash3", op3);
    hash->Insert("hash4", op4);
    hash->Insert("hash5", op5);
    hash->Insert("hash6", op6);

    ObjectPtr l = MakeObject<ListValue>();
    zset->Insert(3.0, l);
    ListValuePtr list = l.AsListPtr();
    list->PushBack(op1);
    list->PushBack(op2);
    list->PushBack(op3);
    list->PushBack(op4);
    list->PushBack(op5);
    list->PushBack(op6);

    std::cout << "zset:" << zset->ToString() << std::endl;
    }
    return 0;
}
//---------------------------------------------------------------------------
