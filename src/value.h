//---------------------------------------------------------------------------
#ifndef DB_VALUE_H_
#define DB_VALUE_H_
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <memory>

#include "../thirdpart/base/include/timestamp.h"

#include "object_ptr.h"
//-----------------------------------------------------------------------------
namespace db
{

//-----------------------------------------------------------------------------
class Value
{
public:
    enum Type
    {
        STRING, //字符串类型
        BINARY, //二进制类型
        LIST,   //列表类型
        SET,    //无序集合类型
        ZSET,   //有序集合类型
        HASH    //字典类型
    };

    enum Encoding
    {
        //STRING类型对应的编码
        RAW,                        //原生字符串
        EMBSTR,                     //TODO:字符串紧凑型
        INT,                        //字符串整型表示

        //BINARY类型对应的编码
        CHAR_VECTOR,                //字符数组

        //LIST类型对应的编码
        LINKED_LIST,                //链表

        //SET类型对应的编码
        UNORDERED_SET,              //无序集合
        INT_SET,                    //TODO:整型集合

        //ZSET类型对应的编码
        SORTED_SET,                 //有序集合

        //HASH类型对应的编码
        UNORDERED_MAP,              //无序字典

        //LIST,HASH类型对应的编码
        ZIPLIST,                    //TODO:压缩列表
    };

    //哈希函数，用于Set
    struct HashFunc
    {
        size_t operator()(const ObjectPtr& value) const;
    };

    //data type alias
    using String        = std::string;
    using Binary        = std::vector<uint8_t>;
    using LinkedList    = std::list<ObjectPtr>;
    using Set           = std::unordered_set<ObjectPtr, HashFunc>;
    using IntSet        = std::vector<uint8_t>;
    using Hash          = std::unordered_map<String, ObjectPtr>;
    using ZipList       = std::vector<uint8_t>;
    using ScoreObjMap   = std::multimap<double, ObjectPtr>;
    using ObjScoreMap   = std::unordered_map<ObjectPtr, double, HashFunc>;
    
    struct SortedSet
    {
        ScoreObjMap list;
        ObjScoreMap map;
    };

protected:
    Value(Type type);
    Value(Type type, Encoding encoding, size_t reserve_size=0);
    Value(const Value& other);
    Value(Value&& other);
    Value& operator=(const Value& other);
    Value& operator=(Value&& other);

public:
    virtual ~Value();

    bool operator==(const Value& other) const;

    void Swap(Value& other);

public:
    Type type() const { return type_; }
    Encoding encoding() const { return encoding_; }
    base::Timestamp lru() const { return lru_; }

    std::string ToString() const;

public:
    friend class ObjectPtr;

protected:
    void InitPayload(size_t reserve_size);

private:
    void DupPayload(const Value& other);
    void ReleasePayload();

    std::string AddTabs(int deep) const;
    std::string ToString(int deep) const;

    template<typename T> std::string UnaryContainerToString(const T& val, int deep) const;
    template<typename T> std::string BinaryContainerToString(const T& val, int deep) const;

protected:
    Type type_;                     //类型
    Encoding encoding_;             //编码方式
    base::Timestamp lru_;           //最后一次访问时间
    union ValueHolder
    {
        String* string;
        Binary* binary;
        LinkedList* linked_list;
        Set* set;
        IntSet* intset;
        SortedSet* sorted_set;
        Hash* hash;
        ZipList* zip_list;
    }val_;
};
//-----------------------------------------------------------------------------
class type_error : public std::logic_error
{
public:
    type_error(const char* msg="type error")
    :   std::logic_error(msg)
    {
    }
    virtual ~type_error(){}
};
//---------------------------------------------------------------------------
bool operator==(const ObjectPtr& left, const ObjectPtr& right);
bool operator!=(const ObjectPtr& left, const ObjectPtr& right);
}//namespace db
//---------------------------------------------------------------------------
#endif //DB_VALUE_H_
