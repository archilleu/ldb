//---------------------------------------------------------------------------
#include <string.h>
#include <sstream>
#include "value.h"
//---------------------------------------------------------------------------
namespace
{

std::string BinToString(const unsigned char* buffer, size_t len)
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

}
//---------------------------------------------------------------------------
namespace db
{

//---------------------------------------------------------------------------
size_t Value::HashFunc::operator()(const Value& obj) const
{
    switch(obj.type())
    {
        case INVALID:
            return 0;

        case BOOLEAN:
        {
            std::hash<bool> hash_fn;
            return hash_fn(*std::static_pointer_cast<bool>(obj.obj()));
        }

        case INT:
        {
            std::hash<int64_t> hash_fn;
            return hash_fn(*std::static_pointer_cast<int64_t>(obj.obj()));
        }

        case UINT:
        {
            std::hash<uint64_t> hash_fn;
            return hash_fn(*std::static_pointer_cast<uint64_t>(obj.obj()));
        }

        case FLOAT:
        {
            std::hash<double> hash_fn;
            return hash_fn(*std::static_pointer_cast<double>(obj.obj()));
        }

        case BINARY:
        {
            std::hash<std::shared_ptr<Binary> > hash_fn;
            return hash_fn(std::static_pointer_cast<Binary>(obj.obj()));
        }

        case STRING:
        {
            std::hash<String> hash_fn;
            return hash_fn(*std::static_pointer_cast<String>(obj.obj()));
        }

        case LIST:
        {
            std::hash<std::shared_ptr<List> > hash_fn;
            return hash_fn(std::static_pointer_cast<List>(obj.obj()));
        }

        case SET:
        {
            std::hash<std::shared_ptr<Set> > hash_fn;
            return hash_fn(std::static_pointer_cast<Set>(obj.obj()));
        }

        case ZSET:
        {
            std::hash<std::shared_ptr<ZSet> > hash_fn;
            return hash_fn(std::static_pointer_cast<ZSet>(obj.obj()));
        }

        case HASH:
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
Value::Value(TYPE t)
{
    switch(t)
    {
        case INVALID:  type_ = INVALID;                                           break;
        case BOOLEAN:  type_ = BOOLEAN;   obj_ = std::make_shared<bool>();        break;
        case INT:      type_ = INT;       obj_ = std::make_shared<int64_t>();     break;
        case UINT:     type_ = UINT;      obj_ = std::make_shared<uint64_t>();    break;
        case FLOAT:    type_ = FLOAT;     obj_ = std::make_shared<double>();      break;
        case BINARY:   type_ = BINARY;    obj_ = std::make_shared<Binary>();      break;
        case STRING:   type_ = STRING;    obj_ = std::make_shared<String>();      break;
        case LIST:     type_ = LIST;      obj_ = std::make_shared<List>();        break;
        case SET:      type_ = SET;       obj_ = std::make_shared<Set>();         break;
        case ZSET:     type_ = ZSET;      obj_ = std::make_shared<ZSet>();        break;
        case HASH:     type_ = HASH;      obj_ = std::make_shared<Hash>();        break;

        default:
            assert(0);
    }

    return;
}
//---------------------------------------------------------------------------
bool Value::SetBoolean(bool val)
{
    if(BOOLEAN != type_)
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
    if(INT != type_)
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
    if(UINT != type_)
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
    if(FLOAT != type_)
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
    if(BINARY != type_)
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
    if(BINARY != type_)
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
    if(STRING != type_)
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
    if(STRING != type_)
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
    if(LIST != type_)
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
    if(LIST != type_)
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
    if(SET != type_)
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
    if(SET != type_)
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
    if(ZSET != type_)
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
    if(ZSET != type_)
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
    if(HASH != type_)
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
    if(HASH != type_)
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
        case INVALID:  return obj_ == val.obj();
        case BOOLEAN:  return *std::static_pointer_cast<bool>(obj_) == *std::static_pointer_cast<bool>(val.obj());
        case INT:      return *std::static_pointer_cast<int64_t>(obj_) == *std::static_pointer_cast<int64_t>(val.obj());
        case UINT:     return *std::static_pointer_cast<uint64_t>(obj_) == *std::static_pointer_cast<uint64_t>(val.obj());
        case FLOAT:    return *std::static_pointer_cast<double>(obj_) == *std::static_pointer_cast<double>(val.obj());
        case BINARY:   return *std::static_pointer_cast<Binary>(obj_) == *std::static_pointer_cast<Binary>(val.obj());
        case STRING:   return *std::static_pointer_cast<String>(obj_) == *std::static_pointer_cast<String>(val.obj());
        case LIST:     return *std::static_pointer_cast<List>(obj_) == *std::static_pointer_cast<List>(val.obj());
        case SET:      return *std::static_pointer_cast<Set>(obj_) == *std::static_pointer_cast<Set>(val.obj());
        case ZSET:     return *std::static_pointer_cast<ZSet>(obj_) == *std::static_pointer_cast<ZSet>(val.obj());
        case HASH:     return *std::static_pointer_cast<Hash>(obj_) == *std::static_pointer_cast<Hash>(val.obj());

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
Value& Value::operator[](const char* key)
{
    assert(HASH == type_);

    return GetHash()[key];
}
//---------------------------------------------------------------------------
Value& Value::operator[](const String& key)
{
    assert(HASH == type_);

    return GetHash()[key];
}
//---------------------------------------------------------------------------
const Value& Value::operator[](const char* key) const
{
    assert(HASH == type_);

    static Value kNone(INVALID);

    const auto& ret = GetHash().find(key);
    if(ret == GetHash().end())
        return kNone;

    return ret->second;
}
//---------------------------------------------------------------------------
const Value& Value::operator[](const String& key) const
{
    assert(HASH == type_);

    static Value kNone(INVALID);

    const auto& ret = GetHash().find(key);
    if(ret == GetHash().end())
        return kNone;

    return ret->second;
}
//---------------------------------------------------------------------------
Value::List Value::operator[](double score) const
{
    Value::List list;

    //std::pair<Value::ZSet::const_iterator, Value::ZSet::const_iterator> pair = GetZSet().equal_range(score);
    for(auto pair=GetZSet().equal_range(score); pair.first!=pair.second; ++pair.first)
        list.push_back(pair.first->second);

    return list;
}
//---------------------------------------------------------------------------
std::string Value::ValueToString(int deep, bool add_tabs) const
{
    std::stringstream ss;

    switch(type())
    {
        case LIST:  if(true==add_tabs) ss << AddTab(deep); ss << "[" << std::endl; break;
        case SET:
        case ZSET:  if(true==add_tabs) ss << AddTab(deep); ss << "(" << std::endl; break;
        case HASH:  if(true==add_tabs) ss << AddTab(deep); ss << "{" << std::endl; break;
    }

    switch(type())
    {
        case INVALID:
            ss << "nil";
            break;

        case BOOLEAN:
            ss << std::boolalpha << GetBoolean() << std::noboolalpha;
            break;

        case INT:
            ss << GetInt();
            break;

        case UINT:
            ss << GetUInt();
            break;

        case FLOAT:
            ss << GetFloat();
            break;

        case STRING:
            ss << "\"" << GetString() << "\"";
            break;

        case BINARY:
            ss << "x\'" << BinToString(GetBinary().data(), GetBinary().size());
            break;

        case LIST:
            ss << UnaryContainerToString(GetList(), deep+1);
            break;

        case SET:
            ss << UnaryContainerToString(GetSet(), deep+1);
            break;

        case ZSET:
            ss << BinaryContainerToString(GetZSet(), deep+1);
            break;

        case HASH:
            ss << BinaryContainerToString(GetHash(), deep+1);
            break;
    }

    switch(type())
    {
        case LIST:  ss << std::endl << AddTab(deep) << "]"; break;
        case SET:
        case ZSET:  ss << std::endl << AddTab(deep) << ")"; break;
        case HASH:  ss << std::endl << AddTab(deep) << "}"; break;
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
            case INVALID:
                ss << AddTab(deep);
                ss << "nil";
                break;

            case BOOLEAN:
                ss << AddTab(deep);
                ss << std::boolalpha << iter.GetBoolean() << std::noboolalpha;
                break;

            case INT:
                ss << AddTab(deep);
                ss << iter.GetInt();
                break;

            case UINT:
                ss << AddTab(deep);
                ss << iter.GetUInt();
                break;

            case FLOAT:
                ss << AddTab(deep);
                ss << iter.GetFloat();
                break;

            case STRING:
                ss << AddTab(deep);
                ss << "\"" << iter.GetString() << "\"";
                break;

            case BINARY:
                ss << AddTab(deep);
                ss << "x\'" << BinToString(iter.GetBinary().data(), iter.GetBinary().size());
                break;

            case LIST:
                ss << iter.ValueToString(deep);
                break;

            case SET:
                ss << iter.ValueToString(deep);
                break;

            case ZSET:
                ss << iter.ValueToString(deep);
                break;

            case HASH:
                ss << iter.ValueToString(deep);
                break;
        }

        ss << "," << std::endl;
    }

    std::string str = ss.str();
    if(2 <= str.size())
    {
        str.pop_back();
        str.pop_back();
    }

    return str;
}
//---------------------------------------------------------------------------
template<typename T>
std::string Value::BinaryContainerToString(const T& val, int deep) const
{
    std::stringstream ss;

    for(auto iter : val)
    {
        ss << AddTab(deep);
        ss << iter.first << ":";

        switch(iter.second.type())
        {
            case INVALID:
                ss << "nil";
                break;

            case BOOLEAN:
                ss << std::boolalpha << iter.second.GetBoolean() << std::noboolalpha;
                break;

            case INT:
                ss << iter.second.GetInt();
                break;

            case UINT:
                ss << iter.second.GetUInt();
                break;

            case FLOAT:
                ss << iter.second.GetFloat();
                break;

            case STRING:
                ss << "\"" << iter.second.GetString() << "\"";
                break;

            case BINARY:
                ss << "x\'" << BinToString(iter.second.GetBinary().data(), iter.second.GetBinary().size());
                break;

            case LIST:
                ss << iter.second.ValueToString(deep, false);
                break;

            case SET:
                ss << iter.second.ValueToString(deep, false);
                break;

            case ZSET:
                ss << iter.second.ValueToString(deep, false);
                break;

            case HASH:
                ss << iter.second.ValueToString(deep, false);
                break;
        }

        ss << "," << std::endl;
    }

    std::string str = ss.str();
    if(2 <= str.size())
    {
        str.pop_back();
        str.pop_back();
    }

    return str;
}
//---------------------------------------------------------------------------
std::string Value::AddTab(int deep) const
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
