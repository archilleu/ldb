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
#include <assert.h>
#include <functional>
//-----------------------------------------------------------------------------
namespace db
{

class Value
{
public:
    //value type define
    enum
    {
        TYPE_INVALID= 0,
        TYPE_BOOLEAN,
        TYPE_INT,
        TYPE_UINT,
        TYPE_FLOAT,
        TYPE_BINARY,
        TYPE_STRING,
        TYPE_LIST,
        TYPE_SET,
        TYPE_ZSET,
        TYPE_HASH
    };

    //hash function(for unordered_set)
    struct HashFunc
    {
        std::size_t operator()(const Value& obj) const;
    };

    //equal function(for unordered_set)
    struct EqualFunc
    {
        bool operator()(const Value& left, const Value& right);
    };

    //data type alias
    using Binary    = std::vector<unsigned char>;
    using String    = std::string;
    using List      = std::list<Value>;
    using Set       = std::unordered_set<Value, HashFunc, EqualFunc>;
    using ZSet      = std::unordered_map<double, Value>;
    using Hash      = std::map<String, Value>;

    //Constructor
    Value():type_(TYPE_INVALID){}
    explicit Value(bool val):type_(TYPE_BOOLEAN), obj_(std::make_shared<bool>(val)){}
    explicit Value(int64_t val):type_(TYPE_INT), obj_(std::make_shared<int64_t>(val)){}
    explicit Value(uint64_t val):type_(TYPE_UINT), obj_(std::make_shared<uint64_t>(val)){}
    explicit Value(double val):type_(TYPE_FLOAT), obj_(std::make_shared<double>(val)){}

    Value(const Binary& val):type_(TYPE_BINARY), obj_(std::make_shared<Binary>(val)){}
    Value(Binary&& val):type_(TYPE_BINARY), obj_(std::make_shared<Binary>(std::move(val))){}

    Value(const char* val):type_(TYPE_STRING), obj_(std::make_shared<String>(val)){}
    Value(const String& val):type_(TYPE_STRING), obj_(std::make_shared<String>(val)){}
    Value(String&& val):type_(TYPE_STRING), obj_(std::make_shared<String>(std::move(val))){}

    Value(const List& val):type_(TYPE_LIST), obj_(std::make_shared<List>(val)){}
    Value(List&& val):type_(TYPE_LIST), obj_(std::make_shared<List>(std::move(val))){}

    Value(const Set& val):type_(TYPE_SET), obj_(std::make_shared<Set>(val)){}
    Value(Set&& val):type_(TYPE_SET), obj_(std::make_shared<Set>(std::move(val))){}

    Value(const ZSet& val):type_(TYPE_ZSET), obj_(std::make_shared<ZSet>(val)){}
    Value(ZSet&& val):type_(TYPE_ZSET), obj_(std::make_shared<ZSet>(std::move(val))){}

    Value(const Hash& val):type_(TYPE_HASH), obj_(std::make_shared<Hash>(val)){}
    Value(Hash&& val):type_(TYPE_HASH), obj_(std::make_shared<Hash>(std::move(val))){}

    Value(const Value& o) { *this = o; }    //lazy copy
    Value(Value&& o) { *this = std::move(o); }

    Value& operator=(const Value& o){ type_=o.type_; obj_=o.obj_; return *this; }   //lazy copy
    Value& operator=(Value&& o){
        type_=o.type_; obj_=std::move(o.obj_); o.type_=TYPE_INVALID; o.obj_.reset(); return *this; }

    //Set method
    bool SetBoolean(bool val);
    bool SetInt(int64_t val);
    bool SetUInt(uint64_t val);
    bool SetFloat(double val);

    bool SetBinary(const Binary& val);
    bool SetBinary(Binary&& val);

    bool SetString(const String& val);
    bool SetString(String&& val);

    bool SetList(const List& val);
    bool SetList(List&& val);

    bool SetSet(const Set& val);
    bool SetSet(Set&& val);

    bool SetZSet(const ZSet& val);
    bool SetZSet(ZSet&& val);

    bool SetHash(const Hash& val);
    bool SetHash(Hash&& val);

    //Get method
    bool GetBoolean() const { assert(TYPE_BOOLEAN); return *std::static_pointer_cast<bool>(obj_); }
    int64_t GetInt() const { assert(TYPE_INT); return *std::static_pointer_cast<int64_t>(obj_); }
    uint64_t GetUInt() const { assert(TYPE_UINT); return *std::static_pointer_cast<uint64_t>(obj_); }
    double GetFloat() const { assert(TYPE_FLOAT); return *std::static_pointer_cast<double>(obj_); }

    const Binary& GetBinary() const { assert(TYPE_BINARY); return *std::static_pointer_cast<Binary>(obj_); }
    Binary& GetBinary() { assert(TYPE_BINARY); return *std::static_pointer_cast<Binary>(obj_); }

    const String& GetString() const { assert(TYPE_STRING); return *std::static_pointer_cast<String>(obj_); }
    String& GetString() { assert(TYPE_STRING); return *std::static_pointer_cast<String>(obj_); }

    const List& GetList() const { assert(TYPE_LIST); return *std::static_pointer_cast<List>(obj_); }
    List& GetList() { assert(TYPE_LIST); return *std::static_pointer_cast<List>(obj_); }

    const Set& GetSet() const { assert(TYPE_SET); return *std::static_pointer_cast<Set>(obj_); }
    Set& GetSet() { assert(TYPE_SET); return *std::static_pointer_cast<Set>(obj_); }

    const ZSet& GetZSet() const { assert(TYPE_ZSET); return *std::static_pointer_cast<ZSet>(obj_); }
    ZSet& GetZSet() { assert(TYPE_ZSET); return *std::static_pointer_cast<ZSet>(obj_); }

    const Hash& GetHash() const { assert(TYPE_HASH); return *std::static_pointer_cast<Hash>(obj_); }
    Hash& GetHash() { assert(TYPE_HASH); return *std::static_pointer_cast<Hash>(obj_); }

    //normal method
    short type() const { return type_; }

    const std::shared_ptr<void>& obj() const { return obj_; }
    std::shared_ptr<void>& obj() { return obj_; }

    //operator overload
    friend bool operator==(const Value& left, const Value& right);

private:
    short type_;
    std::shared_ptr<void> obj_;
};
using ValuePtr = std::shared_ptr<Value>;

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_VALUE_H_
