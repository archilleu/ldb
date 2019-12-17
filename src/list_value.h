//---------------------------------------------------------------------------
#ifndef DB_LIST_VALUE_H_
#define DB_LIST_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
class ListValue : public Value
{
public:
    ListValue();
    ListValue(const ListValue& other)=default;
    ListValue(ListValue&& other)=default;
    ListValue& operator=(const ListValue& other)=default;
    ListValue& operator=(ListValue&& other)=default;
    virtual ~ListValue();

public:
    //capacity
    bool Empty() const;
    size_t Size() const;

    //iterators
    using Iterator = LinkedList::iterator;
    using ConstIterator = LinkedList::const_iterator;
    using ReverseIterator = LinkedList::reverse_iterator;
    using ReverseConstIterator = LinkedList::const_reverse_iterator;

    Iterator Begin();
    Iterator End();
    ConstIterator Begin() const;
    ConstIterator End() const;
    ReverseIterator RBegin();
    ReverseIterator REnd();
    ReverseConstIterator RBegin() const;
    ReverseConstIterator REnd() const;
    
    //element access
    ObjectPtr& Front();
    const ObjectPtr& Front() const;
    ObjectPtr& Back();
    const ObjectPtr& Back() const;

    //modifiers
    void PushFront(const ObjectPtr& value);
    void PushFront(const ObjectPtr&& value);
    void PushFront(const char* value);
    void PushFront(const String& value);
    void PushFront(String&& value);
    void PushFront(int32_t value);
    void PushFront(int64_t value);
    void PushFront(double value);
    void PopFront();

    void PushBack(const ObjectPtr& value);
    void PushBack(const ObjectPtr&& value);
    void PushBack(const char* value);
    void PushBack(const String& value);
    void PushBack(String&& value);
    void PushBack(int32_t value);
    void PushBack(int64_t value);
    void PushBack(double value);
    void PopBack();

    Iterator Insert(ConstIterator position, const ObjectPtr& value);
    Iterator Insert(ConstIterator position, const ObjectPtr&& value);
    Iterator Insert(ConstIterator position, const char* value);
    Iterator Insert(ConstIterator position, const String& value);
    Iterator Insert(ConstIterator position, String&& value);
    Iterator Insert(ConstIterator position, int32_t value);
    Iterator Insert(ConstIterator position, int64_t value);
    Iterator Insert(ConstIterator position, double value);

    Iterator Erase(ConstIterator position);
    Iterator Erase(ConstIterator first, ConstIterator last);

    void Clear();

    //自定义函数对象或函数指针排序
    template<class Compare>
    void Sort(Compare comp);
};
//---------------------------------------------------------------------------
template<class Compare>
void ListValue::Sort(Compare comp)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->sort(comp);
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
}//namespace db
//---------------------------------------------------------------------------
#endif //DB_LIST_VALUE_H_
