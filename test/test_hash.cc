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
    ObjectPtr v1(new StringValue("a"));
    ObjectPtr v2(new StringValue("b"));
    move.Insert(k1, v1);
    assign_move.Insert(k2, v2);
    move.Swap(assign_move);
    TEST_ASSERT(v1 == assign_move.Find(k1)->second);
    TEST_ASSERT(v2 == move.Find(k2)->second);
    }

    //capacity
    {
    HashValue hash;
    hash.Reserve(1024);
    TEST_ASSERT(0 == hash.Size());
    TEST_ASSERT(true == hash.Empty());

    hash.Insert("a", ObjectPtr());
    TEST_ASSERT(1 == hash.Size());
    TEST_ASSERT(false == hash.Empty());
    hash.Rehash(2048);
    }

    //add
    {
    std::string key0  = "empty";
    std::string key1 = "你好";
    ObjectPtr val1(new StringValue("aaa"));
    std::string key2 = "hello";
    ObjectPtr val2(new StringValue("bbb"));
    HashValue hash;
    TEST_ASSERT(true == hash.Insert(key1, val1));
    TEST_ASSERT(false == hash.Insert(key1, val1));
    TEST_ASSERT(true == hash.Insert(key2, val2));
    TEST_ASSERT(false == hash.Insert(key2, val2));
    TEST_ASSERT(2 == hash.Size());
    TEST_ASSERT(false == hash.Empty());

    const HashValue::ConstIterator f0 = hash.Find(key0);
    const ObjectPtr& f1 = hash.Find(key1)->second;
    const ObjectPtr& f2 = hash.Find(key2)->second;
    TEST_ASSERT(hash.End() == f0);
    TEST_ASSERT(f1 == val1);
    TEST_ASSERT(f2 == val2);

    HashValue::Iterator sp1 = hash.Find(key1);
    HashValue::Iterator sp2 = hash.Find(key2);
    TEST_ASSERT(hash.End() == f0);
    sp1->second = val2;
    sp2->second = val1;
    TEST_ASSERT(sp1->second == val2);
    TEST_ASSERT(sp2->second == val1);
    TEST_ASSERT(sp1->second.AsStringPtr()->val() == val2.AsStringPtr()->val());
    TEST_ASSERT(sp2->second.AsStringPtr()->val() == val1.AsStringPtr()->val());

    //insert不会修改已经存在的值
    ObjectPtr val3(new StringValue("ccc"));
    TEST_ASSERT(false == hash.Insert(key1, val3));
    TEST_ASSERT(val1 == hash.Find(key2)->second);
    }

    //modify
    {
    std::string key0  = "empty";
    std::string key1 = "你好";
    ObjectPtr val1(new StringValue("aaa"));
    std::string key2 = "hello";
    ObjectPtr val2(new StringValue("bbb"));
    HashValue hash;
    hash[key0];
    hash[key1] = val1;
    hash[key2] = val2;
    TEST_ASSERT(ObjectPtr() == hash[key0]);
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
    ObjectPtr val1(new StringValue("aaa"));
    std::string key2 = "hello";
    ObjectPtr val2(new StringValue("bbb"));
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
    ObjectPtr val1(new StringValue("aaa"));
    std::string key2 = "hello";
    ObjectPtr val2(new StringValue("bbb"));
    HashValue hash;
    hash[key1] = val1;
    hash[key2] = val2;

    TEST_ASSERT(hash.End() == hash.Find(key0));
    TEST_ASSERT(val1 == hash.Find(key1)->second);
    TEST_ASSERT(val2 == hash.Find(key2)->second);
    TEST_ASSERT(0 == hash.Count(key0));
    TEST_ASSERT(1 == hash.Count(key1));
    TEST_ASSERT(1 == hash.Count(key2));

    }

    //iterator
    {
    int size = 1024;
    HashValue hash(size*2);
    for(int i=0; i<size; i++)
    {
        hash[std::to_string(i)] = ObjectPtr(new StringValue(i));
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
    ObjectPtr val(new HashValue());
    hash[key] = val;

    int count = 0;
    int size = 1024;
    for(int i=0; i<size; i++)
    {
        val.AsHashPtr()->Insert(std::to_string(i), ObjectPtr(new StringValue(i)));
    }
    for(HashValue::ConstIterator it=hash.Find(key)->second.AsHashPtr()->Begin(); it!=hash.End(); it++)
    {
        count++;
    }
    TEST_ASSERT(count == size);
    
    }

    //iterators
    {
    std::string k1 = "1";
    std::string k2 = "2";
    std::string k3 = "3";
    std::string k4 = "4";
    std::string k5 = "5";
    std::string k6 = "6";
    std::string k7 = "7";
    std::string k8 = "8";
    std::string k9 = "9";
    std::string k10_ = "10";
    std::string k11_ = "11";
    std::string k12_ = "12";
    HashValue hash(2048);
    for(size_t i=0; i<10; i++)
    {
        std::string k11 = k1 + std::to_string(i);
        std::string k21 = k2 + std::to_string(i);
        std::string k31 = k3 + std::to_string(i);
        std::string k41 = k4 + std::to_string(i);
        std::string k51 = k5 + std::to_string(i);
        std::string k61 = k6 + std::to_string(i);
        std::string k71 = k7 + std::to_string(i);
        std::string k81 = k8 + std::to_string(i);
        std::string k91 = k9 + std::to_string(i);
        std::string k101 = k10_ + std::to_string(i);
        std::string k111 = k11_ + std::to_string(i);
        std::string k121 = k12_ + std::to_string(i);
        TEST_ASSERT(true == hash.Insert(k11, ObjectPtr(new StringValue(i))));
        TEST_ASSERT(true == hash.Insert(std::move(k21), ObjectPtr(new StringValue(i))));
        TEST_ASSERT(true == hash.Insert((k31), ObjectPtr(new StringValue(i))));
        TEST_ASSERT(true == hash.Insert(std::move(k41), ObjectPtr(new StringValue(i))));
        TEST_ASSERT(true == hash.Insert((k51), static_cast<int32_t>(i)));
        TEST_ASSERT(true == hash.Insert(std::move(k61), static_cast<int32_t>(i)));
        TEST_ASSERT(true == hash.Insert((k71), static_cast<int64_t>(i)));
        TEST_ASSERT(true == hash.Insert(std::move(k81), static_cast<int64_t>(i)));
        TEST_ASSERT(true == hash.Insert((k91), (static_cast<double>(i)*1.0)));
        TEST_ASSERT(true == hash.Insert(std::move(k101), (static_cast<double>(i)*1.0)));
        hash[k111] = ObjectPtr(new StringValue(i));
        hash[std::move(k121)] = ObjectPtr(new StringValue(i));
    }
    int count = 0;
    for(auto it=hash.Begin(); it!=hash.End(); it++)
    {
        count++;
    }
    TEST_ASSERT(10*12 == count);

    for(size_t i=0; i<10; i++)
    {
        std::string k11 = k1 + std::to_string(i);
        std::string k21 = k2 + std::to_string(i);
        std::string k31 = k3 + std::to_string(i);
        std::string k41 = k4 + std::to_string(i);
        std::string k51 = k5 + std::to_string(i);
        std::string k61 = k6 + std::to_string(i);
        std::string k71 = k7 + std::to_string(i);
        std::string k81 = k8 + std::to_string(i);
        std::string k91 = k9 + std::to_string(i);

        TEST_ASSERT(hash.Find(k11)->second.AsStringPtr()->AsInt() == static_cast<long>(i));
        TEST_ASSERT(hash.Find(k21.c_str())->second.AsStringPtr()->AsInt() == static_cast<long>(i));
        TEST_ASSERT(hash.Find(k31)->second.AsStringPtr()->AsInt() == static_cast<long>(i));
        TEST_ASSERT(hash.Find(k41.c_str())->second.AsStringPtr()->AsInt() == static_cast<long>(i));
        TEST_ASSERT(hash.Find(k51)->second.AsStringPtr()->AsInt() == static_cast<long>(i));
        TEST_ASSERT(hash.Find(k61.c_str())->second.AsStringPtr()->AsInt() == static_cast<long>(i));
        TEST_ASSERT(hash.Find(k91)->second.AsStringPtr()->AsDouble() == (static_cast<double>(i))*1.0);
        TEST_ASSERT(hash.Find(k91.c_str())->second.AsStringPtr()->AsDouble() == static_cast<double>(i)*1.0);
    }

    }

    return 0;
}
//---------------------------------------------------------------------------
