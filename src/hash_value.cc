//---------------------------------------------------------------------------
#include "hash_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
HashValue::HashValue(size_t reserve_size)
:   Value(HASH, UNORDERED_MAP, reserve_size)
{
    return;
}
//---------------------------------------------------------------------------
HashValue::~HashValue()
{
    return;
}
//---------------------------------------------------------------------------
bool HashValue::Empty() const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->empty();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return true;
}
//---------------------------------------------------------------------------
size_t HashValue::Size() const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->size();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
void HashValue::Reserve(size_t size)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        this->val_.hash->reserve(size);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
void HashValue::Rehash(size_t size)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        this->val_.hash->rehash(size);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
HashValue::Iterator HashValue::Begin()
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->begin();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    throw type_error();
}
//---------------------------------------------------------------------------
HashValue::Iterator HashValue::End()
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
    throw type_error();
}
//---------------------------------------------------------------------------
HashValue::ConstIterator HashValue::Begin() const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->begin();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
    throw type_error();
}
//---------------------------------------------------------------------------
HashValue::ConstIterator HashValue::End() const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->end();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
    throw type_error();
}
//---------------------------------------------------------------------------
ValuePtr& HashValue::operator[] (const std::string& key)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return (*this->val_.hash)[key];
    }
    else
    {
        //TODO:ziplist
    }

    throw type_error();
}
//---------------------------------------------------------------------------
ValuePtr& HashValue::operator[] (std::string&& key)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return (*this->val_.hash)[std::move(key)];
    }
    else
    {
        //TODO:ziplist
    }

    throw type_error();
}
//---------------------------------------------------------------------------
const ValuePtr& HashValue::Find(const std::string& key) const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        auto got = this->val_.hash->find(key);
        if(got == this->val_.hash->end())
            return Value::NullPtr;

        return got->second;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return Value::NullPtr;
}
//---------------------------------------------------------------------------
size_t HashValue::Count(const std::string& key) const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->count(key);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return 0;
}
//---------------------------------------------------------------------------
StringValuePtr HashValue::FindAsString(const std::string& key) const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        auto got = this->val_.hash->find(key);
        if(got == this->val_.hash->end())
            return StringValue::NullPtr;

        return std::dynamic_pointer_cast<StringValue>(got->second);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return StringValue::NullPtr;
}
//---------------------------------------------------------------------------
bool HashValue::Insert(const std::string& key, const ValuePtr& value)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        std::pair<std::string, ValuePtr> pair(key, value);
        auto result = this->val_.hash->insert(pair);
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
bool HashValue::Insert(std::string&& key, ValuePtr&& value)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        auto pair = std::make_pair<std::string, ValuePtr>(std::move(key), std::move(value));
        auto result = this->val_.hash->insert(pair);
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
bool HashValue::Erase(const std::string& key)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->erase(key);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
void HashValue::Clear()
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->clear();
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return;
}
//---------------------------------------------------------------------------
HashValuePtr HashValue::AsHashPtr(ValuePtr value)
{
    return std::dynamic_pointer_cast<HashValue>(value);
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
