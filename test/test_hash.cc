//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/string_value.h"
#include "../src/hash_value.h"
//---------------------------------------------------------------------------
using namespace db;
using namespace db::test;
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    //构造
    {
    HashValue hash;
    HashValue copy(hash);
    HashValue assign = hash;
    HashValue move(std::move(hash));
    HashValue assign_move = std::move(assign);

    const char* k1 = "a";
    const char* k2 = "b";
    StringValuePtr v1 = std::make_shared<StringValue>("a");
    StringValuePtr v2 = std::make_shared<StringValue>("b");
    move.Insert(k1, v1);
    assign_move.Insert(k2, v2);
    move.Swap(assign_move);
    TEST_ASSERT(v1 == assign_move.FindAsString(k1));
    TEST_ASSERT(v2 == move.FindAsString(k2));
    }

    //capacity
    {
    HashValue hash;
    TEST_ASSERT(0 == hash.Size());
    TEST_ASSERT(true == hash.Empty());

    hash.Insert("a", ValuePtr());
    TEST_ASSERT(1 == hash.Size());
    TEST_ASSERT(false == hash.Empty());
    }

    //add
    {
    std::string key0  = "empty";
    std::string key1 = "你好";
    StringValuePtr val1 = std::make_shared<StringValue>("aaa");
    std::string key2 = "hello";
    StringValuePtr val2 = std::make_shared<StringValue>("bbb");
    HashValue hash;
    TEST_ASSERT(true == hash.Insert(key1, val1));
    TEST_ASSERT(false == hash.Insert(key1, val1));
    TEST_ASSERT(true == hash.Insert(key2, val2));
    TEST_ASSERT(false == hash.Insert(key2, val2));
    TEST_ASSERT(2 == hash.Size());
    TEST_ASSERT(false == hash.Empty());

    const ValuePtr& f0 = hash.Find(key0);
    const ValuePtr& f1 = hash.Find(key1);
    const ValuePtr& f2 = hash.Find(key2);
    TEST_ASSERT(Value::NullPtr == f0);
    TEST_ASSERT(f1 == val1);
    TEST_ASSERT(f2 == val2);

    StringValuePtr sp0 = hash.FindAsString(key0);
    StringValuePtr sp1 = hash.FindAsString(key1);
    StringValuePtr sp2 = hash.FindAsString(key2);
    TEST_ASSERT(StringValue::NullPtr == sp0);
    TEST_ASSERT(sp1 == val1);
    TEST_ASSERT(sp2 == val2);
    TEST_ASSERT(sp1->val() == val1->val());
    TEST_ASSERT(sp2->val() == val2->val());

    //insert不会修改已经存在的值
    StringValuePtr val3 = std::make_shared<StringValue>("ccc");
    TEST_ASSERT(false == hash.Insert(key1, val3));
    TEST_ASSERT(val1 == hash.FindAsString(key1));
    }

    //modify
    {
    std::string key0  = "empty";
    std::string key1 = "你好";
    StringValuePtr val1 = std::make_shared<StringValue>("aaa");
    std::string key2 = "hello";
    StringValuePtr val2 = std::make_shared<StringValue>("bbb");
    HashValue hash;
    hash[key0];
    hash[key1] = val1;
    hash[key2] = val2;
    TEST_ASSERT(Value::NullPtr == hash[key0]);
    TEST_ASSERT(val1 == hash[key1]);
    TEST_ASSERT(val2 == hash[key2]);
    TEST_ASSERT(3 == hash.Size());

    hash[key1] = val2;
    TEST_ASSERT(val2 == hash[key1]);
    }

    //erase
    {
    std::string key0  = "empty";
    std::string key1 = "你好";
    StringValuePtr val1 = std::make_shared<StringValue>("aaa");
    std::string key2 = "hello";
    StringValuePtr val2 = std::make_shared<StringValue>("bbb");
    HashValue hash;
    hash[key1] = val1;
    hash[key2] = val2;

    TEST_ASSERT(false == hash.Erase(key0));
    TEST_ASSERT(true == hash.Erase(key1));
    TEST_ASSERT(true == hash.Erase(key2));
    TEST_ASSERT(true == hash.Empty());

    hash[key0];
    TEST_ASSERT(false == hash.Empty());
    hash.Clear();
    TEST_ASSERT(true == hash.Empty());
    }

    //find
    {
    std::string key0  = "empty";
    std::string key1 = "你好";
    StringValuePtr val1 = std::make_shared<StringValue>("aaa");
    std::string key2 = "hello";
    StringValuePtr val2 = std::make_shared<StringValue>("bbb");
    HashValue hash;
    hash[key1] = val1;
    hash[key2] = val2;

    TEST_ASSERT(Value::NullPtr == hash.Find(key0));
    TEST_ASSERT(val1 == hash.Find(key1));
    TEST_ASSERT(val2 == hash.Find(key2));
    TEST_ASSERT(0 == hash.Count(key0));
    TEST_ASSERT(1 == hash.Count(key1));
    TEST_ASSERT(1 == hash.Count(key2));

    //as string
    TEST_ASSERT(StringValue::NullPtr == hash.FindAsString(key0));
    TEST_ASSERT(val1 == hash.FindAsString(key1));
    TEST_ASSERT(val2 == hash.FindAsString(key2));
    }

    //iterator
    {
    int size = 1024;
    HashValue hash(size*2);
    for(int i=0; i<size; i++)
    {
        hash[std::to_string(i)] = StringValuePtr(std::make_shared<StringValue>(i));
    }
    int count = 0;
    TEST_ASSERT(static_cast<size_t>(size) == hash.Size());
    for(HashValue::ConstIterator iter=hash.Begin(); iter!=hash.End(); iter++)
    {
        count ++;
    }
    TEST_ASSERT(count == size);

    }

    //hahs{key:hash}
    {
    HashValue hash;
    std::string key = "hash";
    HashValuePtr val(new HashValue());
    hash[key] = val;

    int count = 0;
    int size = 1024;
    for(int i=0; i<size; i++)
    {
        val->Insert(std::to_string(i), StringValuePtr(new StringValue(i)));
    }
    for(HashValue::ConstIterator it=HashValue::AsHashPtr(hash.Find(key))->Begin(); it!=hash.End(); it++)
    {
        count++;
    }
    TEST_ASSERT(count == size);
    
    }

    return 0;
}
//---------------------------------------------------------------------------
