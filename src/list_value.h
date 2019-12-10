//---------------------------------------------------------------------------
#ifndef DB_LIST_VALUE_H_
#define DB_LIST_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
//hash pointer define
using ListValuePtr = std::shared_ptr<class ListValue>;
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
    ValuePtr& Front();
    const ValuePtr& Front() const;
    ValuePtr& Back();
    const ValuePtr& Back() const;

    //modifiers
    void PushFront(const ValuePtr& value);
    void PopFront();
    void PushBack(const ValuePtr& value);
    void PopBack();

    Iterator Insert(ConstIterator position, const ValuePtr& val);
    Iterator Erase(ConstIterator position);
    Iterator Erase(ConstIterator first, ConstIterator last);
    void Clear();

    //自定义函数对象或函数指针排序
    template<class Compare>
    void Sort(Compare comp);

    static ListValuePtr AsListPtr(ValuePtr value);

public:
    const static ListValue NullPtr;
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
