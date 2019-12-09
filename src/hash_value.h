//---------------------------------------------------------------------------
#ifndef DB_HASH_VALUE_H_
#define DB_HASH_VALUE_H_
//---------------------------------------------------------------------------
#include "string_value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
//hash pointer define
using HashValuePtr = std::shared_ptr<class HashValue>;
//---------------------------------------------------------------------------
class HashValue : public Value
{
public:
    HashValue(size_t reserve_size=0);
    HashValue(const HashValue& other)=default;
    HashValue(HashValue&& other)=default;
    HashValue& operator=(const HashValue& other)=default;
    HashValue& operator=(HashValue&& other)=default;
    virtual ~HashValue();

public:
    //capacity
    bool Empty() const;
    size_t Size() const;

    //hahs policy
    void Reserve(size_t size);
    void Rehash(size_t size);

    //iterators
    using Iterator = Hash::iterator;
    using ConstIterator = Hash::const_iterator;

    Iterator Begin() ;
    Iterator End();
    ConstIterator Begin() const;
    ConstIterator End() const;
    
    //element access
    ValuePtr& operator[] (const std::string& key);
    ValuePtr& operator[] (std::string&& key);

    //element lookup
    const ValuePtr& Find(const std::string& key) const;
    size_t Count(const std::string& key) const;
    StringValuePtr FindAsString(const std::string& key) const;

    //modifiers
    bool Insert(const std::string& key, const ValuePtr& value);
    bool Insert(std::string&& key, ValuePtr&& value);
    bool Erase(const std::string& key);
    void Clear();

    static HashValuePtr AsHashPtr(ValuePtr value);

public:
    const static HashValue NullPtr;
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_HASH_VALUE_H_
