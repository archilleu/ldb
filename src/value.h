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
//-----------------------------------------------------------------------------
namespace db
{

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
//-----------------------------------------------------------------------------
//value pointer define
using ValuePtr = std::shared_ptr<class Value>;
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

    //data type alias
    using String        = std::string;
    using Binary        = std::vector<uint8_t>;
    using LinkedList    = std::list<ValuePtr>;
    using Set           = std::unordered_set<ValuePtr>;
    using IntSet        = std::vector<uint8_t>;
    using SortedSet     = std::multimap<double, ValuePtr>;
    using Hash          = std::unordered_map<String, ValuePtr>;
    using ZipList       = std::vector<uint8_t>;

protected:
    Value(Type type, Encoding encoding, size_t reserve_size=0);
    Value(const Value& other);
    Value(Value&& other);
    Value& operator=(const Value& other);
    Value& operator=(Value&& other);
    virtual ~Value();

public:
    void Swap(Value& other);

public:
    Type type() const { return type_; }
    Encoding encoding() const { return encoding_; }
    base::Timestamp lru() const { return lru_; }

public:
    const static ValuePtr NullPtr;

private:
    void InitPayload(size_t reserve_size);
    void DupPayload(const Value& other);
    void ReleasePayload();

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
//---------------------------------------------------------------------------
//operator overload
//std::ostream& operator<<(std::ostream& out, const Value& val);

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_VALUE_H_
