//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/string_value.h"
#include "../src/set_value.h"
//---------------------------------------------------------------------------
using namespace db;
using namespace db::test;
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    //构造
    {
    SetValue set;
    TEST_ASSERT(true == set.Empty());
    TEST_ASSERT(0 == set.Size());
    }

    //拷贝移动等构造
    {
    SetValue set;
    set.Reserve(2045);
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
        Value* value = new StringValue(std::to_string(i));
        set.Insert(ObjectPtr(value));
    }
    TEST_ASSERT(false == set.Empty());
    TEST_ASSERT(size == set.Size());

    SetValue copy(set);
    SetValue copy1 = set;
    TEST_ASSERT(false == copy.Empty());
    TEST_ASSERT(size == copy.Size());
    TEST_ASSERT(false == copy1.Empty());
    TEST_ASSERT(size == copy1.Size());

    SetValue move(std::move(copy));
    SetValue move1 = std::move(copy1);
    TEST_ASSERT(false == move.Empty());
    TEST_ASSERT(size == move.Size());
    TEST_ASSERT(false == move1.Empty());
    TEST_ASSERT(size == move1.Size());

    SetValue assgin = move;
    SetValue assgin_move = std::move(move);
    TEST_ASSERT(false == assgin.Empty());
    TEST_ASSERT(size == assgin.Size());
    TEST_ASSERT(false == assgin_move.Empty());
    TEST_ASSERT(size == assgin_move.Size());
    assgin_move.Rehash(2048);
    std::list<long> comps;
    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key(new StringValue(std::to_string(i)));
        auto got = assgin_move.Find(key);
        TEST_ASSERT(1 == set.Count(key));
        comps.push_back(got->AsStringPtr()->AsInt());
    }
    comps.sort();
    TEST_ASSERT(size == comps.size());
    int i=0;
    for(auto it=comps.begin(); it!=comps.end(); it++)
    {
        TEST_ASSERT(i == *it);
        i++;
    }
    }

    //iterator
    {
    SetValue set;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
        set.Insert(ObjectPtr(new StringValue(std::to_string(i))));
    }

    std::list<long> comps;
    for(SetValue::ConstIterator it=set.Begin(); it!=set.End(); it++)
    {
        comps.push_back(it->AsStringPtr()->AsInt());
    }
    comps.sort();
    TEST_ASSERT(size == comps.size());
    int i = 0;
    for(auto it=comps.begin(); it!=comps.end(); it++)
    {
        TEST_ASSERT(i == *it);
        i++;
    }
    for(SetValue::ConstIterator it=set.Begin(); it!=set.End(); it++)
    {
        comps.push_back(it->AsStringPtr()->AsInt());
    }

    }

    //lookup & modifiers
    {
    SetValue set;
    ObjectPtr op1 = ObjectPtr(new StringValue(1));
    const char* op2 = "2";
    const std::string op3 = "3";
    int op4 = 4;
    long op5 = 5;
    double op6 = 6;
    TEST_ASSERT(true == set.Insert(op1));
    TEST_ASSERT(true == set.Insert(op2));
    TEST_ASSERT(true == set.Insert(op3));
    TEST_ASSERT(true == set.Insert(op4));
    TEST_ASSERT(true == set.Insert(op5));
    TEST_ASSERT(true == set.Insert(op6));
    TEST_ASSERT(false == set.Insert(op1));
    TEST_ASSERT(false == set.Insert(op2));
    TEST_ASSERT(false == set.Insert(op3));
    TEST_ASSERT(false == set.Insert(op4));
    TEST_ASSERT(false == set.Insert(op5));
    TEST_ASSERT(false == set.Insert(op6));
    TEST_ASSERT(6 == set.Size());

    TEST_ASSERT(set.End() == set.Find(""));
    TEST_ASSERT(op1 == *set.Find(op1));
    TEST_ASSERT(std::string(op2) == set.Find(op2)->AsStringPtr()->val());
    TEST_ASSERT(std::string(op3) == set.Find(op3)->AsStringPtr()->val());
    TEST_ASSERT(op4 == set.Find(op4)->AsStringPtr()->AsInt());
    TEST_ASSERT(op5 == set.Find(op5)->AsStringPtr()->AsInt());
    TEST_ASSERT(op6 == set.Find(op6)->AsStringPtr()->AsDouble());

    TEST_ASSERT(1==set.Count(op1));
    TEST_ASSERT(1==set.Count(op2));
    TEST_ASSERT(1==set.Count(op3));
    TEST_ASSERT(1==set.Count(op4));
    TEST_ASSERT(1==set.Count(op5));
    TEST_ASSERT(1==set.Count(op6));

    TEST_ASSERT(true == set.Erase(op1));
    TEST_ASSERT(true == set.Erase(op2));
    TEST_ASSERT(true == set.Erase(op3));
    TEST_ASSERT(true == set.Erase(op4));
    TEST_ASSERT(true == set.Erase(op5));
    TEST_ASSERT(true == set.Erase(op6));
    TEST_ASSERT(false == set.Erase(op1));
    TEST_ASSERT(false == set.Erase(op2));
    TEST_ASSERT(false == set.Erase(op3));
    TEST_ASSERT(false == set.Erase(op4));
    TEST_ASSERT(false == set.Erase(op5));
    TEST_ASSERT(false == set.Erase(op6));
    TEST_ASSERT(0 == set.Size());
    TEST_ASSERT(true  == set.Empty());
    }
    

    //modifiers
    {
    SetValue set;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue(std::to_string(i)));
        set.Insert(key);
        set.Erase(key);
    }
    TEST_ASSERT(true == set.Empty());
    TEST_ASSERT(0 == set.Size());

    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue(std::to_string(i)));
        set.Insert(key);
    }

    for(auto it=set.Begin(); it!=set.End();)
    {
        set.Erase(it);
        it = set.Begin();
    }
    TEST_ASSERT(true == set.Empty());
    TEST_ASSERT(0 == set.Size());

    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue(std::to_string(i)));
        set.Insert(key);
    }
    set.Erase(set.Begin(), set.End());
    TEST_ASSERT(true == set.Empty());
    TEST_ASSERT(0 == set.Size());

    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue(std::to_string(i)));
        set.Insert(key);
    }
    set.Clear();
    TEST_ASSERT(true == set.Empty());
    TEST_ASSERT(0 == set.Size());

    }

    //repeat
    {
    SetValue set;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue("a"));
        set.Insert(key);
    }
    TEST_ASSERT(false == set.Empty());
    TEST_ASSERT(1 == set.Size());

    }

    //dup object ptr
    {
    ObjectPtr op(new StringValue("a"));
    ObjectPtr dup = op.Dup();
    TEST_ASSERT(op == dup);
    TEST_ASSERT(false ==(op != dup));
    }

    return 0;
}
//---------------------------------------------------------------------------
