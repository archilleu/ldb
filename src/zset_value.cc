//---------------------------------------------------------------------------
#include <cassert>
#include "zset_value.h"
#include "string_value.h"
#include "list_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
ZSetValue::ZSetValue(size_t reserve_size)
:   Value(ZSET, SORTED_SET, reserve_size)
{
    return;
}
//---------------------------------------------------------------------------
ZSetValue::~ZSetValue()
{
    return;
}
//---------------------------------------------------------------------------
bool ZSetValue::Empty() const
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.empty();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return true;
}
//---------------------------------------------------------------------------
size_t ZSetValue::Size() const
{
    if(SORTED_SET == this->encoding_)
    {
        assert(this->val_.sorted_set->list.size() == this->val_.sorted_set->map.size()); 
        return this->val_.sorted_set->list.size();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
ZSetValue::Iterator ZSetValue::Begin()
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.begin();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::Iterator ZSetValue::End()
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ConstIterator ZSetValue::Begin() const
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ConstIterator ZSetValue::End() const
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ReverseIterator ZSetValue::RBegin()
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.rbegin();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ReverseIterator ZSetValue::REnd()
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.rend();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ConstReverseIterator ZSetValue::RBegin() const
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.rbegin();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ConstReverseIterator ZSetValue::REnd() const
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->list.rend();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ObjScoreMapIter ZSetValue::MapEnd()
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->map.end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ZSetValue::ConstObjScoreMapIter ZSetValue::MapEnd() const
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->map.end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
ListValuePtr ZSetValue::Range(double left_interval, double right_interval)
{
    ListValuePtr list = MakeObject<ListValue>().AsListPtr();
    if(SORTED_SET == this->encoding_)
    {
        auto left = this->val_.sorted_set->list.lower_bound(left_interval);
        auto right = this->val_.sorted_set->list.upper_bound(right_interval);
        for(auto it=left; it!=right; ++it)
        {
            list->PushBack(it->second);
        }
        return list;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
void ZSetValue::Clear()
{
    if(SORTED_SET == this->encoding_)
    {
        this->val_.sorted_set->list.clear();
        this->val_.sorted_set->map.clear();
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
