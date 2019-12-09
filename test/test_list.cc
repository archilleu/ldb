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
    list.PushFront(StringValuePtr(new StringValue(std::to_string(i))));
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
    TEST_ASSERT(static_cast<long>(i) == StringValue::AsStringPtr(assgin_move.Front())->AsInt());
    list.PopFront();
    }
    }

    //iterator
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    list.PushFront(StringValuePtr(new StringValue(std::to_string(i))));
    }

    size_t num = 0;
    for(ListValue::ConstIterator it=list.Begin(); it!=list.End(); it++)
    {
    TEST_ASSERT(static_cast<long>(num++)==StringValue::AsStringPtr(*it)->AsInt());
    }

    num = 0;
    for(ListValue::Iterator it=list.Begin(); it!=list.End(); it++)
    {
    *(StringValue::AsStringPtr(*it)) = std::to_string(num);
    }

    num = 0;
    for(ListValue::ConstIterator it=list.Begin(); it!=list.End(); it++)
    {
    num++;
    TEST_ASSERT(static_cast<long>(num*2)==StringValue::AsStringPtr(*it)->AsInt());
    }

    num = size;
    for(ListValue::ReverseIterator it=list.RBegin(); it!=list.REnd(); it++)
    {
    num--;
    TEST_ASSERT(static_cast<long>(num*2)==StringValue::AsStringPtr(*it)->AsInt());
    }

    }

    //font back
    {
    ListValue list;
    list.PushBack(StringValuePtr(new StringValue("a")));
    TEST_ASSERT("a" == StringValue::AsStringPtr(list.Front())->val());
    *(StringValue::AsStringPtr(list.Front())) = "b";
    TEST_ASSERT("b" == StringValue::AsStringPtr(list.Front())->val());
    *(StringValue::AsStringPtr(list.Back())) = "a";
    TEST_ASSERT("a" == StringValue::AsStringPtr(list.Back())->val());
    }

    //push pop front
    {
    ListValue list;
    size_t size = 1024;
    for(size_t i=0; i<size; i++)
    {
    list.PushFront(StringValuePtr(new StringValue(std::to_string(i))));
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    for(size_t i=0; i<size; i++)
    {
    TEST_ASSERT(static_cast<long>(i) == StringValue::AsStringPtr(list.Front())->AsInt());
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
    list.PushBack(StringValuePtr(new StringValue(std::to_string(i))));
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    for(size_t i=size; static_cast<ssize_t>(i)>=0; i--)
    {
    TEST_ASSERT(static_cast<long>(i) == StringValue::AsStringPtr(list.Back())->AsInt());
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
    ListValue::Iterator it = list.Insert(list.Begin(), StringValuePtr(new StringValue(std::to_string(i))));
    TEST_ASSERT(static_cast<long>(i) == StringValue::AsStringPtr(*it)->AsInt());
    }
    TEST_ASSERT(false == list.Empty());
    TEST_ASSERT(size == list.Size());

    for(size_t i=size; static_cast<ssize_t>(i)>=0; i--)
    {
    ListValue::Iterator it = list.Erase(++list.End());
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
    ListValue::Iterator it = list.Insert(list.Begin(), StringValuePtr(new StringValue(std::to_string(i))));
    TEST_ASSERT(static_cast<long>(i) == StringValue::AsStringPtr(*it)->AsInt());
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
    ListValue::Iterator it = list.Insert(list.Begin(), StringValuePtr(new StringValue(std::to_string(i))));
    TEST_ASSERT(static_cast<long>(i) == StringValue::AsStringPtr(*it)->AsInt());
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
    list.PushBack(StringValuePtr(new StringValue(std::to_string(std::rand()))));
    }
    list.Sort();

    for(ListValue::ConstIterator it=list.Begin(); it!=--list.End(); it++)
    {
        double v1 = StringValue::AsStringPtr(*it)->AsDouble();
        double v2 = StringValue::AsStringPtr(*(it++))->AsDouble();
        TEST_ASSERT(v1 <= v2);
    }

    }

    return 0;
}
//---------------------------------------------------------------------------
