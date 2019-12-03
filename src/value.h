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

//value pointer define
using ValuePtr = std::shared_ptr<class Value>;

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
    using LinkedList    = std::list<Value>;
    using Set           = std::unordered_set<Value>;
    using IntSet        = std::vector<uint8_t>;
    using SortedSet     = std::multimap<double, Value>;
    using Hash          = std::unordered_map<String, Value>;
    using ZipList       = std::vector<uint8_t>;

public:
    //Constructor

    //STRING
    explicit Value(const char* str);
    Value(const char* ptr, size_t len);
    explicit Value(const std::string& str);

    //BINARY
    Value(const uint8_t* ptr, size_t len);

    //LIST


private:
    //Constructor
    Value(Type type, const ValuePtr& obj);




    //Set method

    //Get method

    //normal method
    Type type() const { return type_; }
    Encoding encoding() const { return encoding_; }
    base::Timestamp lru() const { return lru_; }
    const std::shared_ptr<void>& obj() const { return obj_; }
    std::shared_ptr<void>& obj() { return obj_; }

public:
    //operator overload

    //output
    //friend std::ostream& operator<<(std::ostream& out, const Value& val);

private:
    Type type_;                     //类型
    Encoding encoding_;             //编码方式
    base::Timestamp lru_;           //最后一次访问时间
    std::shared_ptr<void> obj_;     //对象实际内容
};
//---------------------------------------------------------------------------
//operator overload
//std::ostream& operator<<(std::ostream& out, const Value& val);

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_VALUE_H_
