//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/string_value.h"
#include "../src/zset_value.h"
#include "../src/list_value.h"
//---------------------------------------------------------------------------
using namespace db;
using namespace db::test;
//---------------------------------------------------------------------------
int main(int, char**)
{
    TestTitle();

    //构造
    {
    ZSetValue zset;
    TEST_ASSERT(true == zset.Empty());
    TEST_ASSERT(0 == zset.Size());
    }

    //拷贝移动等构造
    {
    ZSetValue zset(2045);
    size_t size = 1;
    for(size_t i=0; i<size; i++)
    {
        zset.Insert(static_cast<double>(i), i);
    }
    TEST_ASSERT(false == zset.Empty());
    TEST_ASSERT(size == zset.Size());

    ZSetValue copy(zset);
    ZSetValue copy1 = zset;
    TEST_ASSERT(false == copy.Empty());
    TEST_ASSERT(size == copy.Size());
    TEST_ASSERT(false == copy1.Empty());
    TEST_ASSERT(size == copy1.Size());

    ZSetValue move(std::move(copy));
    ZSetValue move1 = std::move(copy1);
    TEST_ASSERT(false == move.Empty());
    TEST_ASSERT(size == move.Size());
    TEST_ASSERT(false == move1.Empty());
    TEST_ASSERT(size == move1.Size());

    ZSetValue assgin = move;
    ZSetValue assgin_move = std::move(move);
    TEST_ASSERT(false == assgin.Empty());
    TEST_ASSERT(size == assgin.Size());
    TEST_ASSERT(false == assgin_move.Empty());
    TEST_ASSERT(size == assgin_move.Size());
    std::list<double> comps;
    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key(new StringValue(std::to_string(i)));
        auto got = assgin_move.Find(key);
        TEST_ASSERT(1 == zset.Count(i));
        comps.push_back(got->first.AsStringPtr()->AsDouble());
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
    ZSetValue zset;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
        zset.Insert(static_cast<double>(i), i);
    }

    std::list<long> comps;
    for(ZSetValue::ConstIterator it=zset.Begin(); it!=zset.End(); it++)
    {
        comps.push_back(it->second.AsStringPtr()->AsInt());
    }
    comps.sort();
    TEST_ASSERT(size == comps.size());
    int i = 0;
    for(auto it=comps.begin(); it!=comps.end(); it++)
    {
        TEST_ASSERT(i == *it);
        i++;
    }
    for(ZSetValue::ConstIterator it=zset.Begin(); it!=zset.End(); it++)
    {
        comps.push_back(it->second.AsStringPtr()->AsInt());
    }

    for(ZSetValue::Iterator it=zset.Begin(); it!=zset.End(); it++)
    {
        *it->second.AsStringPtr() = 2 * it->second.AsStringPtr()->AsInt();
    }
    comps.clear();
    for(ZSetValue::ConstIterator it=zset.Begin(); it!=zset.End(); it++)
    {
        comps.push_back(it->second.AsStringPtr()->AsInt());
    }
    comps.sort();
    i = 0;
    for(auto it=comps.begin(); it!=comps.end(); it++)
    {
        TEST_ASSERT(i*2 == *it);
        i++;
    }

    }

    //lookup & modifiers
    {
    ZSetValue zset;
    ObjectPtr op1 = ObjectPtr(new StringValue(1));
    const char* op2 = "2";
    const std::string op3 = "3";
    int op4 = 4;
    long op5 = 5;
    double op6 = 6;
    TEST_ASSERT(true == zset.Insert(1.0, op1));
    TEST_ASSERT(true == zset.Insert(2.0, op2));
    TEST_ASSERT(true == zset.Insert(3.0, op3));
    TEST_ASSERT(true == zset.Insert(4.0, op4));
    TEST_ASSERT(true == zset.Insert(5.0, op5));
    TEST_ASSERT(true == zset.Insert(6.0, op6));
    TEST_ASSERT(false == zset.Insert(1, op1));
    TEST_ASSERT(false == zset.Insert(2, op2));
    TEST_ASSERT(false == zset.Insert(3, op3));
    TEST_ASSERT(false == zset.Insert(4, op4));
    TEST_ASSERT(false == zset.Insert(5, op5));
    TEST_ASSERT(false == zset.Insert(6, op6));
    TEST_ASSERT(6 == zset.Size());

    TEST_ASSERT(zset.MapEnd() == zset.Find(""));
    TEST_ASSERT(op1 == zset.Find(op1)->first);
    TEST_ASSERT(1 == zset.Find(op1)->second);
    TEST_ASSERT(std::string(op2) == zset.Find(op2)->first.AsStringPtr()->val());
    TEST_ASSERT(2.0 == zset.Find(op2)->second);
    TEST_ASSERT(op3 == zset.Find(op3)->first.AsStringPtr()->AsString());
    TEST_ASSERT(3.0 == zset.Find(op3)->second);
    TEST_ASSERT(op4 == zset.Find(op4)->first.AsStringPtr()->AsInt());
    TEST_ASSERT(4.0 == zset.Find(op4)->second);
    TEST_ASSERT(op5 == zset.Find(op5)->first.AsStringPtr()->AsInt());
    TEST_ASSERT(5.0 == zset.Find(op5)->second);
    TEST_ASSERT(op6 == zset.Find(op6)->first.AsStringPtr()->AsDouble());
    TEST_ASSERT(6.0 == zset.Find(op6)->second);

    TEST_ASSERT(0==zset.Count(""));
    TEST_ASSERT(1==zset.Count(op1));
    TEST_ASSERT(1==zset.Count(op2));
    TEST_ASSERT(1==zset.Count(op3));
    TEST_ASSERT(1==zset.Count(op4));
    TEST_ASSERT(1==zset.Count(op5));
    TEST_ASSERT(1==zset.Count(op6));

    ListValuePtr list = zset.Range(-1, 10);
    for(auto it=list->Begin(); it!=list->End(); ++it)
    {
        if(
                (*it != op1)
                && (it->AsStringPtr()->AsString()!=op2) 
                && (it->AsStringPtr()->AsString()!=op3) 
                && (it->AsStringPtr()->AsInt()!=op4) 
                && (it->AsStringPtr()->AsInt()!=op5)
                && (it->AsStringPtr()->AsDouble()!=op6) 
        )
        {
            TEST_ASSERT(false);
        }

    }

    TEST_ASSERT(true == zset.Erase(op1));
    TEST_ASSERT(true == zset.Erase(op2));
    TEST_ASSERT(true == zset.Erase(op3));
    TEST_ASSERT(true == zset.Erase(op4));
    TEST_ASSERT(true == zset.Erase(op5));
    TEST_ASSERT(true == zset.Erase(op6));
    TEST_ASSERT(false == zset.Erase(op1));
    TEST_ASSERT(false == zset.Erase(op2));
    TEST_ASSERT(false == zset.Erase(op3));
    TEST_ASSERT(false == zset.Erase(op4));
    TEST_ASSERT(false == zset.Erase(op5));
    TEST_ASSERT(false == zset.Erase(op6));
    TEST_ASSERT(0 == zset.Size());
    TEST_ASSERT(true  == zset.Empty());

    list->Clear();
    list = zset.Range(-1, 10);
    TEST_ASSERT(true == list->Empty());
    }
    

    //modifiers
    {
    ZSetValue zset;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue(std::to_string(i)));
        zset.Insert(static_cast<double>(i), key);
        zset.Erase(key);
    }
    TEST_ASSERT(true == zset.Empty());
    TEST_ASSERT(0 == zset.Size());

    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue(std::to_string(i)));
        zset.Insert(static_cast<double>(i), key);
    }

    for(auto it=zset.Begin(); it!=zset.End();)
    {
        zset.Erase(it->second);
        it = zset.Begin();
    }
    TEST_ASSERT(true == zset.Empty());
    TEST_ASSERT(0 == zset.Size());


    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue(std::to_string(i)));
        zset.Insert(static_cast<double>(i), key);
    }
    zset.Clear();
    TEST_ASSERT(true == zset.Empty());
    TEST_ASSERT(0 == zset.Size());

    }

    //repeat
    {
    ZSetValue zset;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
        ObjectPtr key = ObjectPtr(new StringValue("a"));
        zset.Insert(static_cast<double>(i), key);
    }
    TEST_ASSERT(false == zset.Empty());
    TEST_ASSERT(1 == zset.Size());

    }

    return 0;
}
//---------------------------------------------------------------------------
