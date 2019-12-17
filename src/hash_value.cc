//---------------------------------------------------------------------------
#include "hash_value.h"
#include "string_value.h"
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
ObjectPtr& HashValue::operator[] (const std::string& key)
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
ObjectPtr& HashValue::operator[] (std::string&& key)
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
HashValue::Iterator HashValue::Find(const char* key)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->find(key);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
HashValue::Iterator HashValue::Find(const String& key)
{
    return Find(key.c_str());
}
//---------------------------------------------------------------------------
HashValue::ConstIterator HashValue::Find(const char* key) const
{
    if(UNORDERED_MAP == this->encoding_)
    {
        return this->val_.hash->find(key);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
HashValue::ConstIterator HashValue::Find(const String& key) const
{
    return Find(key.c_str());
}
//---------------------------------------------------------------------------
size_t HashValue::Count(const char* key) const
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
size_t HashValue::Count(const std::string& key) const
{
    return Count(key.c_str());
}
//---------------------------------------------------------------------------
bool HashValue::Insert(const std::string& key, const ObjectPtr& value)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        std::pair<String, ObjectPtr> pair(key, value);
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
bool HashValue::Insert(std::string&& key, ObjectPtr&& value)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        auto pair = std::make_pair<std::string, ObjectPtr>(std::move(key), std::move(value));
        auto result = this->val_.hash->insert(std::move(pair));
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
bool HashValue::Insert(const std::string& key, String& val)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        std::pair<String, ObjectPtr> pair(key, new StringValue(val));
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
bool HashValue::Insert(std::string&& key, String&& val)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        auto pair = std::make_pair<std::string, ObjectPtr>(std::move(key), ObjectPtr(new StringValue(val)));
        auto result = this->val_.hash->insert(std::move(pair));
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
bool HashValue::Insert(std::string& key, int32_t val)
{
    return Insert(key, static_cast<int64_t>(val));
}
//---------------------------------------------------------------------------
bool HashValue::Insert(std::string&& key, int32_t val)
{
    return Insert(key, static_cast<int64_t>(val));
}
//---------------------------------------------------------------------------
bool HashValue::Insert(std::string& key, int64_t val)
{
    return Insert(String(key), val);
}
//---------------------------------------------------------------------------
bool HashValue::Insert(std::string&& key, int64_t val)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        auto pair = std::make_pair<std::string, ObjectPtr>(std::move(key), ObjectPtr(new StringValue(val)));
        auto result = this->val_.hash->insert(std::move(pair));
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
bool HashValue::Insert(std::string& key, double val)
{
    return Insert(String(key), val);
}
//---------------------------------------------------------------------------
bool HashValue::Insert(std::string&& key, double val)
{
    if(UNORDERED_MAP == this->encoding_)
    {
        auto pair = std::make_pair<std::string, ObjectPtr>(std::move(key), ObjectPtr(new StringValue(val)));
        auto result = this->val_.hash->insert(std::move(pair));
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

}//namespace db
//---------------------------------------------------------------------------
