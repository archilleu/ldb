//---------------------------------------------------------------------------
#include "list_value.h"
#include "object_ptr.h"
#include "string_value.h"
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
ObjectPtr& ListValue::Front()
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
const ObjectPtr& ListValue::Front() const
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
ObjectPtr& ListValue::Back()
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
const ObjectPtr& ListValue::Back() const
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
void ListValue::PushFront(const ObjectPtr& value)
{
    PushFront(ObjectPtr(value));
}
//---------------------------------------------------------------------------
void ListValue::PushFront(const ObjectPtr&& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(value);
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushFront(const char* value)
{
    PushFront(String(value));
}
//---------------------------------------------------------------------------
void ListValue::PushFront(const String& value)
{
    PushFront(String(value));
}
//---------------------------------------------------------------------------
void ListValue::PushFront(String&& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(ObjectPtr(new StringValue(value)));
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushFront(int32_t value)
{
    PushFront(static_cast<int64_t>(value));
}
//---------------------------------------------------------------------------
void ListValue::PushFront(int64_t value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(ObjectPtr(new StringValue(value)));
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushFront(double value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(ObjectPtr(new StringValue(value)));
        return;
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
        this->val_.linked_list->pop_front();
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushBack(const ObjectPtr& value)
{
    PushFront(ObjectPtr(value));
}
//---------------------------------------------------------------------------
void ListValue::PushBack(const ObjectPtr&& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(value);
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushBack(const char* value)
{
    PushFront(String(value));
}
//---------------------------------------------------------------------------
void ListValue::PushBack(const String& value)
{
    PushFront(String(value));
}
//---------------------------------------------------------------------------
void ListValue::PushBack(String&& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(ObjectPtr(new StringValue(value)));
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushBack(int32_t value)
{
    PushFront(static_cast<int64_t>(value));
}
//---------------------------------------------------------------------------
void ListValue::PushBack(int64_t value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(ObjectPtr(new StringValue(value)));
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void ListValue::PushBack(double value)
{
    if(LINKED_LIST == this->encoding_)
    {
        this->val_.linked_list->push_back(ObjectPtr(new StringValue(value)));
        return;
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
        this->val_.linked_list->pop_back();
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, const ObjectPtr& value)
{
    return Insert(position, ObjectPtr(value));
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, const ObjectPtr&& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->insert(position, std::move(value));
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, const char* value)
{
    return Insert(position, String(value));
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, const String& value)
{
    return Insert(position, String(value));
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, String&& value)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->insert(position, ObjectPtr(new StringValue(value)));
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, int32_t value)
{
    return Insert(position, static_cast<int64_t>(value));
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, int64_t value)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->insert(position, ObjectPtr(new StringValue(value)));
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ListValue::Iterator ListValue::Insert(ConstIterator position, double value)
{
    if(LINKED_LIST == this->encoding_)
    {
        return this->val_.linked_list->insert(position, ObjectPtr(new StringValue(value)));
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
        this->val_.linked_list->clear();
        return;
    }
    else
    {
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
