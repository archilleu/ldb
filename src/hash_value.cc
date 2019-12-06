//---------------------------------------------------------------------------
#include <cassert>
#include "hash_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
HashValue::HashValue(size_t reserve_size)
:   Value(HASH)
{
    this->encoding_ = UNORDERED_MAP;

    InitPayload();

    if(UNORDERED_MAP == this->encoding_)
    {
        if(0 != reserve_size)
            Reserve(reserve_size);
    }

    return;
}
//---------------------------------------------------------------------------
HashValue::HashValue(const HashValue& other)
:   Value(HASH)
{
    this->encoding_ = other.encoding_;
    InitPayload();

    if(UNORDERED_MAP == this->encoding_)
        *(this->val_.hash) = *(other.val_.hash);
    else
        *(this->val_.zip_list) = *(other.val_.zip_list);

    return;
}
//---------------------------------------------------------------------------
HashValue::HashValue(HashValue&& other)
:   Value(HASH)
{
    this->encoding_ = other.encoding_;
    InitPayload();
    Swap(other);
}
//---------------------------------------------------------------------------
HashValue& HashValue::operator=(const HashValue& other)
{
    if(this == &other)
        return *this;

    HashValue(other).Swap(*this);
    return *this;
}
//---------------------------------------------------------------------------
HashValue& HashValue::operator=(HashValue&& other)
{
    other.Swap(*this);
    return *this;
}
//---------------------------------------------------------------------------
HashValue::~HashValue()
{
    if(UNORDERED_MAP == this->encoding_)
        delete this->val_.hash;
    else
        delete this->val_.zip_list;

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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
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
        assert(0);
    }

    return;
}
//---------------------------------------------------------------------------
void HashValue::Swap(HashValue& other)
{
    std::swap(this->encoding_, other.encoding_);
    std::swap(this->val_, other.val_);
    std::swap(this->lru_, other.lru_);
}
//---------------------------------------------------------------------------
HashValuePtr HashValue::AsHashPtr(ValuePtr value)
{
    return std::dynamic_pointer_cast<HashValue>(value);
}
//---------------------------------------------------------------------------
void HashValue::InitPayload()
{
    assert(this->type() == HASH);

    if(UNORDERED_MAP == this->encoding())
        this->val_.hash = new Hash();
    else
        this->val_.zip_list = new ZipList();

    return;
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
