//---------------------------------------------------------------------------
#ifndef DB_TYPE_H_
#define DB_TYPE_H_
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

//data type define
const short TYPE_INVALID= 0;
const short TYPE_BOOLEAN= 1;
const short TYPE_INT    = 2;
const short TYPE_UINT   = 3;
const short TYPE_FLOAT  = 4;
const short TYPE_BINARY = 5;
const short TYPE_STRING = 6;
const short TYPE_LIST   = 7;
const short TYPE_SET    = 8;
const short TYPE_ZSET   = 9;
const short TYPE_HASH   = 10;

class Object;

//hash function(for Set)
struct HashFunc
{
    std::size_t operator()(const Object& obj) const;
};

//equal function(for Set)
struct EqualFunc
{
    bool operator()(const Object& left, const Object& right);
};

//data type alias
using Binary    = std::vector<unsigned char>;
using String    = std::string;
using List      = std::list<Object>;
using Set       = std::unordered_set<Object, HashFunc, EqualFunc>;
using ZSet      = std::unordered_map<String, Object>;
using Hash      = std::map<String, Object>;

//data object
class Object
{
public:
    //Constructor
    Object():type_(TYPE_INVALID){}
    Object(bool val):type_(TYPE_BOOLEAN), obj_(std::make_shared<bool>(val)){}
    Object(int64_t val):type_(TYPE_INT), obj_(std::make_shared<int64_t>(val)){}
    Object(uint64_t val):type_(TYPE_UINT), obj_(std::make_shared<uint64_t>(val)){}
    Object(double val):type_(TYPE_FLOAT), obj_(std::make_shared<double>(val)){}

    Object(const Binary& val):type_(TYPE_BINARY), obj_(std::make_shared<Binary>(val)){}
    Object(Binary&& val):type_(TYPE_BINARY), obj_(std::make_shared<Binary>(std::move(val))){}

    Object(const String& val):type_(TYPE_STRING), obj_(std::make_shared<String>(val)){}
    Object(String&& val):type_(TYPE_STRING), obj_(std::make_shared<String>(std::move(val))){}

    Object(const List& val):type_(TYPE_LIST), obj_(std::make_shared<List>(val)){}
    Object(List&& val):type_(TYPE_LIST), obj_(std::make_shared<List>(std::move(val))){}

    Object(const Set& val):type_(TYPE_SET), obj_(std::make_shared<Set>(val)){}
    Object(Set&& val):type_(TYPE_SET), obj_(std::make_shared<Set>(std::move(val))){}

    Object(const ZSet& val):type_(TYPE_ZSET), obj_(std::make_shared<ZSet>(val)){}
    Object(ZSet&& val):type_(TYPE_ZSET), obj_(std::make_shared<ZSet>(std::move(val))){}

    Object(const Hash& val):type_(TYPE_HASH), obj_(std::make_shared<Hash>(val)){}
    Object(Hash&& val):type_(TYPE_HASH), obj_(std::make_shared<Hash>(std::move(val))){}

    Object(const Object& o) { *this = o; }
    Object(Object&& o) { *this = std::move(o); }

    Object& operator=(const Object& o){ type_=o.type_; obj_=o.obj_; return *this; }
    Object& operator=(Object&& o){ type_=o.type_; obj_=std::move(o.obj_); o.type_=TYPE_INVALID; o.obj_=nullptr; return *this; }

    //Set method
    void SetBoolean(bool val);
    void SetInt(int64_t val);
    void SetUInt(uint64_t val);
    void SetFloat(double val);

    void SetBinary(const Binary& val);
    void SetBinary(Binary&& val);

    void SetString(const String& val);
    void SetString(String&& val);

    void SetList(const List& val);
    void SetList(List&& val);

    void SetSet(const Set& val);
    void SetSet(Set&& val);

    void SetZSet(const ZSet& val);
    void SetZSet(ZSet&& val);

    void SetHash(const Hash& val);
    void SetHash(Hash&& val);

    //Get method
    bool GetBoolean() { assert(TYPE_BOOLEAN); return *std::static_pointer_cast<bool>(obj_); }
    int64_t GetInt() { assert(TYPE_INT); return *std::static_pointer_cast<int64_t>(obj_); }
    uint64_t GetUInt() { assert(TYPE_UINT); return *std::static_pointer_cast<uint64_t>(obj_); }
    double GetFloat() { assert(TYPE_FLOAT); return *std::static_pointer_cast<double>(obj_); }

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

private:
    short type_;
    std::shared_ptr<void> obj_;
};
using ObjectPtr = std::shared_ptr<Object>;

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_TYPE_H_
