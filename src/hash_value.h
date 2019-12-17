//---------------------------------------------------------------------------
#ifndef DB_HASH_VALUE_H_
#define DB_HASH_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

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
    ObjectPtr& operator[] (const std::string& key);
    ObjectPtr& operator[] (std::string&& key);

    //element lookup
    Iterator Find(const char* key);
    Iterator Find(const std::string& key);
    ConstIterator Find(const char* key) const;
    ConstIterator Find(const std::string& key) const;

    size_t Count(const char* key) const;
    size_t Count(const std::string& key) const;

    //modifiers
    bool Insert(const std::string& key, const ObjectPtr& val);
    bool Insert(std::string&& key, ObjectPtr&& val);
    bool Insert(const std::string& key, String& val);
    bool Insert(std::string&& key, String&& val);
    bool Insert(std::string& key, int32_t val);
    bool Insert(std::string&& key, int32_t val);
    bool Insert(std::string& key, int64_t val);
    bool Insert(std::string&& key, int64_t val);
    bool Insert(std::string& key, double val);
    bool Insert(std::string&& key, double val);

    bool Erase(const char* key);
    bool Erase(const std::string& key);

    void Clear();
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_HASH_VALUE_H_
