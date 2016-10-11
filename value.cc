//---------------------------------------------------------------------------
#include <string.h>
#include <sstream>
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{
//---------------------------------------------------------------------------
size_t Value::HashFunc::operator()(const Value& obj) const
{
    switch(obj.type())
    {
        case TYPE_INVALID:
            return 0;

        case TYPE_BOOLEAN:
        {
            std::hash<bool> hash_fn;
            return hash_fn(*std::static_pointer_cast<bool>(obj.obj()));
        }

        case TYPE_INT:
        {
            std::hash<int64_t> hash_fn;
            return hash_fn(*std::static_pointer_cast<int64_t>(obj.obj()));
        }

        case TYPE_UINT:
        {
            std::hash<uint64_t> hash_fn;
            return hash_fn(*std::static_pointer_cast<uint64_t>(obj.obj()));
        }

        case TYPE_FLOAT:
        {
            std::hash<double> hash_fn;
            return hash_fn(*std::static_pointer_cast<double>(obj.obj()));
        }

        case TYPE_BINARY:
        {
            std::hash<std::shared_ptr<Binary> > hash_fn;
            return hash_fn(std::static_pointer_cast<Binary>(obj.obj()));
        }

        case TYPE_STRING:
        {
            std::hash<String> hash_fn;
            return hash_fn(*std::static_pointer_cast<String>(obj.obj()));
        }

        case TYPE_LIST:
        {
            std::hash<std::shared_ptr<List> > hash_fn;
            return hash_fn(std::static_pointer_cast<List>(obj.obj()));
        }

        case TYPE_SET:
        {
            std::hash<std::shared_ptr<Set> > hash_fn;
            return hash_fn(std::static_pointer_cast<Set>(obj.obj()));
        }

        case TYPE_ZSET:
        {
            std::hash<std::shared_ptr<ZSet> > hash_fn;
            return hash_fn(std::static_pointer_cast<ZSet>(obj.obj()));
        }

        case TYPE_HASH:
        {
            std::hash<std::shared_ptr<Hash> > hash_fn;
            return hash_fn(std::static_pointer_cast<Hash>(obj.obj()));
        }

        default:
            assert(0);
    }

    return 0;
}
//---------------------------------------------------------------------------
bool Value::SetBoolean(bool val)
{
    if(TYPE_BOOLEAN != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<bool>(obj_) = val;
    else
        obj_ = std::make_shared<bool>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetInt(int64_t val)
{
    if(TYPE_INT != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<int64_t>(obj_) = val;
    else
        obj_ = std::make_shared<int64_t>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetUInt(uint64_t val)
{
    if(TYPE_UINT != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<uint64_t>(obj_) = val;
    else
        obj_ = std::make_shared<uint64_t>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetFloat(double val)
{
    if(TYPE_FLOAT != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<double>(obj_) = val;
    else
        obj_ = std::make_shared<double>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetBinary(const Binary& val)
{
    if(TYPE_BINARY != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<Binary>(obj_) = val;
    else
        obj_ = std::make_shared<Binary>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetBinary(Binary&& val)
{
    if(TYPE_BINARY != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<Binary>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<Binary>(std::move(val));

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetString(const String& val)
{
    if(TYPE_STRING != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<String>(obj_) = val;
    else
        obj_ = std::make_shared<String>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetString(String&& val)
{
    if(TYPE_STRING != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<String>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<String>(std::move(val));

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetList(const List& val)
{
    if(TYPE_LIST != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<List>(obj_) = val;
    else
        obj_ = std::make_shared<List>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetList(List&& val)
{
    if(TYPE_LIST != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<List>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<List>(std::move(val));

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetSet(const Set& val)
{
    if(TYPE_SET != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<Set>(obj_) = val;
    else
        obj_ = std::make_shared<Set>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetSet(Set&& val)
{
    if(TYPE_SET != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<Set>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<Set>(std::move(val));

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetZSet(const ZSet& val)
{
    if(TYPE_ZSET != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<ZSet>(obj_) = val;
    else
        obj_ = std::make_shared<ZSet>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetZSet(ZSet&& val)
{
    if(TYPE_ZSET != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<ZSet>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<ZSet>(std::move(val));

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetHash(const Hash& val)
{
    if(TYPE_HASH != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<Hash>(obj_) = val;
    else
        obj_ = std::make_shared<Hash>(val);

    return true;
}
//---------------------------------------------------------------------------
bool Value::SetHash(Hash&& val)
{
    if(TYPE_HASH != type_)
    {
        assert(0);
        return false;
    }

    if(obj_.unique())
        *std::static_pointer_cast<Hash>(obj_) = std::move(val);
    else
        obj_ = std::make_shared<Hash>(std::move(val));

    return true;
}
//---------------------------------------------------------------------------
bool Value::operator==(const Value& val) const
{
    if(type() != val.type())
        return false;

    switch(val.type())
    {
        case TYPE_INVALID:  return obj_ == val.obj();
        case TYPE_BOOLEAN:  return *std::static_pointer_cast<bool>(obj_) == *std::static_pointer_cast<bool>(val.obj());
        case TYPE_INT:      return *std::static_pointer_cast<int64_t>(obj_) == *std::static_pointer_cast<int64_t>(val.obj());
        case TYPE_UINT:     return *std::static_pointer_cast<uint64_t>(obj_) == *std::static_pointer_cast<uint64_t>(val.obj());
        case TYPE_FLOAT:    return *std::static_pointer_cast<double>(obj_) == *std::static_pointer_cast<double>(val.obj());
        case TYPE_BINARY:   return *std::static_pointer_cast<Binary>(obj_) == *std::static_pointer_cast<Binary>(val.obj());
        case TYPE_STRING:   return *std::static_pointer_cast<String>(obj_) == *std::static_pointer_cast<String>(val.obj());
        case TYPE_LIST:     return *std::static_pointer_cast<List>(obj_) == *std::static_pointer_cast<List>(val.obj());
        case TYPE_SET:      return *std::static_pointer_cast<Set>(obj_) == *std::static_pointer_cast<Set>(val.obj());
        case TYPE_ZSET:     return *std::static_pointer_cast<ZSet>(obj_) == *std::static_pointer_cast<ZSet>(val.obj());
        case TYPE_HASH:     return *std::static_pointer_cast<Hash>(obj_) == *std::static_pointer_cast<Hash>(val.obj());

        default:
            assert(0);
    }

    return true;
}
//---------------------------------------------------------------------------
bool Value::operator!=(const Value& val) const
{
    return !(*this == val);
}
//---------------------------------------------------------------------------
bool operator!=(const Value& left, const Value& right)
{
    return !(left==right);
}
//---------------------------------------------------------------------------
static std::string BinToString(const unsigned char* buffer, size_t len)
{
     char bin[3];
     std::string result;
     for(size_t i=0; i<len; i++)
     {
         snprintf(bin, 3, "%02X", buffer[i]);
         result.append(bin);
     }

     return result;
}
//---------------------------------------------------------------------------
std::string Value::ValueToString(int deep, bool add_tabs) const
{
    std::stringstream ss;

    switch(type())
    {
        case Value::TYPE_LIST:  if(true==add_tabs) ss << Tab(deep); ss << "[" << std::endl; break;
        case Value::TYPE_SET:
        case Value::TYPE_ZSET:  if(true==add_tabs) ss << Tab(deep); ss << "(" << std::endl; break;
        case Value::TYPE_HASH:  if(true==add_tabs) ss << Tab(deep); ss << "{" << std::endl; break;
    }

    switch(type())
    {
        case Value::TYPE_INVALID:
            ss << "nil";
            break;

        case Value::TYPE_BOOLEAN: 
            ss << std::boolalpha << GetBoolean() << std::noboolalpha;
            break;

        case Value::TYPE_INT: 
            ss << GetInt();
            break;

        case Value::TYPE_UINT: 
            ss << GetUInt();
            break;

        case Value::TYPE_FLOAT: 
            ss << GetFloat();
            break;

        case Value::TYPE_STRING: 
            ss << "\"" << GetString() << "\"";
            break;

        case Value::TYPE_BINARY:
            ss << "x\'" << BinToString(GetBinary().data(), GetBinary().size());
            break;

        case Value::TYPE_LIST:
            ss << UnaryContainerToString(GetList(), deep+1);
            break;

        case Value::TYPE_SET:
            ss << UnaryContainerToString(GetSet(), deep+1);
            break;

        case Value::TYPE_ZSET:
            ss << BinaryContainerToString(GetZSet(), deep+1);
            break;

        case Value::TYPE_HASH:
            ss << BinaryContainerToString(GetHash(), deep+1);
            break;
    }

    switch(type())
    {
        case Value::TYPE_LIST:  ss << std::endl << Tab(deep) << "]"; break;
        case Value::TYPE_SET:
        case Value::TYPE_ZSET:  ss << std::endl << Tab(deep) << ")"; break;
        case Value::TYPE_HASH:  ss << std::endl << Tab(deep) << "}"; break;
    }

    return ss.str();
}
//---------------------------------------------------------------------------
template<typename T>
std::string Value::UnaryContainerToString(const T& val, int deep) const
{
    std::stringstream ss;

    for(auto iter : val)
    {
        switch(iter.type())
        {
            case TYPE_INVALID:
                ss << Tab(deep);
                ss << "nil";
                break;

            case TYPE_BOOLEAN: 
                ss << Tab(deep);
                ss << std::boolalpha << iter.GetBoolean() << std::noboolalpha;
                break;

            case TYPE_INT: 
                ss << Tab(deep);
                ss << iter.GetInt();
                break;

            case TYPE_UINT: 
                ss << Tab(deep);
                ss << iter.GetUInt();
                break;

            case TYPE_FLOAT: 
                ss << Tab(deep);
                ss << iter.GetFloat();
                break;

            case TYPE_STRING: 
                ss << Tab(deep);
                ss << "\"" << iter.GetString() << "\"";
                break;

            case TYPE_BINARY:
                ss << Tab(deep);
                ss << "x\'" << BinToString(iter.GetBinary().data(), iter.GetBinary().size());
                break;

            case TYPE_LIST:
                ss << iter.ValueToString(deep);
                break;

            case TYPE_SET:
                ss << iter.ValueToString(deep);
                break;

            case TYPE_ZSET:
                ss << iter.ValueToString(deep);
                break;

            case TYPE_HASH:
                ss << iter.ValueToString(deep);
                break;
        }

        ss << "," << std::endl;
    }


    std::string str = ss.str();
    str.pop_back(); str.pop_back(); 

    return str;
}
//---------------------------------------------------------------------------
template<typename T>
std::string Value::BinaryContainerToString(const T& val, int deep) const
{
    std::stringstream ss;

    for(auto iter : val)
    {
        ss << Tab(deep);
        ss << iter.first << ":";

        switch(iter.second.type())
        {
            case TYPE_INVALID:
                ss << "nil";
                break;

            case TYPE_BOOLEAN: 
                ss << std::boolalpha << iter.second.GetBoolean() << std::noboolalpha;
                break;

            case TYPE_INT: 
                ss << iter.second.GetInt();
                break;

            case TYPE_UINT: 
                ss << iter.second.GetUInt();
                break;

            case TYPE_FLOAT: 
                ss << iter.second.GetFloat();
                break;

            case TYPE_STRING: 
                ss << "\"" << iter.second.GetString() << "\"";
                break;

            case TYPE_BINARY:
                ss << "x\'" << BinToString(iter.second.GetBinary().data(), iter.second.GetBinary().size());
                break;

            case TYPE_LIST:
                ss << iter.second.ValueToString(deep, false);
                break;

            case TYPE_SET:
                ss << iter.second.ValueToString(deep, false);
                break;

            case TYPE_ZSET:
                ss << iter.second.ValueToString(deep, false);
                break;

            case TYPE_HASH:
                ss << iter.second.ValueToString(deep, false);
                break;
        }

        ss << "," << std::endl;
    }

    std::string str = ss.str();
    str.pop_back();str.pop_back();

    return str;
}
//---------------------------------------------------------------------------
std::string Value::Tab(int deep) const
{
    std::string str;
    for(int i=0; i<deep; i++)
        str += "\t";

    return str;
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const Value& val)
{
    std::string str = val.ValueToString(0);
    out << str;

    return out;
}
//---------------------------------------------------------------------------
}//namespace db
