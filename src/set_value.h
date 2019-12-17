//---------------------------------------------------------------------------
#ifndef DB_SET_VALUE_H_
#define DB_SET_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
class SetValue : public Value
{
public:
    SetValue();
    SetValue(SetValue& other)=default;
    SetValue(SetValue&& other)=default;
    SetValue& operator=(const SetValue& other)=default;
    SetValue& operator=(SetValue&& other)=default;
    virtual ~SetValue();

public:
    //capacity
    bool Empty() const;
    size_t Size() const;

    //hahs policy
    void Reserve(size_t size);
    void Rehash(size_t size);

    //iterators
    using ConstIterator = Set::const_iterator;

    ConstIterator Begin() const;
    ConstIterator End() const;

    //element lookup
    ConstIterator Find(const ObjectPtr& val) const;
    ConstIterator Find(const char* val) const;
    ConstIterator Find(const String& val) const;
    ConstIterator Find(int32_t val) const;
    ConstIterator Find(int64_t val) const;
    ConstIterator Find(double val) const;

    size_t Count(const ObjectPtr& val) const;
    size_t Count(const char* val) const;
    size_t Count(const String& val) const;
    size_t Count(int32_t val) const;
    size_t Count(int64_t val) const;
    size_t Count(double val) const;

    //modifiers
    bool Insert(const ObjectPtr& val);
    bool Insert(const char* val);
    bool Insert(const String& val);
    bool Insert(String&& val);
    bool Insert(int32_t val);
    bool Insert(int64_t val);
    bool Insert(double val);

    bool Erase(const ObjectPtr& val);
    bool Erase(const char* val);
    bool Erase(const String& val);
    bool Erase(int32_t val);
    bool Erase(int64_t val);
    bool Erase(double val);

    ConstIterator Erase(ConstIterator position);
    ConstIterator Erase(ConstIterator first, ConstIterator last);
    void Clear();
};

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_SET_VALUE_H_
