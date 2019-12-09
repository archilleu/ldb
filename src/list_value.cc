//---------------------------------------------------------------------------
#include <cassert>
#include "list_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
ListValue::ListValue()
:   Value(LIST, LINKED_LIST)
{
    return;
}
//---------------------------------------------------------------------------
ListValue::~ListValue()
{
    return;
}
//---------------------------------------------------------------------------
bool ListValue::Empty() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->empty();
    }
    else
    {
        throw type_error();
    }

    return true;
}
//---------------------------------------------------------------------------
size_t ListValue::Size() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->size();
    }
    else
    {
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Begin()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->begin();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::End()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->end();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::ConstIterator ListValue::Begin() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->begin();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::ConstIterator ListValue::End() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->end();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::ReverseIterator ListValue::RBegin()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->rbegin();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::ReverseIterator ListValue::REnd()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->rend();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::ReverseConstIterator ListValue::RBegin() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->rbegin();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::ReverseConstIterator ListValue::REnd() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->rend();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ValuePtr& ListValue::Front()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->front();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
const ValuePtr& ListValue::Front() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->front();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ValuePtr& ListValue::Back()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->back();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
const ValuePtr& ListValue::Back() const
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->back();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushFront(const ValuePtr& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->push_back(value);
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PopFront()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->pop_front();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushBack(const ValuePtr& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->push_back(value);
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PopBack()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->pop_back();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, const ValuePtr& val)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->insert(position, val);
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Erase(ConstIterator position)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->erase(position);
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Erase(ConstIterator first, ConstIterator last)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->erase(first, last);
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::Clear()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->clear();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::Sort()
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->sort();
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
template<class Compare>
void ListValue::Sort(Compare comp)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->sort(comp);
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValuePtr ListValue::AsListPtr(ValuePtr value)
{
    return std::dynamic_pointer_cast<ListValue>(value);
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
