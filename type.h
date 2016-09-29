//---------------------------------------------------------------------------
#ifndef DB_TYPE_H_
#define DB_TYPE_H_
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
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
                                    using Binary= std::vector<unsigned char>;
                                    using String= std::string;
template<typename T>                using List  = std::list<T>;
template<typename T>                using Set   = std::unordered_set<T>;
template<typename T, typename Y>    using ZSet  = std::map<T, Y>;
template<typename T, typename Y>    using Hash  = std::unordered_map<T, Y>;

//data object
class Object
{
public:
    Object(short t=TYPE_INVALID):type_(t){}

    short type() { return type_; }

    std::shared_ptr<void> obj_;

private:
    short type_;
};
using ObjectPtr = std::shared_ptr<Object>;

}//namespace db
//---------------------------------------------------------------------------
#endif //DB_TYPE_H_
