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
#include <iostream>
//-----------------------------------------------------------------------------
namespace db
{

class Value
{
public:
    //value type define
    enum TYPE
    {
        INVALID= 0,
        BOOLEAN,
        INT,
        UINT,
        FLOAT,
        BINARY,
        STRING,
        LIST,
        SET,
        ZSET,
        HASH
    };

    //hash function(for unordered_set)
    struct HashFunc
    {
        size_t operator()(const Value& obj) const;
    };

    //data type alias
    using Binary    = std::vector<unsigned char>;
    using String    = std::string;
    using List      = std::list<Value>;
    using Set       = std::unordered_set<Value, HashFunc>;
    using ZSet      = std::multimap<double, Value>;
    using Hash      = std::unordered_map<String, Value>;

    //Constructor
    explicit Value(TYPE t=INVALID);
    explicit Value(bool val):type_(BOOLEAN), obj_(std::make_shared<bool>(val)){}
    explicit Value(int64_t val):type_(INT), obj_(std::make_shared<int64_t>(val)){}
    explicit Value(uint64_t val):type_(UINT), obj_(std::make_shared<uint64_t>(val)){}
    explicit Value(double val):type_(FLOAT), obj_(std::make_shared<double>(val)){}

    explicit Value(const Binary& val):type_(BINARY), obj_(std::make_shared<Binary>(val)){}
    explicit Value(Binary&& val):type_(BINARY), obj_(std::make_shared<Binary>(std::move(val))){}

    explicit Value(const char* val):type_(STRING), obj_(std::make_shared<String>(val)){}
    explicit Value(const String& val):type_(STRING), obj_(std::make_shared<String>(val)){}
    explicit Value(String&& val):type_(STRING), obj_(std::make_shared<String>(std::move(val))){}

    explicit Value(const List& val):type_(LIST), obj_(std::make_shared<List>(val)){}
    explicit Value(List&& val):type_(LIST), obj_(std::make_shared<List>(std::move(val))){}

    explicit Value(const Set& val):type_(SET), obj_(std::make_shared<Set>(val)){}
    explicit Value(Set&& val):type_(SET), obj_(std::make_shared<Set>(std::move(val))){}

    explicit Value(const ZSet& val):type_(ZSET), obj_(std::make_shared<ZSet>(val)){}
    explicit Value(ZSet&& val):type_(ZSET), obj_(std::make_shared<ZSet>(std::move(val))){}

    explicit Value(const Hash& val):type_(HASH), obj_(std::make_shared<Hash>(val)){}
    explicit Value(Hash&& val):type_(HASH), obj_(std::make_shared<Hash>(std::move(val))){}

    Value(const Value& o) { *this = o; }    //lazy copy
    Value(Value&& o) { *this = std::move(o); }

    Value& operator=(const Value& o){ type_=o.type_; obj_=o.obj_; return *this; }   //lazy copy
    Value& operator=(Value&& o){
        type_=o.type_; obj_=std::move(o.obj_); o.type_=INVALID; o.obj_.reset(); return *this; }

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
    bool GetBoolean() const { assert(BOOLEAN); return *std::static_pointer_cast<bool>(obj_); }
    int64_t GetInt() const { assert(INT); return *std::static_pointer_cast<int64_t>(obj_); }
    uint64_t GetUInt() const { assert(UINT); return *std::static_pointer_cast<uint64_t>(obj_); }
    double GetFloat() const { assert(FLOAT); return *std::static_pointer_cast<double>(obj_); }

    const Binary& GetBinary() const { assert(BINARY); return *std::static_pointer_cast<Binary>(obj_); }
    Binary& GetBinary() { assert(BINARY); return *std::static_pointer_cast<Binary>(obj_); }

    const String& GetString() const { assert(STRING); return *std::static_pointer_cast<String>(obj_); }
    String& GetString() { assert(STRING); return *std::static_pointer_cast<String>(obj_); }

    const List& GetList() const { assert(LIST); return *std::static_pointer_cast<List>(obj_); }
    List& GetList() { assert(LIST); return *std::static_pointer_cast<List>(obj_); }

    const Set& GetSet() const { assert(SET); return *std::static_pointer_cast<Set>(obj_); }
    Set& GetSet() { assert(SET); return *std::static_pointer_cast<Set>(obj_); }

    const ZSet& GetZSet() const { assert(ZSET); return *std::static_pointer_cast<ZSet>(obj_); }
    ZSet& GetZSet() { assert(ZSET); return *std::static_pointer_cast<ZSet>(obj_); }

    const Hash& GetHash() const { assert(HASH); return *std::static_pointer_cast<Hash>(obj_); }
    Hash& GetHash() { assert(HASH); return *std::static_pointer_cast<Hash>(obj_); }

    //normal method
    short type() const { return type_; }

    const std::shared_ptr<void>& obj() const { return obj_; }
    std::shared_ptr<void>& obj() { return obj_; }

public:
    //operator overload
    bool operator==(const Value& val) const;
    bool operator!=(const Value& val) const;

    Value& operator[](const char* key);
    Value& operator[](const String& key);
    const Value& operator[](const char* key) const;
    const Value& operator[](const String& key) const;

    Value::List operator[](double score) const;

    //output
    friend std::ostream& operator<<(std::ostream& out, const Value& val);

private:
    std::string ValueToString(int deep=0, bool add_tabs=true) const;
    template<typename T>std::string UnaryContainerToString(const T& val, int deep) const;
    template<typename T>std::string BinaryContainerToString(const T& val, int deep) const;

    std::string AddTab(int deep) const;

private:
    short type_;
    std::shared_ptr<void> obj_;
};
using ValuePtr = std::shared_ptr<Value>;
//---------------------------------------------------------------------------
//operator overload
std::ostream& operator<<(std::ostream& out, const Value& val);

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_VALUE_H_
