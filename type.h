//---------------------------------------------------------------------------
#ifndef DB_TYPE_H_
#define DB_TYPE_H_
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <memory>
//---------------------------------------------------------------------------
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

//data type alias
using Binary = std::vector<unsigned char>;
using String = std::string;

//data object
class Object
{
public:
    Object(short t, std::shared_ptr<void>&& o)
    :   type_(t),
        obj_(o)
    {}
    Object(const Object&) =delete;
    Object(const Object&&) =delete;
    Object& operator=(const Object&) =delete;
    Object& operator=(Object&&) =delete;

    short type() { return type_; }

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
