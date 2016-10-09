//---------------------------------------------------------------------------
#include <string.h>
#include "value.h"
//---------------------------------------------------------------------------
namespace db
{
//---------------------------------------------------------------------------
size_t Value::HashFunc::operator()(const Value& obj) const
{
    switch(obj.type())
    {
        case TYPE_BOOLEAN:
            {
                std::hash<std::shared_ptr<bool> > hash_fn;
                return hash_fn(std::static_pointer_cast<bool>(obj.obj()));
            }

        case TYPE_INT:
            {
                std::hash<std::shared_ptr<int64_t> > hash_fn;
                return hash_fn(std::static_pointer_cast<int64_t>(obj.obj()));
            }

        case TYPE_UINT:
            {
                std::hash<std::shared_ptr<uint64_t> > hash_fn;
                return hash_fn(std::static_pointer_cast<uint64_t>(obj.obj()));
            }

        case TYPE_FLOAT:
            {
                std::hash<std::shared_ptr<double> > hash_fn;
                return hash_fn(std::static_pointer_cast<double>(obj.obj()));
            }

        case TYPE_BINARY:
            {
                std::hash<std::shared_ptr<Binary> > hash_fn;
                return hash_fn(std::static_pointer_cast<Binary>(obj.obj()));
            }

        case TYPE_STRING:
            {
                std::hash<std::shared_ptr<String> > hash_fn;
                return hash_fn(std::static_pointer_cast<String>(obj.obj()));
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
            return 0;
    }
}
//---------------------------------------------------------------------------
bool Value::EqualFunc::operator()(const Value& left, const Value& right)
{
    if(left.type() == right.type())
    {
        switch(left.type())
        {
            case TYPE_BOOLEAN: return std::static_pointer_cast<bool>(left.obj()) == std::static_pointer_cast<bool>(right.obj());
            case TYPE_INT: return std::static_pointer_cast<int64_t>(left.obj()) == std::static_pointer_cast<int64_t>(right.obj());
            case TYPE_UINT: return std::static_pointer_cast<uint64_t>(left.obj()) == std::static_pointer_cast<uint64_t>(right.obj());
            case TYPE_FLOAT: return std::static_pointer_cast<double>(left.obj()) == std::static_pointer_cast<double>(right.obj());
            case TYPE_BINARY: return std::static_pointer_cast<Binary>(left.obj()) == std::static_pointer_cast<Binary>(right.obj());
            case TYPE_STRING: return std::static_pointer_cast<String>(left.obj()) == std::static_pointer_cast<String>(right.obj());
            case TYPE_LIST: return std::static_pointer_cast<List>(left.obj()) == std::static_pointer_cast<List>(right.obj());
            case TYPE_SET: return std::static_pointer_cast<Set>(left.obj()) == std::static_pointer_cast<Set>(right.obj());
            case TYPE_ZSET: return std::static_pointer_cast<ZSet>(left.obj()) == std::static_pointer_cast<ZSet>(right.obj());
            case TYPE_HASH: return std::static_pointer_cast<Hash>(left.obj()) == std::static_pointer_cast<Hash>(right.obj());

            default:
                assert(0);
                return true;
        }
    }

    return false;
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
template<typename T>
static bool CompContainer1(const T& left, const T& right);
template<typename T>
static bool CompContainer2(const T& left, const T& right);
//---------------------------------------------------------------------------
template<typename T>
static bool CompContainer1(const T& left, const T& right)
{
    if(left.size() != right.size())
        return false;

    for(auto l=left.begin(),r=right.begin(); l!=left.end(); ++l,++r)
    {
        if(l->type() != r->type())
            return false;

        switch(l->type())
        {
            case Value::TYPE_INVALID:
                if(l->obj() != r->obj())
                    return false;

                break;

            case Value::TYPE_BOOLEAN:
                if(l->GetBoolean() != r->GetBoolean())
                    return false;

                break;

            case Value::TYPE_INT:
                if(l->GetInt() != r->GetInt())
                    return false;

                break;

            case Value::TYPE_UINT:
                if(l->GetUInt() != r->GetUInt())
                    return false;

                break;

            case Value::TYPE_FLOAT:
                if(0 != static_cast<int>(l->GetFloat()-r->GetFloat()))
                    return false;

                break;

            case Value::TYPE_BINARY:
                if(0 != memcmp(l->GetBinary().data(), r->GetBinary().data(), l->GetBinary().size()))
                    return false;

                break;

            case Value::TYPE_STRING:
                if(l->GetString() != r->GetString())
                    return false;

                break;

            case Value::TYPE_LIST:
                if(true != CompContainer1(l->GetList(), r->GetList()))
                    return false;

                break;

            case Value::TYPE_SET:
                if(true != CompContainer1(l->GetSet(), r->GetSet()))
                    return false;

                break;

            case Value::TYPE_ZSET:
                if(true != CompContainer2(l->GetZSet(), r->GetZSet()))
                    return false;

                break;

            case Value::TYPE_HASH:
                if(true != CompContainer2(l->GetHash(), r->GetHash()))
                    return false;

                break;

            default:
                assert(0);
                return false;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
template<typename T>
static bool CompContainer2(const T& left, const T& right)
{
    if(left.size() != right.size())
        return false;

    for(auto l=left.begin(),r=right.begin(); l!=left.end(); ++l,++r)
    {
        if(l->first != r->first)
            return false;

        if(l->second.type() != r->second.type())
            return false;

        switch(l->second.type())
        {
            case Value::TYPE_INVALID:
                if(l->second.obj() != r->second.obj())
                    return false;

                break;

            case Value::TYPE_BOOLEAN:
                if(l->second.GetBoolean() != r->second.GetBoolean())
                    return false;

                break;

            case Value::TYPE_INT:
                if(l->second.GetInt() != r->second.GetInt())
                    return false;

                break;

            case Value::TYPE_UINT:
                if(l->second.GetUInt() != r->second.GetUInt())
                    return false;

                break;

            case Value::TYPE_FLOAT:
                if(0 != static_cast<int>(l->second.GetFloat()-r->second.GetFloat()))
                    return false;

                break;

            case Value::TYPE_BINARY:
                return (0 == memcmp(l->second.GetBinary().data(), r->second.GetBinary().data(), l->second.GetBinary().size()));

                break;

            case Value::TYPE_STRING:
                if(l->second.GetString() != r->second.GetString())
                    return false;

                break;

            case Value::TYPE_LIST:
                if(true != CompContainer1(l->second.GetList(), r->second.GetList()))
                    return false;

                break;

            case Value::TYPE_SET:
                if(true != CompContainer1(l->second.GetSet(), r->second.GetSet()))
                    return false;

                break;

            case Value::TYPE_ZSET:
                if(true != CompContainer2(l->second.GetZSet(), r->second.GetZSet()))
                    return false;

                break;

            case Value::TYPE_HASH:
                if(true != CompContainer2(l->second.GetHash(), r->second.GetHash()))
                    return false;

                break;

            default:
                assert(0);
                return false;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
bool operator==(const Value& left, const Value& right)
{
    if(left.type() != right.type())
        return false;

    switch(left.type())
    {
        case Value::TYPE_INVALID:
            return (left.obj() == right.obj());

        case Value::TYPE_BOOLEAN:
            return (left.GetBoolean() == right.GetBoolean());

        case Value::TYPE_INT:
            return (left.GetInt() == right.GetInt());

        case Value::TYPE_UINT:
            return (left.GetUInt() == right.GetUInt());

        case Value::TYPE_FLOAT:
            return (0 != static_cast<int>(left.GetFloat() - right.GetFloat()));

        case Value::TYPE_BINARY:
            return (0 == memcmp(left.GetBinary().data(), right.GetBinary().data(), left.GetBinary().size()));

        case Value::TYPE_STRING:
            return (left.GetString() == right.GetString());

        case Value::TYPE_LIST:
            return CompContainer1(left.GetList(), right.GetList());

        case Value::TYPE_SET:
            return CompContainer1(left.GetSet(), right.GetSet());

        case Value::TYPE_ZSET:
            return CompContainer2(left.GetZSet(), right.GetZSet());

        case Value::TYPE_HASH:
            return CompContainer2(left.GetHash(), right.GetHash());

        default:
            assert(0);
            return false;
        }

    return true;
}
//---------------------------------------------------------------------------
bool operator!=(const Value& left, const Value& right)
{
    return !(left==right);
}
//---------------------------------------------------------------------------
}//namespace db
