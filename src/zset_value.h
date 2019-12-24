//---------------------------------------------------------------------------
#ifndef DB_ZSET_VALUE_H_
#define DB_ZSET_VALUE_H_
//---------------------------------------------------------------------------
#include "value.h"
#include "object_ptr.h"
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class ZSetValue : public Value
{
public:
    ZSetValue(size_t reserve_size=0);
    ZSetValue(ZSetValue& other)=default;
    ZSetValue(ZSetValue&& other)=default;
    ZSetValue& operator=(const ZSetValue& other)=default;
    ZSetValue& operator=(ZSetValue&& other)=default;
    virtual ~ZSetValue();

public:
    //capacity
    bool Empty() const;
    size_t Size() const;

    //iterators
    using Iterator = ScoreObjMap::iterator;
    using ConstIterator = ScoreObjMap::const_iterator;
    using ReverseIterator = ScoreObjMap::reverse_iterator;
    using ConstReverseIterator = ScoreObjMap::const_reverse_iterator;
    using ObjScoreMapIter = ObjScoreMap::iterator;
    using ConstObjScoreMapIter = ObjScoreMap::const_iterator;

    Iterator Begin();
    Iterator End();
    ConstIterator Begin() const;
    ConstIterator End() const;
    ReverseIterator RBegin();
    ReverseIterator REnd();
    ConstReverseIterator RBegin() const;
    ConstReverseIterator REnd() const;

    ObjScoreMapIter MapEnd();
    ConstObjScoreMapIter MapEnd() const;

    //element lookup
    template<typename T>
    ObjScoreMapIter Find(const T& val) const;

    template<typename T>
    bool Count(const T& val);

    ListValuePtr Range(double left_interval, double right_interval);

    //modifiers
    template<typename T>
    bool Insert(double score, const T& val);

    template<typename T>
    bool Erase(const T& val);

    void Clear();
};
//---------------------------------------------------------------------------
template<typename T>
inline ZSetValue::ObjScoreMapIter ZSetValue::Find(const T& val) const
{
    ObjectPtr op = MakeObject<StringValue>(val);
    return Find(op);
}
//---------------------------------------------------------------------------
template<>
inline ZSetValue::ObjScoreMapIter ZSetValue::Find(const ObjectPtr& val) const
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->map.find(val);
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------
template<typename T>
inline bool ZSetValue::Insert(double score, const T& val)
{
    ObjectPtr op = MakeObject<StringValue>(val);
    return Insert(score, op);
}
//---------------------------------------------------------------------------
template<>
inline bool ZSetValue::Insert(double score, const ObjectPtr& val)
{
    if(SORTED_SET == this->encoding_)
    {
        auto& list = this->val_.sorted_set->list;
        auto& map = this->val_.sorted_set->map;
        auto found = map.find(val);
        if(map.end() != found)
        {
            double old_score = found->second;
            found->second = score;
            auto range = list.equal_range(old_score);
            for(auto i=range.first; i!=range.second; ++i)
            {
                if(i->second == val)
                {
                    list.erase(i);
                    break;
                }
            }
            list.insert({score, val});
            return false;
        }
        else
        {
            map.insert({val, score});
            list.insert({score, val});
            return true;
        }
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
template<typename T>
bool ZSetValue::Count(const T& val)
{
    ObjectPtr op = MakeObject<StringValue>(val);
    return Count(op);
}
//---------------------------------------------------------------------------
template<>
inline bool ZSetValue::Count(const ObjectPtr& val)
{
    if(SORTED_SET == this->encoding_)
    {
        return this->val_.sorted_set->map.count(val);
    }
    else
    {
        throw type_error();
    }

    return false;
}
//---------------------------------------------------------------------------
template<typename T>
inline bool ZSetValue::Erase(const T& val)
{
    ObjectPtr op = MakeObject<StringValue>(val);
    return Erase(op);
}
//---------------------------------------------------------------------------
template<>
inline bool ZSetValue::Erase(const ObjectPtr& val)
{
    if(SORTED_SET == this->encoding_)
    {
        auto& list = this->val_.sorted_set->list;
        auto& map = this->val_.sorted_set->map;
        auto found = map.find(val);
        if(map.end() == found)
            return false;

        auto range = list.equal_range(found->second);
        for(auto i=range.first; i!=range.second; ++i)
        {
            if(i->second == val)
            {
                list.erase(i);
                break;
            }
        }
        map.erase(found);

        return true;
    }
    else
    {
        //TODO:ziplist
        throw type_error();
    }
}
//---------------------------------------------------------------------------

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_ZSET_VALUE_H_
