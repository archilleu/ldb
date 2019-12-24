//---------------------------------------------------------------------------
#include "test_inc.h"
#include "../src/string_value.h"
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
    ListValue list;
    TEST_ASSERT(true == list.Empty());
    TEST_ASSERT(0 == list.Size());
    }

    //拷贝移动等构造
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    list.PushBack(ObjectPtr(new StringValue(std::to_string(i))));
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    ListValue copy(list);
    ListValue copy1 = list;
    TEST_ASSERT(false == copy.Empty());
    TEST_ASSERT(size == copy.Size());
    TEST_ASSERT(false == copy1.Empty());
    TEST_ASSERT(size == copy1.Size());

    ListValue move(std::move(copy));
    ListValue move1 = std::move(copy1);
    TEST_ASSERT(false == move.Empty());
    TEST_ASSERT(size == move.Size());
    TEST_ASSERT(false == move1.Empty());
    TEST_ASSERT(size == move1.Size());

    ListValue assgin = move;
    ListValue assgin_move = std::move(move);
    TEST_ASSERT(false == assgin.Empty());
    TEST_ASSERT(size == assgin.Size());
    TEST_ASSERT(false == assgin_move.Empty());
    TEST_ASSERT(size == assgin_move.Size());
    for(size_t i=0; i<size; i++)
    {
    TEST_ASSERT(static_cast<long>(i) == assgin_move.Front().AsStringPtr()->AsInt());
    assgin_move.PopFront();
    }
    }

    //iterator
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    list.PushFront(ObjectPtr(new StringValue(std::to_string(i))));
    }

    size_t num = 0;
    for(ListValue::ConstIterator it=list.Begin(); it!=list.End(); it++)
    {
    TEST_ASSERT(static_cast<long>(num++)==it->AsStringPtr()->AsInt());
    }

    num = 0;
    for(ListValue::Iterator it=list.Begin(); it!=list.End(); it++)
    {
    long test = static_cast<long>((num++)*2);
    std::string s = std::to_string(test);
    ObjectPtr sp = *it;
    *sp.AsStringPtr() = s;
    }

    num = 0;
    for(ListValue::ConstIterator it=list.Begin(); it!=list.End(); it++)
    {
    long test = static_cast<long>((num++)*2);
    TEST_ASSERT(test==it->AsStringPtr()->AsInt());
    }

    num = --size;
    for(ListValue::ReverseIterator it=list.RBegin(); it!=list.REnd(); it++)
    {
    long test = static_cast<long>((num--)*2);
    TEST_ASSERT(static_cast<long>(test)==it->AsStringPtr()->AsInt());
    }

    }

    //font back
    {
    ListValue list;
    list.PushBack(ObjectPtr(new StringValue("a")));
    TEST_ASSERT(std::string("a") == list.Front().AsStringPtr()->val());
    *list.Front().AsStringPtr() = "b";
    TEST_ASSERT(std::string("b") == list.Front().AsStringPtr()->val());
    *list.Back().AsStringPtr() = "a";
    TEST_ASSERT(std::string("a") == list.Back().AsStringPtr()->val());
    }

    //push pop front
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    list.PushFront(ObjectPtr(new StringValue(std::to_string(i))));
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    for(size_t i=0; i<size; i++)
    {
    TEST_ASSERT(static_cast<long>(i) == list.Front().AsStringPtr()->AsInt());
    list.PopFront();
    }
    TEST_ASSERT(true == list.Empty());
    TEST_ASSERT(0 == list.Size());
    }

    //push pop back
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    list.PushBack(ObjectPtr(new StringValue(std::to_string(i))));
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    for(size_t i=size-1; static_cast<ssize_t>(i)>=0; i--)
    {
    TEST_ASSERT(static_cast<long>(i) == list.Back().AsStringPtr()->AsInt());
    list.PopBack();
    }
    TEST_ASSERT(true == list.Empty());
    TEST_ASSERT(0 == list.Size());
    }
    
    //insert erase
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    ListValue::Iterator it = list.Insert(list.Begin(), ObjectPtr(new StringValue(std::to_string(i))));
    TEST_ASSERT(static_cast<long>(i) == it->AsStringPtr()->AsInt());
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    for(size_t i=size-1; static_cast<ssize_t>(i)>=0; i--)
    {
    ListValue::Iterator it = list.Erase(--list.End());
    TEST_ASSERT(list.End() == it);
    }
    TEST_ASSERT(true == list.Empty());
    TEST_ASSERT(0 == list.Size());
    }

    //insert erase
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    ListValue::Iterator it = list.Insert(list.Begin(), ObjectPtr(new StringValue(std::to_string(i))));
    TEST_ASSERT(static_cast<long>(i) == it->AsStringPtr()->AsInt());
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    list.Erase(list.Begin(), list.End());
    TEST_ASSERT(true == list.Empty());
    TEST_ASSERT(0 == list.Size());
    }

    //clear
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    ListValue::Iterator it = list.Insert(list.Begin(), ObjectPtr(new StringValue(std::to_string(i))));
    TEST_ASSERT(static_cast<long>(i) == it->AsStringPtr()->AsInt());
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    list.Clear();
    TEST_ASSERT(true == list.Empty());
    TEST_ASSERT(0 == list.Size());
    }

    //sort
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    list.PushBack(ObjectPtr(new StringValue(std::to_string(std::rand()))));
    }
    list.Sort([](const ObjectPtr& left, const ObjectPtr& right)->
            bool
            {
            return left.AsStringPtr()->AsInt()<right.AsStringPtr()->AsInt(); 
            });

    for(ListValue::ConstIterator it=list.Begin(); it!=--list.End(); it++)
    {
        double v1 = it->AsStringPtr()->AsDouble();
        double v2 = (++it)->AsStringPtr()->AsDouble();
        it--;
        TEST_ASSERT(v1 <= v2);
    }
    }

    //modifiers
    {
    std::string k1 = "1";
    std::string k2 = "2";
    std::string k3 = "3";
    std::string k4 = "4";
    std::string k5 = "5";
    ListValue list;
    ObjectPtr o1(new StringValue(k1));
    list.PushFront(o1);
    list.PushFront(new StringValue(k2));
    list.PushFront(k3);
    list.PushFront(k4.c_str());
    list.PushFront(std::move(k5));
    list.PushFront(6);
    list.PushFront(7L);
    list.PushFront(8.0);
    while(!list.Empty())
    {
        list.PopFront();
    }

    list.PushBack(o1);
    list.PushBack(new StringValue(k2));
    list.PushBack(k3);
    list.PushBack(k4.c_str());
    list.PushBack(std::move(k5));
    list.PushBack(6);
    list.PushBack(7L);
    list.PushBack(8.0);
    while(!list.Empty())
    {
        list.PopBack();
    }

    list.Insert(list.Begin(), o1);
    list.Insert(list.Begin(), new StringValue(k2));
    list.Insert(list.Begin(), k3);
    list.Insert(list.Begin(), k4.c_str());
    list.Insert(list.Begin(), std::move(k5));
    list.Insert(list.Begin(), 6);
    list.Insert(list.Begin(), 7L);
    list.Insert(list.Begin(), 8.0);
    while(!list.Empty())
    {
        list.PopFront();
    }
    }

    return 0;
}
//---------------------------------------------------------------------------
