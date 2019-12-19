//---------------------------------------------------------------------------
#include "set_value.h"
#include "string_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
SetValue::SetValue(size_t reserve_size)
:   Value(SET, UNORDERED_SET, reserve_size)
{
    return;
}
//---------------------------------------------------------------------------
SetValue::~SetValue()
{
    return;
}
//---------------------------------------------------------------------------
bool SetValue::Empty() const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->empty();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return true;
}
//---------------------------------------------------------------------------
size_t SetValue::Size() const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->size();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
void SetValue::Reserve(size_t size)
{
    if(UNORDERED_SET == this->encoding_)
    {
        this->val_.set->reserve(size);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
void SetValue::Rehash(size_t size)
{
    if(UNORDERED_SET == this->encoding_)
    {
        this->val_.set->rehash(size);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Begin() const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->begin();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
    throw type_error();
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::End() const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
    throw type_error();
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Find(const ObjectPtr& val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->find(val);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return val_.set->end();
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Find(const char* val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->find(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return val_.set->end();
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Find(const String& val) const
{
    return Find(val.c_str());
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Find(int32_t val) const
{
    return Find(static_cast<int64_t>(val));
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Find(int64_t val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->find(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return val_.set->end();
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Find(double val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->find(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return val_.set->end();
}
//---------------------------------------------------------------------------
size_t SetValue::Count(const ObjectPtr& val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->count(val);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
size_t SetValue::Count(const char* val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->count(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
size_t SetValue::Count(const String& val) const
{
    return Count(val.c_str());
}
//---------------------------------------------------------------------------
size_t SetValue::Count(int32_t val) const
{
    return Count(static_cast<int64_t>(val));
}
//---------------------------------------------------------------------------
size_t SetValue::Count(int64_t val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->count(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
size_t SetValue::Count(double val) const
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->count(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
bool SetValue::Insert(const ObjectPtr& val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        auto result = this->val_.set->insert(val);
        return result.second;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Insert(const char* val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        auto result = this->val_.set->insert(ObjectPtr(new StringValue(val)));
        return result.second;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Insert(const String& val)
{
    return Insert(val.c_str());
}
//---------------------------------------------------------------------------
bool SetValue::Insert(String&& val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        auto result = this->val_.set->insert(ObjectPtr(new StringValue(val)));
        return result.second;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Insert(int32_t val)
{
    return Insert(static_cast<int64_t>(val));
}
//---------------------------------------------------------------------------
bool SetValue::Insert(int64_t val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        auto result = this->val_.set->insert(ObjectPtr(new StringValue(val)));
        return result.second;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Insert(double val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        auto result = this->val_.set->insert(ObjectPtr(new StringValue(val)));
        return result.second;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Erase(const ObjectPtr& val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->erase(val);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Erase(const char* val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->erase(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Erase(const String& val)
{
    return Erase(val.c_str());
}
//---------------------------------------------------------------------------
bool SetValue::Erase(int32_t val)
{
    return Erase(static_cast<int64_t>(val));
}
//---------------------------------------------------------------------------
bool SetValue::Erase(int64_t val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->erase(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
bool SetValue::Erase(double val)
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->erase(ObjectPtr(new StringValue(val)));
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Erase(ConstIterator position)
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->erase(position);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
SetValue::ConstIterator SetValue::Erase(ConstIterator first, ConstIterator last)
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->erase(first, last);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
void SetValue::Clear()
{
    if(UNORDERED_SET == this->encoding_)
    {
        return this->val_.set->clear();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------

