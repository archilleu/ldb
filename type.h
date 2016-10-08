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
    inline std::size_t operator()(const Object& obj) const;
};

//equal function(for Set)
struct EqualFunc
{
    inline bool operator()(const Object& left, const Object& right);
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
    Object& operator=(Object&& o){ type_=o.type_; obj_=std::move(o.obj_); o.type_=TYPE_INVALID; o.obj_ = nullptr; return *this; }

    //Set method
    inline void SetBoolean(bool val);
    inline void SetInt(int64_t val);
    inline void SetUInt(uint64_t val);
    inline void SetFloat(double val);

    inline void SetBinary(const Binary& val);
    inline void SetBinary(Binary&& val);

    inline void SetString(const String& val);
    inline void SetString(String&& val);

    inline void SetList(const List& val);
    inline void SetList(List&& val);

    inline void SetSet(const Set& val);
    inline void SetSet(Set&& val);

    inline void SetZSet(const ZSet& val);
    inline void SetZSet(ZSet&& val);

    inline void SetHash(const Hash& val);
    inline void SetHash(Hash&& val);

    //Get method
    inline bool GetBoolean() { assert(TYPE_BOOLEAN); return *std::static_pointer_cast<bool>(obj_); }
    inline int64_t GetInt() { assert(TYPE_INT); return *std::static_pointer_cast<int64_t>(obj_); }
    inline uint64_t GetUInt() { assert(TYPE_UINT); return *std::static_pointer_cast<uint64_t>(obj_); }
    inline double GetFloat() { assert(TYPE_FLOAT); return *std::static_pointer_cast<double>(obj_); }

    inline const Binary& GetBinary() const { assert(TYPE_BINARY); return *std::static_pointer_cast<Binary>(obj_); }
    inline Binary& GetBinary() { assert(TYPE_BINARY); return *std::static_pointer_cast<Binary>(obj_); }

    inline const String& GetString() const { assert(TYPE_STRING); return *std::static_pointer_cast<String>(obj_); }
    inline String& GetString() { assert(TYPE_STRING); return *std::static_pointer_cast<String>(obj_); }

    inline const List& GetList() const { assert(TYPE_LIST); return *std::static_pointer_cast<List>(obj_); }
    inline List& GetList() { assert(TYPE_LIST); return *std::static_pointer_cast<List>(obj_); }

    inline const Set& GetSet() const { assert(TYPE_SET); return *std::static_pointer_cast<Set>(obj_); }
    inline Set& GetSet() { assert(TYPE_SET); return *std::static_pointer_cast<Set>(obj_); }

    inline const ZSet& GetZSet() const { assert(TYPE_ZSET); return *std::static_pointer_cast<ZSet>(obj_); }
    inline ZSet& GetZSet() { assert(TYPE_ZSET); return *std::static_pointer_cast<ZSet>(obj_); }

    inline const Hash& GetHash() const { assert(TYPE_HASH); return *std::static_pointer_cast<Hash>(obj_); }
    inline Hash& GetHash() { assert(TYPE_HASH); return *std::static_pointer_cast<Hash>(obj_); }

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
